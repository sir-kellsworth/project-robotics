#include "Network/SocketSerialLogger.h"

#include "Utils/LoggerDefines.h"


//*****************************************************************************
Network::SocketSerialLogger::SocketSerialLogger
(
  const std::string& deviceName,
  uint16_t baudRate
)
:m_socket(deviceName, baudRate),
 m_running(true)
{
  m_backgroundThread = std::thread(this, &Network::SocketSerialLogger::backgroundHandle);
}


//*****************************************************************************
Network::SocketSerialLogger::SocketSerialLogger
(
  int handle
)
:m_socket(handle),
 m_running(true)
{
  m_backgroundThread = std::thread(this, &Network::SocketSerialLogger::backgroundHandle);
}


//*****************************************************************************
Network::SocketSerialLogger::~SocketSerialLogger()
{

}


//*****************************************************************************
void Network::SocketSerialLogger::backgroundHandle()
{
  while(m_running)
  {
    std::vector<uint8_t> data;
    uint32_t size = m_socket.read(data);
    if(!serialDebugLog(data))
    {
      data.resize(size);
      std::lock_guard<std::mutex> lock(m_queueMutex);
      m_queue.push_back(data);
    }
  }
}


//*****************************************************************************
bool Network::SocketSerialLogger::send
(
  const std::vector<uint8_t>& data
)
{
  return m_socket.send(data);
}


//*****************************************************************************
uint32_t Network::SocketSerialLogger::read
(
  std::vector<uint8_t>& data
)
{
  Packet packet = m_queue.pop();
  if(packet.get())
  {
    std::vector<uint8_t>* packetPtr = packet.release();
    data = *packetPtr;
  }

  return data.size();
}


//*****************************************************************************
bool Network::SocketSerialLogger::serialDebugLog
(
  const std::vector<uint8_t>& message
)
{
  bool loggedMessage(false);
  if(std::equal(LOG_HEADER.begin(), LOG_HEADER.end(), message.begin()))
  {
    LOGGER_DEBUG(ARDUINO_DOMAIN, &message[LOG_HEADER_LENGTH]);
    loggedMessage = true;
  }

  return loggedMessage;
}

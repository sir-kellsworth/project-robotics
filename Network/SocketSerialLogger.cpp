#include "Network/SocketSerialLogger.h"

#include "Utils/LoggerDefines.h"

#include <vector>


namespace
{
  const uint16_t LOG_HEADER_LENGTH      (7);
  const std::vector<uint8_t> LOG_HEADER {'#', '#', 'l', 'o', 'g', '#', '#'};
  const char* ARDUINO_DOMAIN            ("Arduino Logger");
  const char* LOGGER_DOMAIN             ("SocketSerialLogger");
}

//*****************************************************************************
Network::SocketSerialLogger::SocketSerialLogger
(
  const std::string& deviceName,
  uint16_t baudRate
)
:m_socket(deviceName, baudRate),
 m_running(true)
{
  m_backgroundThread = std::thread(&Network::SocketSerialLogger::backgroundHandle, this);
}


//*****************************************************************************
Network::SocketSerialLogger::SocketSerialLogger
(
  int handle
)
:m_socket(handle),
 m_running(true)
{
  m_backgroundThread = std::thread(&Network::SocketSerialLogger::backgroundHandle, this);
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
    std::vector<uint8_t> *data(new std::vector<uint8_t>());
    uint32_t size = m_socket.read(*data);
    if(size > 0 && !serialDebugLog(*data))
    {
      data->resize(size);
      std::lock_guard<std::mutex> lock(m_queueMutex);
      m_queue.push(data);
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
  std::vector<uint8_t>* packet = m_queue.pop();
  if(packet)
  {
    data = *packet;
  }

  for(uint8_t& next : data)
  {
    std::cout << (int)next << " ";
  }
  std::cout << std::endl;

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
    LOGGER_DEBUG(ARDUINO_DOMAIN, "%s", &message[LOG_HEADER_LENGTH]);
    loggedMessage = true;
  }

  return loggedMessage;
}

#include "Network/SocketSerial.h"

#include "Utils/LoggerDefines.h"

#include <cstring>
#include <iostream>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


namespace
{
  const char* LOGGER_DOMAIN ("SocketSerial");

  const uint8_t LENGTH_NUM_BYTES(2);
};


//*****************************************************************************
Network::SocketSerial::SocketSerial
(
  const std::string& deviceName,
  uint16_t baudRate
)
{
  m_handle = open(deviceName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if(m_handle < 0)
  {
    LOGGER_ERROR(LOGGER_DOMAIN, "failed to open serial device: %s", deviceName.c_str());
  }

  struct termios tty;
  if(tcgetattr(m_handle, &tty) != 0)
  {
    LOGGER_ERROR(LOGGER_DOMAIN, "failed to get termios settings");
  }
  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
	                                // no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 1;            // should enable blocking

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
	                                // enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

  //set baudrate
  cfsetspeed(&tty, B115200);

	if (tcsetattr (m_handle, TCSANOW, &tty) != 0)
	{
	   LOGGER_ERROR(LOGGER_DOMAIN, "failed to set termios settings %i", errno);
	}
}


//*****************************************************************************
Network::SocketSerial::SocketSerial
(
  int handle
)
:m_handle(handle)
{

}


//*****************************************************************************
Network::SocketSerial::~SocketSerial()
{

}


//*****************************************************************************
bool Network::SocketSerial::send
(
  const std::vector<uint8_t>& data
)
{
  LOGGER_DEBUG(LOGGER_DOMAIN, "trying to write data");
  std::lock_guard<std::mutex> lock(m_writeMutex);
  bool success(true);

  //arduino requires that end bytes are attached
  int totalSize(LENGTH_NUM_BYTES + data.size());
  char rawData[totalSize];
  char* ptr = rawData;
  uint16_t length(data.size());
  memcpy(ptr, &length, LENGTH_NUM_BYTES);
  ptr += LENGTH_NUM_BYTES;
  memcpy(ptr, data.data(), data.size());
  if(write(m_handle, rawData, totalSize) <= 0)
  {
    success = false;
    LOGGER_ERROR(LOGGER_DOMAIN, "failed to send data");
  }
  LOGGER_DEBUG(LOGGER_DOMAIN, "wrote data");

  return success;
}


//*****************************************************************************
uint32_t Network::SocketSerial::read
(
  std::vector<uint8_t>& data
)
{
  std::lock_guard<std::mutex> lock(m_readMutex);
  uint32_t bytesRead(0);
  uint16_t length(0);
  if(readSub((uint8_t*)&length, 2, 200))
  {
    if(data.size() < length)
    {
      data.resize(length);
    }
    uint8_t* dataPtr = data.data();
    uint8_t numTrys(0);
    while(numTrys < 10)
    {
      uint32_t numBytes = readSub(dataPtr, length - bytesRead, 200);
      dataPtr += numBytes;
      bytesRead += numBytes;
      ++numTrys;
    }

    data.resize(bytesRead);
    for(uint8_t& next : data)
    {
      std::cout << (int)next << " ";
    }
    std::cout << std::endl;
  }

  return bytesRead;
}


//*****************************************************************************
uint32_t Network::SocketSerial::readSub
(
  uint8_t* dataPtr,
  uint16_t numBytes,
  uint32_t timeoutMs
)
{
  uint32_t bytesRead(0);
  fd_set socks;
	struct timeval t;
	FD_ZERO(&socks);
	FD_SET(m_handle, &socks);
	t.tv_sec = timeoutMs / 1000;
  t.tv_usec = (timeoutMs % 1000) * 100;
  if(select(m_handle+1, &socks, NULL, NULL, &t))
  {
    bytesRead = ::read(m_handle, dataPtr, numBytes);
  }

  return bytesRead;
}

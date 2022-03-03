#include "Network/SocketSerial.h"

#include <iostream>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


namespace
{
  const uint8_t NUM_END_BYTES(3);
  const uint8_t MESSAGE_END_BYTES[NUM_END_BYTES] = {0x44, 0x44, 0x44};
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
    std::cout << "failed to open serial device: " << deviceName << std::endl;
  }

  struct termios tty;
  if(tcgetattr(m_handle, &tty) != 0)
  {
    std::cout << "failed to get termios settings" << std::endl;
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
	        std::cout << "failed to set termios settings " << errno << std::endl;
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
  std::lock_guard<std::mutex> lock(m_mutex);
  bool success(false);

  std::cout << "sending " << data.size() << " bytes (plus 3 end bytes)" << std::endl;
  if(write(m_handle, data.data(), data.size()) > 0)
  {
    //arduino requires that end bytes are attached
    write(m_handle, MESSAGE_END_BYTES, NUM_END_BYTES);
    success = true;
  }

  return success;
}


//*****************************************************************************
uint32_t Network::SocketSerial::read
(
  std::vector<uint8_t>& data
)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  uint32_t bytesRead;
  fd_set socks;
	struct timeval t;
	FD_ZERO(&socks);
	FD_SET(m_handle, &socks);
	t.tv_sec = 1;
  if(select(m_handle+1, &socks, NULL, NULL, &t))
  {
    bytesRead = ::read(m_handle, data.data(), data.size());
  }
  data.resize(bytesRead);
  std::cout << "read " << bytesRead << " bytes (including end bytes)" << std::endl;

  //arduino requires that end bytes are attached
  data.resize(data.size()-3);

  return bytesRead;
}

#include "Network/SocketSerial.h"

#include <iostream>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


//*****************************************************************************
Network::SocketSerial::SocketSerial
(
  const std::string& deviceName,
  uint16_t baudRate
)
{
  m_handle = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
  if(m_handle < 0)
  {
    std::cout << "failed to open serial device: " << deviceName << std::endl;
  }

  struct termios tty;
  if(tcgetattr(m_handle, &tty) != 0)
  {
    std::cout << "failed to get termios settings" << std::endl;
  }
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cflag |= CREAD | CLOCAL;
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ISIG;

  //set baudrate
  cfsetspeed(&tty, B115200);

  if(tcsetattr(m_handle, TCSANOW, &tty) != 0)
  {
    std::cout << "failed to set termios settings" << std::endl;
  }
}


//*****************************************************************************
Network::SocketSerial::SocketSerial
(
  int handle
)
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
  bool success(false);

  if(write(m_handle, data.data(), data.size()) > 0)
  {
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
  std::cout << "read " << bytesRead << std::endl;

  return bytesRead;
}

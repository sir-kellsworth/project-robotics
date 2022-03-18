#include "Network/SocketTcp.h"

#include "Utils/LoggerDefines.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


namespace
{
  const char* LOGGER_DOMAIN ("SocketTcp");
}

//*****************************************************************************
Network::SocketTcp::SocketTcp
(
  const std::string& ip,
  unsigned short port
)
{
    m_handle = socket(AF_INET, SOCK_STREAM, 0);
    if(m_handle < 0)
    {
      LOGGER_ERROR(LOGGER_DOMAIN, "failed to create tcp socket");
    }

    struct sockaddr_in serv_addr;
    struct hostent *server = gethostbyname(ip.c_str());
    serv_addr.sin_family = AF_INET;
    bcopy(reinterpret_cast<char *>(server->h_addr),
         reinterpret_cast<char *>(&serv_addr.sin_addr.s_addr),
         server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(m_handle,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
      LOGGER_ERROR(LOGGER_DOMAIN, "failed to connect to server at %s", ip.c_str());
    }
}


//*****************************************************************************
Network::SocketTcp::SocketTcp
(
  int handle
)
:m_handle(handle)
{

}


//*****************************************************************************
Network::SocketTcp::~SocketTcp()
{
  close(m_handle);
}


//*****************************************************************************
bool Network::SocketTcp::send
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
uint32_t Network::SocketTcp::read
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

  return bytesRead;
}

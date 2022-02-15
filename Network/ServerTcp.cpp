#include "Network/ServerTcp.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


//*****************************************************************************
Network::ServerTcp::ServerTcp
(
  const std::string& ip,
  unsigned short port
)
{
  struct sockaddr_in serv_addr;

  m_handle = socket(AF_INET, SOCK_STREAM, 0);
  if (m_handle < 0)
  {
    std::cout << "failed to open server socket" << std::endl;
     //error("ERROR opening socket");
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(m_handle, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    std::cout << "failed to bind to server socket" << std::endl;
    //error("ERROR on binding");
  }
  listen(m_handle, 1);
}


//*****************************************************************************
Network::ServerTcp::~ServerTcp()
{

}


//*****************************************************************************
std::unique_ptr<Network::SocketTcp> Network::ServerTcp::accept()
{
  struct sockaddr_in cli_addr;
  socklen_t len =  sizeof(cli_addr);
  std::unique_ptr<Network::SocketTcp> client = std::unique_ptr<Network::SocketTcp>(
    new Network::SocketTcp(::accept(
      m_handle,
      (struct sockaddr *) &cli_addr,
      &len)));

  return std::move(client);
}

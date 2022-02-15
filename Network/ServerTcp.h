#ifndef NETWORK_SERVERTCP_H
#define NETWORK_SERVERTCP_H

#include "Network/SocketTcp.h"

#include <memory>

namespace Network
{

class ServerTcp
{
public:
  ServerTcp(
    const std::string& ip,
    unsigned short port);

  ~ServerTcp();

  std::unique_ptr<Network::SocketTcp> accept();
private:
  int m_handle;
};

}

#endif

#ifndef NETWORK_SOCKETTCP_H
#define NETWORK_SOCKETTCP_H

#include "Network/Socket.h"

namespace Network
{

class SocketTcp : public Socket
{
public:
  SocketTcp(
    const std::string& ip,
    unsigned short port);

  SocketTcp(
    int handle);

  virtual ~SocketTcp();

  virtual bool send(
    const std::vector<uint8_t>& data);

  virtual uint32_t read(
    std::vector<uint8_t>& data);
private:
  int m_handle;
};

}

#endif

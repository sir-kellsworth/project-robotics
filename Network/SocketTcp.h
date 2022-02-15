#ifndef NETWORK_SOCKETTCP_H
#define NETWORK_SOCKETTCP_H

#include <string>
#include <vector>

namespace Network
{

class SocketTcp
{
public:
  SocketTcp(
    const std::string& ip,
    unsigned short port);

  SocketTcp(
    int handle);

  ~SocketTcp();

  bool send(
    const std::vector<uint8_t>& data);

  uint32_t read(
    std::vector<uint8_t>& data);
private:
  int m_handle;
};

}

#endif

#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include <string>
#include <vector>

namespace Network
{

class Socket
{
public:
  virtual ~Socket();

  virtual bool send(
    const std::vector<uint8_t>& data) = 0;

  virtual uint32_t read(
    std::vector<uint8_t>& data) = 0;
};

}

#endif

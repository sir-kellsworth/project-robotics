#ifndef NETWORK_SOCKETSERIAL_H
#define NETWORK_SOCKETSERIAL_H

#include "Network/Socket.h"

#include <mutex>

namespace Network
{

class SocketSerial : public Socket
{
public:
  SocketSerial(
    const std::string& deviceName,
    uint16_t baudRate);

  SocketSerial(
    int handle);

  ~SocketSerial();

  bool send(
    const std::vector<uint8_t>& data);

  uint32_t read(
    std::vector<uint8_t>& data);
private:
  int m_handle;
  std::mutex m_mutex;
};

}

#endif

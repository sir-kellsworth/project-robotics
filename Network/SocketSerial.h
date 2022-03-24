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

  virtual ~SocketSerial();

  virtual bool send(
    const std::vector<uint8_t>& data);

  virtual uint32_t read(
    std::vector<uint8_t>& data);

  uint32_t readSub(
    uint8_t* dataPtr,
    uint16_t numBytes,
    uint32_t timeoutMs);
private:
  int m_handle;
  std::mutex m_readMutex;
  std::mutex m_writeMutex;
};

}

#endif

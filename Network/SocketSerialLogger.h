#ifndef NETWORK_SOCKETSERIALLOGGER_H
#define NETWORK_SOCKETSERIALLOGGER_H

#include "Network/Socket.h"
#include "Network/SocketSerial.h"

#include <atomic>
#include <thread>
#include <queue>

namespace Network
{

class SocketSerialLogger : public Socket
{
public:
  SocketSerialLogger(
    const std::string& deviceName,
    uint16_t baudRate);

  SocketSerialLogger(
    int handle);

  virtual ~SocketSerialLogger();

  virtual bool send(
    const std::vector<uint8_t>& data);

  virtual uint32_t read(
    std::vector<uint8_t>& data);
private:
  void backgroundHandle();

  bool serialDebugLog(
    const std::vector<uint8_t>& message);

  typedef std::shared_ptr<std::vector<uint8_t>> Packet;
  std::mutex m_queueMutex;
  std::queue<Packet> m_queue;
  std::thread m_backgroundThread;
  Network::SocketSerial m_socket;
  std::atomic<bool> m_running;
};

}

#endif

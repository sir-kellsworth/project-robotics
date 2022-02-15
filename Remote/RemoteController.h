#ifndef REMOTE_REMOTECONTROLLER_H
#define REMOTE_REMOTECONTROLLER_H

#include "ControlInterface/Device.h"
#include "Network/SocketTcp.h"

#include <atomic>
#include <memory>
#include <string>
#include <thread>

namespace Remote
{

class RemoteController
{
public:
  RemoteController(
    std::unique_ptr<ControlInterface::Device>& sim,
    unsigned short port);

  ~RemoteController();
private:
  void backgroundHandle();

  std::unique_ptr<ControlInterface::Device> m_sim;
  std::unique_ptr<Network::SocketTcp> m_socket;
  std::thread m_thread;
  std::atomic<bool> m_running;
};

}

#endif

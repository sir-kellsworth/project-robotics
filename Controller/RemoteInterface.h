#ifndef CONTROLLER_REMOTEINTERFACE_H
#define CONTROLLER_REMOTEINTERFACE_H


#include "ControlInterface/Device.h"
#include "Network/Socket.h"

namespace Controller
{

class RemoteInterface : public ControlInterface::Device
{
public:
  RemoteInterface(
    std::unique_ptr<Network::Socket>& socket);

  ~RemoteInterface();

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    std::shared_ptr<ActionMessage::Action> nextAction);
private:
  std::unique_ptr<Network::Socket> m_socket;
};

}

#endif
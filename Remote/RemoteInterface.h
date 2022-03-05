#ifndef REMOTE_REMOTEINTERFACE_H
#define REMOTE_REMOTEINTERFACE_H


#include "ControlInterface/Device.h"
#include "Network/Socket.h"

namespace Remote
{

class RemoteInterface : public ControlInterface::Device
{
public:
  RemoteInterface(
    std::unique_ptr<Network::Socket>& socket);

  ~RemoteInterface();

  virtual void actionSend(
    std::shared_ptr<ActionMessage::Action> nextAction);

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    std::shared_ptr<ActionMessage::Action> nextAction);

  virtual void powerDownSend();

  virtual void powerUpSend();
private:
  std::unique_ptr<Network::Socket> m_socket;
};

}

#endif

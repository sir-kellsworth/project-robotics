#ifndef REMOTE_REMOTEINTERFACE_H
#define REMOTE_REMOTEINTERFACE_H


#include "ControlInterface/Device.h"
#include "Network/SocketTcp.h"

namespace Remote
{

class RemoteInterface : public ControlInterface::Device
{
public:
  RemoteInterface(
    const std::string& ip,
    unsigned short port);

  ~RemoteInterface();

  virtual void actionSend(
    std::shared_ptr<ActionMessage::Action> nextAction);

  virtual void powerDownSend();

  virtual void powerUpSend();
private:
  Network::SocketTcp m_socket;
};

}

#endif

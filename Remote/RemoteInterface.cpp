#include "Remote/RemoteInterface.h"


#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"

#include <vector>

//*****************************************************************************
Remote::RemoteInterface::RemoteInterface
(
  std::unique_ptr<Network::Socket>& socket
)
:m_socket(std::move(socket))
{

}


//*****************************************************************************
Remote::RemoteInterface::~RemoteInterface()
{

}


//*****************************************************************************
void Remote::RemoteInterface::actionSend
(
  std::shared_ptr<ActionMessage::Action> nextAction
)
{
  if(nextAction.get() != 0)
  {
    std::unique_ptr<ActionMessage::ActionEncoder> encoder
      = ActionMessage::ActionFactory::encoderGet(nextAction);
    std::vector<uint8_t> data;
    encoder->actionEncode(data);

    m_socket->send(data);
  }
}


//*****************************************************************************
shared_ptr<ActionMessage::Action> Remote::RemoteInterface::actionSendReply
(
  std::shared_ptr<ActionMessage::Action> nextAction
)
{
  shared_ptr<ActionMessage::Action> reply;
  if(nextAction.get() != 0)
  {
    std::unique_ptr<ActionMessage::ActionEncoder> encoder
      = ActionMessage::ActionFactory::encoderGet(nextAction);
    std::vector<uint8_t> data;
    encoder->actionEncode(data);

    m_socket->send(data);

    m_socket->read(data);
    reply = ActionMessage::ActionFactory::messageGenerate(data);
  }

  return reply;
}


//*****************************************************************************
void Remote::RemoteInterface::powerDownSend()
{

}


//*****************************************************************************
void Remote::RemoteInterface::powerUpSend()
{

}

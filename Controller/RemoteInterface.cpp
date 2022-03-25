#include "Controller/RemoteInterface.h"


#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"

#include <vector>

namespace
{
  const uint16_t MAX_SIZE(500);
}

//*****************************************************************************
Controller::RemoteInterface::RemoteInterface
(
  std::unique_ptr<Network::Socket>& socket
)
:m_socket(std::move(socket))
{

}


//*****************************************************************************
Controller::RemoteInterface::~RemoteInterface()
{

}


//*****************************************************************************
shared_ptr<ActionMessage::Action> Controller::RemoteInterface::actionSendReply
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

    data.resize(MAX_SIZE);
    if(m_socket->read(data))
    {
      reply = ActionMessage::ActionFactory::messageGenerate(data);
    }
  }

  return reply;
}

#include "Remote/RemoteInterface.h"


#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"

#include <vector>

namespace
{
  const uint16_t MAX_SIZE(500);
}

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


#include <iostream>
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

    data.resize(MAX_SIZE);
    m_socket->read(data);
    std::cout << "got data: ";
    for(uint8_t& next: data)
    {
      std::cout << (char)next;
    }
    std::cout << std::endl;
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

#include "Remote/RemoteInterface.h"


#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"

#include <vector>

//*****************************************************************************
Remote::RemoteInterface::RemoteInterface
(
  const std::string& ip,
  unsigned short port
)
:m_socket(ip, port)
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
  std::unique_ptr<ActionMessage::ActionEncoder> encoder
    = ActionMessage::ActionFactory::encoderGet(nextAction);
  std::vector<uint8_t> data;
  encoder->actionEncode(data);

  m_socket.send(data);
}


//*****************************************************************************
void Remote::RemoteInterface::powerDownSend()
{

}


//*****************************************************************************
void Remote::RemoteInterface::powerUpSend()
{

}

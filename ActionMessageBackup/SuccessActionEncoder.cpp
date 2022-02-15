#include "ActionMessage/SuccessActionEncoder.h"


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
}

//*****************************************************************************
ActionMessage::SuccessActionEncoder::SuccessActionEncoder
(
  SuccessAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::SuccessActionEncoder::~SuccessActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::SuccessActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::SuccessAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::SuccessAction::TYPE_ID;
}

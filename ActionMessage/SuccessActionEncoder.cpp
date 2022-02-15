#include "ActionMessage/SuccessActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::SuccessActionEncoder::SuccessActionEncoder
(
  ActionMessage::SuccessAction* action
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

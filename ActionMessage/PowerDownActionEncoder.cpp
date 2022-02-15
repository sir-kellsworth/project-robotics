#include "ActionMessage/PowerDownActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::PowerDownActionEncoder::PowerDownActionEncoder
(
  ActionMessage::PowerDownAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::PowerDownActionEncoder::~PowerDownActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::PowerDownActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::PowerDownAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::PowerDownAction::TYPE_ID;

}

#include "ActionMessage/FailedActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::FailedActionEncoder::FailedActionEncoder
(
  ActionMessage::FailedAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::FailedActionEncoder::~FailedActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::FailedActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::FailedAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::FailedAction::TYPE_ID;

}

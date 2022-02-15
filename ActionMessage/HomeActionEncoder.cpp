#include "ActionMessage/HomeActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::HomeActionEncoder::HomeActionEncoder
(
  ActionMessage::HomeAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::HomeActionEncoder::~HomeActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::HomeActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::HomeAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::HomeAction::TYPE_ID;

}

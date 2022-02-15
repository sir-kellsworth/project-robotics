#include "ActionMessage/KillActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::KillActionEncoder::KillActionEncoder
(
  ActionMessage::KillAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::KillActionEncoder::~KillActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::KillActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::KillAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::KillAction::TYPE_ID;

}

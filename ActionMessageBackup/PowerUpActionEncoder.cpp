#include "ActionMessage/PowerUpActionEncoder.h"


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
}

//*****************************************************************************
ActionMessage::PowerUpActionEncoder::PowerUpActionEncoder
(
  PowerUpAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::PowerUpActionEncoder::~PowerUpActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::PowerUpActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::PowerUpAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::PowerUpAction::TYPE_ID;
}

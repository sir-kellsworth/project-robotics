#include "ActionMessage/NoActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);

}

//*****************************************************************************
ActionMessage::NoActionEncoder::NoActionEncoder
(
  ActionMessage::NoAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::NoActionEncoder::~NoActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::NoActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::NoAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::NoAction::TYPE_ID;

}

#include "ActionMessage/MoveActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
	const uint16_t INDEX_PARAM_0(2);
	const uint16_t INDEX_PARAM_1(INDEX_PARAM_0 + ActionMessage::MoveAction::SIZE_PARAM_1);
	const uint16_t INDEX_PARAM_2(INDEX_PARAM_1 + ActionMessage::MoveAction::SIZE_PARAM_2);

}

//*****************************************************************************
ActionMessage::MoveActionEncoder::MoveActionEncoder
(
  ActionMessage::MoveAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::MoveActionEncoder::~MoveActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::MoveActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::MoveAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::MoveAction::TYPE_ID;
	uint16_t x = m_action->xGet();
	uint16_t y = m_action->yGet();
	uint16_t z = m_action->zGet();
	memcpy(&data[INDEX_PARAM_0], &x, sizeof(uint16_t));
	memcpy(&data[INDEX_PARAM_1], &y, sizeof(uint16_t));
	memcpy(&data[INDEX_PARAM_2], &z, sizeof(uint16_t));

}

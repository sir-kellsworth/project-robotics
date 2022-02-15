#include "ActionMessage/MoveActionEncoder.h"

#ifdef __linux__
#include <cstring>
#endif


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
	const uint16_t INDEX_PARAM_0(2);
	const uint16_t INDEX_PARAM_1(INDEX_PARAM_0 + sizeof(ActionMessage::MoveAction::SIZE_PARAM_1));
	const uint16_t INDEX_PARAM_2(INDEX_PARAM_1 + sizeof(ActionMessage::MoveAction::SIZE_PARAM_2));

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
	float x = m_action->xGet();
	float y = m_action->yGet();
	float z = m_action->zGet();
	memcpy(&data[INDEX_PARAM_0], &x, sizeof(float));
	memcpy(&data[INDEX_PARAM_1], &y, sizeof(float));
	memcpy(&data[INDEX_PARAM_2], &z, sizeof(float));

}

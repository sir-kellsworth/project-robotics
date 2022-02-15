#include "ActionMessage/MoveAction.h"


const uint8_t ActionMessage::MoveAction::TYPE_ID = 3;
const uint8_t ActionMessage::MoveAction::PACKET_SIZE = 1 + sizeof(float) + sizeof(float) + sizeof(float);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_0 = sizeof(float);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_1 = sizeof(float);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_2 = sizeof(float);


//*****************************************************************************
ActionMessage::MoveAction::MoveAction(
	float x,
	float y,
	float z)
:m_x(x),
m_y(y),
m_z(z)
{

}


//*****************************************************************************
ActionMessage::MoveAction::~MoveAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::MoveAction::messageTypeGet()
{
  return TYPE_ID;
}

//*****************************************************************************
float ActionMessage::MoveAction::xGet()
{
	return m_x;
}

//*****************************************************************************
float ActionMessage::MoveAction::yGet()
{
	return m_y;
}

//*****************************************************************************
float ActionMessage::MoveAction::zGet()
{
	return m_z;
}


//*****************************************************************************
void ActionMessage::MoveAction::xSet
(

	const float& x
)
{
	m_x = x;
}

//*****************************************************************************
void ActionMessage::MoveAction::ySet
(

	const float& y
)
{
	m_y = y;
}

//*****************************************************************************
void ActionMessage::MoveAction::zSet
(

	const float& z
)
{
	m_z = z;
}

#include "ActionMessage/MoveAction.h"


const uint8_t ActionMessage::MoveAction::TYPE_ID = 3;
const uint8_t ActionMessage::MoveAction::PACKET_SIZE = 1 + sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_0 = sizeof(uint16_t);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_1 = sizeof(uint16_t);
const uint8_t ActionMessage::MoveAction::SIZE_PARAM_2 = sizeof(uint16_t);


//*****************************************************************************
ActionMessage::MoveAction::MoveAction(
	uint16_t x,
	uint16_t y,
	uint16_t z)
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
uint16_t ActionMessage::MoveAction::xGet()
{
	return m_x;
}

//*****************************************************************************
uint16_t ActionMessage::MoveAction::yGet()
{
	return m_y;
}

//*****************************************************************************
uint16_t ActionMessage::MoveAction::zGet()
{
	return m_z;
}


//*****************************************************************************
void ActionMessage::MoveAction::xSet
(

	const uint16_t& x
)
{
	m_x = x;
}

//*****************************************************************************
void ActionMessage::MoveAction::ySet
(

	const uint16_t& y
)
{
	m_y = y;
}

//*****************************************************************************
void ActionMessage::MoveAction::zSet
(

	const uint16_t& z
)
{
	m_z = z;
}



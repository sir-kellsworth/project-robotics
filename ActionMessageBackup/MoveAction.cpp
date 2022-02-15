#include "ActionMessage/MoveAction.h"


const uint8_t ActionMessage::MoveAction::TYPE_ID = 0x3;
const uint8_t ActionMessage::MoveAction::PACKET_SIZE = 13;

//*****************************************************************************
ActionMessage::MoveAction::MoveAction
(
	const Pathing::Point& point
)
:m_point(point)
{

}


//*****************************************************************************
ActionMessage::MoveAction::~MoveAction()
{

}

//*****************************************************************************
Pathing::Point ActionMessage::MoveAction::pointGet()
{
	return m_point;
}


//*****************************************************************************
void ActionMessage::MoveAction::pointSet
(

	const Pathing::Point& point
)
{
	m_point = point;
}

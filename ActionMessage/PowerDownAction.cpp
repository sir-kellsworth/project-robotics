#include "ActionMessage/PowerDownAction.h"


const uint8_t ActionMessage::PowerDownAction::TYPE_ID = 5;
const uint8_t ActionMessage::PowerDownAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::PowerDownAction::PowerDownAction()

{

}


//*****************************************************************************
ActionMessage::PowerDownAction::~PowerDownAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::PowerDownAction::messageTypeGet()
{
  return TYPE_ID;
}




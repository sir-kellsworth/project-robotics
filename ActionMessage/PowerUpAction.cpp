#include "ActionMessage/PowerUpAction.h"


const uint8_t ActionMessage::PowerUpAction::TYPE_ID = 6;
const uint8_t ActionMessage::PowerUpAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::PowerUpAction::PowerUpAction()

{

}


//*****************************************************************************
ActionMessage::PowerUpAction::~PowerUpAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::PowerUpAction::messageTypeGet()
{
  return TYPE_ID;
}




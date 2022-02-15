#include "ActionMessage/NoAction.h"


const uint8_t ActionMessage::NoAction::TYPE_ID = 4;
const uint8_t ActionMessage::NoAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::NoAction::NoAction()

{

}


//*****************************************************************************
ActionMessage::NoAction::~NoAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::NoAction::messageTypeGet()
{
  return TYPE_ID;
}




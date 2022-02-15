#include "ActionMessage/KillAction.h"


const uint8_t ActionMessage::KillAction::TYPE_ID = 2;
const uint8_t ActionMessage::KillAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::KillAction::KillAction()

{

}


//*****************************************************************************
ActionMessage::KillAction::~KillAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::KillAction::messageTypeGet()
{
  return TYPE_ID;
}




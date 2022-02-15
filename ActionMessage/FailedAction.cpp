#include "ActionMessage/FailedAction.h"


const uint8_t ActionMessage::FailedAction::TYPE_ID = 0;
const uint8_t ActionMessage::FailedAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::FailedAction::FailedAction()

{

}


//*****************************************************************************
ActionMessage::FailedAction::~FailedAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::FailedAction::messageTypeGet()
{
  return TYPE_ID;
}




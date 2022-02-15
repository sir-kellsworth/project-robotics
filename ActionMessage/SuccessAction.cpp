#include "ActionMessage/SuccessAction.h"


const uint8_t ActionMessage::SuccessAction::TYPE_ID = 7;
const uint8_t ActionMessage::SuccessAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::SuccessAction::SuccessAction()

{

}


//*****************************************************************************
ActionMessage::SuccessAction::~SuccessAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::SuccessAction::messageTypeGet()
{
  return TYPE_ID;
}




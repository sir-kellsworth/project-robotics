#include "ActionMessage/HomeAction.h"


const uint8_t ActionMessage::HomeAction::TYPE_ID = 1;
const uint8_t ActionMessage::HomeAction::PACKET_SIZE = 1;


//*****************************************************************************
ActionMessage::HomeAction::HomeAction()

{

}


//*****************************************************************************
ActionMessage::HomeAction::~HomeAction()
{

}


//*****************************************************************************
uint8_t ActionMessage::HomeAction::messageTypeGet()
{
  return TYPE_ID;
}




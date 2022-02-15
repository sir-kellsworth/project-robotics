#include "RemoteInterface.h"

#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "ActionMessage/MoveAction.h"

#include <Arduino.h>


//*****************************************************************
RemoteInterface::RemoteInterface
(
  RoboticArm& arm
)
:m_arm(arm)
{
  Serial.begin(115200);
}


//*****************************************************************
RemoteInterface::~RemoteInterface()
{

}


//*****************************************************************
bool RemoteInterface::actionGet
(
  unique_ptr<ActionMessage::Action>& nextAction
)
{
  bool success(false);
  if(Serial.available() > 0)
  {
    vector<uint8_t> data(20);
    uint8_t i(0);
    while(Serial.available() > 0)
    {
      data[i] = Serial.read();
    }
    nextAction = ActionMessage::ActionFactory::messageGenerate(data);
    success = true;
  }

  return success;
}


//*****************************************************************
void RemoteInterface::moveHandle
(
  unique_ptr<ActionMessage::MoveAction> moveAction
)
{
  
}


//*****************************************************************
void RemoteInterface::step()
{
  unique_ptr<ActionMessage::Action> nextAction;

  if(actionGet(nextAction))
  {
    if(nextAction->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
    {
      unique_ptr<ActionMessage::MoveAction> move =
        unique_ptr<ActionMessage::MoveAction>(
          (ActionMessage::MoveAction*)nextAction.get());

      moveHandle(move);
    }
  }
}

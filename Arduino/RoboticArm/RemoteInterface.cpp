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
  shared_ptr<ActionMessage::Action>& nextAction
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
    shared_ptr<ActionMessage::Action> test(
      ActionMessage::ActionFactory::messageGenerate(data).get());
    success = true;
  }

  return success;
}


//*****************************************************************
void RemoteInterface::step()
{
  shared_ptr<ActionMessage::Action> nextAction;

  if(actionGet(nextAction))
  {
    m_arm.actionSend(nextAction);
  }
}

#include "RoboticArm.h"
#include "RemoteInterface.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"

#include <Arduino.h>


namespace
{
    const uint8_t baseStepPin      (4);
    const uint8_t baseDirPin       (5);
    const uint8_t shoulderStepPin  (6);
    const uint8_t shoulderDirPin   (7);
    const uint8_t elbowStepPin     (8);
    const uint8_t elbowDirPin      (9);
    const uint16_t armLength       (100);
    const uint16_t forarmLength    (100);
    const Pathing::Point homePoint (0, 0, 30);
    const Pathing::Point startPoint(0, 0, 30);
};

RoboticArm arm(
  baseStepPin,
  baseDirPin,
  shoulderStepPin,
  shoulderDirPin,
  elbowStepPin,
  elbowDirPin,
  armLength,
  forarmLength,
  homePoint,
  startPoint);
RemoteInterface interface(arm);


//*****************************************************************************
void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(100);
}


//*****************************************************************************
void loop()
{
  shared_ptr<ActionMessage::Action> nextAction;

  if(interface.actionGet(nextAction))
  {
    Serial.print("got_action");
    Serial.flush();
    shared_ptr<ActionMessage::Action> response = arm.actionSendReply(nextAction);

    vector<uint8_t> data;
    unique_ptr<ActionMessage::ActionEncoder> encoder
      = ActionMessage::ActionFactory::encoderGet(response);
    encoder->actionEncode(data);

    //Serial.write(data.data(), data.size());
    //Serial.flush();
  }

  arm.step();
}

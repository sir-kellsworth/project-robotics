#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "RemoteInterface.h"
#include "RoboticArm.h"
#include "SerialLogger.h"

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
RemoteInterface interface;


//*****************************************************************************
void setup()
{
  Serial.begin(115200);

  LOGGER_DEBUG("arduino started");
}


//*****************************************************************************
void loop()
{
  shared_ptr<ActionMessage::Action> nextAction;

  if(interface.actionGet(nextAction))
  {
    LOGGER_DEBUG("got action");
    shared_ptr<ActionMessage::Action> response = arm.actionSendReply(nextAction);
    LOGGER_DEBUG("got response");

    interface.send(response);
  }

  interface.step();
  arm.step();
}

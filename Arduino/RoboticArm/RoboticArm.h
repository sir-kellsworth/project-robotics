#ifndef ROBOTIC_ARM_H
#define ROBOTIC_ARM_H

#include "ActionMessage/MoveAction.h"
#include "ControlInterface/Device.h"
#include "Pathing/Point.h"

#include "AccelStepper.h"

class RoboticArm : public ControlInterface::Device
{
public:
  RoboticArm();

  virtual ~RoboticArm();

  virtual void actionSend(
    shared_ptr<ActionMessage::Action> action);

  void step();

  virtual void powerDownSend();

  virtual void powerUpSend();
private:
  bool anglesValidate(
    float baseAngle,
    float shoulderAngle,
    float elbowAngle);

  void moveHandle(
    ActionMessage::MoveAction* moveAction);

    void moveTo(
      Pathing::Point goal);

  AccelStepper m_baseMotor;
  AccelStepper m_shoulderMotor;
  AccelStepper m_elbowMotor;

  uint32_t m_armLength;
  uint32_t m_forarmLength;

  Pathing::Point m_home;
  Pathing::Point m_currentPosition;
};

#endif

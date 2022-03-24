#ifndef ROBOTIC_ARM_H
#define ROBOTIC_ARM_H

#include "ActionMessage/MoveAction.h"
#include "ControlInterface/Device.h"
#include "Pathing/Point.h"
#include "Utils/Queue.h"
#include "Utils/memory.h"

#include "AccelStepper.h"

class RoboticArm : public ControlInterface::Device
{
public:
  RoboticArm(
    uint8_t baseStepPin,
    uint8_t baseDirPin,
    uint8_t shoulderStepPin,
    uint8_t shoulderDirPin,
    uint8_t elbowStepPin,
    uint8_t elbowDirPin,
    uint16_t armLength,
    uint16_t forarmLength,
    Pathing::Point homePoint,
    Pathing::Point startPoint);

  virtual ~RoboticArm();

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    shared_ptr<ActionMessage::Action> action);

  unique_ptr<ActionMessage::Action> actionSendReply(
    unique_ptr<ActionMessage::Action> action);

  void step();

  void powerDown();

  void powerUp();
private:
  bool anglesValidate(
    float baseAngle,
    float shoulderAngle,
    float elbowAngle);

  unique_ptr<ActionMessage::Action> moveHandle(
    ActionMessage::MoveAction* moveAction);

  unique_ptr<ActionMessage::Action> moveTo(
    Pathing::Point goal);

  AccelStepper m_baseMotor;
  AccelStepper m_shoulderMotor;
  AccelStepper m_elbowMotor;

  float m_baseAngleMax;
  float m_baseAngleMin;
  float m_shoulderAngleMax;
  float m_shoulderAngleMin;
  float m_elbowAngleMax;
  float m_elbowAngleMin;

  uint32_t m_armLength;
  uint32_t m_forarmLength;

  Pathing::Point m_home;
  Pathing::Point m_currentPosition;
};

#endif

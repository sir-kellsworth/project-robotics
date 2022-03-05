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

  virtual void actionSend(
    shared_ptr<ActionMessage::Action> action);

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    shared_ptr<ActionMessage::Action> action);

  void step();

  virtual void powerDownSend();

  virtual void powerUpSend();
private:
  bool anglesValidate(
    float baseAngle,
    float shoulderAngle,
    float elbowAngle);

  //void messageSend(
  //  const unique_ptr<ActionMessage::Action>& response);

  shared_ptr<ActionMessage::Action> moveHandle(
    ActionMessage::MoveAction* moveAction);

  shared_ptr<ActionMessage::Action> moveTo(
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

  Utils::Queue<ActionMessage::Action> m_actionQueue;
};

#endif

#include "RoboticArm.h"

#include "Utils/TrigEquations.h"


namespace
{
  const uint16_t STEPPER_SPEED_MAX(1000);
  const uint16_t STEPPER_SPEED_DEFAULT(400);
  const float DEGREE_STEPS(1.8);
}

//*****************************************************************************
RoboticArm::RoboticArm
(
  uint8_t baseStepPin,
  uint8_t baseDirPin,
  uint8_t shoulderStepPin,
  uint8_t shoulderDirPin,
  uint8_t elbowStepPin,
  uint8_t elbowDirPin,
  uint16_t armLength,
  uint16_t forarmLength,
  Pathing::Point homePoint,
  Pathing::Point startPoint
)
:m_baseMotor(AccelStepper::DRIVER, baseStepPin, baseDirPin),
 m_shoulderMotor(AccelStepper::DRIVER, shoulderStepPin, shoulderDirPin),
 m_elbowMotor(AccelStepper::DRIVER, elbowStepPin, elbowDirPin),
 m_armLength(armLength),
 m_forarmLength(forarmLength),
 m_home(homePoint),
 m_currentPosition(startPoint)
{
  m_baseMotor.setMaxSpeed(STEPPER_SPEED_MAX);
  m_shoulderMotor.setMaxSpeed(STEPPER_SPEED_MAX);
  m_elbowMotor.setMaxSpeed(STEPPER_SPEED_MAX);

  //for now use a const speed. Eventually, this will be set by the controller
  m_baseMotor.setSpeed(STEPPER_SPEED_DEFAULT);
  m_shoulderMotor.setSpeed(STEPPER_SPEED_DEFAULT);
  m_elbowMotor.setSpeed(STEPPER_SPEED_DEFAULT);
}


//*****************************************************************************
RoboticArm::~RoboticArm()
{

}


//*****************************************************************************
void RoboticArm::actionSend
(
  shared_ptr<ActionMessage::Action> action
)
{
  m_queue.push(action);
}


//*****************************************************************************
bool RoboticArm::anglesValidate
(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle
)
{
  return Utils::boundsCheck(baseAngle, m_baseAngleMin, m_baseAngleMax) \
    && Utils::boundsCheck(shoulderAngle, m_shoulderAngleMin, m_shoulderAngleMax) \
    && Utils::boundsCheck(elbowAngle, m_elbowAngleMin, m_elbowAngleMax);
}


//*****************************************************************
void RoboticArm::moveHandle
(
  ActionMessage::MoveAction* moveAction
)
{
  Pathing::Point goal(
    moveAction->xGet(),
    moveAction->yGet(),
    moveAction->zGet());

    if(goal.xGet() == Utils::NO_MOVEMENT)
    {
      goal.xSet(m_currentPosition.xGet());
    }
    if(goal.yGet() == Utils::NO_MOVEMENT)
    {
      goal.ySet(m_currentPosition.yGet());
    }
    if(goal.zGet() == Utils::NO_MOVEMENT)
    {
      goal.zSet(m_currentPosition.zGet());
    }

    moveTo(goal);
}


//*****************************************************************
void RoboticArm::moveTo
(
  Pathing::Point goal
)
{
  float baseAngle(0);
  float shoulderAngle(0);
  float elbowAngle(0);
  Utils::anglesCalculate(
    goal.xGet(),
    goal.yGet(),
    goal.zGet(),
    m_armLength,
    m_forarmLength,
    baseAngle,
    shoulderAngle,
    elbowAngle);

  //if any of these are invalid, then the angle is outside of the
  //physical bounds of the arm. Set in the config file
  bool validAngle = anglesValidate(baseAngle, shoulderAngle, elbowAngle);

  if(validAngle)
  {
    uint16_t basePosition(0);
    uint16_t shoulderPosition(0);
    uint16_t elbowPosition(0);

    Utils::stepperPositionCalculate(
      baseAngle,
      shoulderAngle,
      elbowAngle,
      DEGREE_STEPS,
      basePosition,
      shoulderPosition,
      elbowPosition);

    m_baseMotor.moveTo(basePosition);
    m_shoulderMotor.moveTo(shoulderPosition);
    m_elbowMotor.moveTo(elbowPosition);
  }
}


//*****************************************************************************
void RoboticArm::step()
{
  shared_ptr<ActionMessage::Action> action = m_queue.pop();
  if(action.get() != 0)
  {
    if(action->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
    {
      ActionMessage::MoveAction* move =
          (ActionMessage::MoveAction*)action.get();

      moveHandle(move);
    }
  }
  //eventually, acceleration will be enabled. But for now, only use const speeds
  //to use acceleration, use .run() instead
  m_baseMotor.runSpeed();
  m_shoulderMotor.runSpeed();
  m_elbowMotor.runSpeed();
}


//*****************************************************************************
void RoboticArm::powerDownSend()
{
  m_baseMotor.disableOutputs();
  m_shoulderMotor.disableOutputs();
  m_elbowMotor.disableOutputs();
}


//*****************************************************************************
void RoboticArm::powerUpSend()
{
  m_baseMotor.enableOutputs();
  m_shoulderMotor.enableOutputs();
  m_elbowMotor.enableOutputs();
}

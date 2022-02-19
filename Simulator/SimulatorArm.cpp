#include "Simulator/SimulatorArm.h"

#include "ActionMessage/HomeAction.h"
#include "ActionMessage/KillAction.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerUpAction.h"
#include "Utils/TrigEquations.h"


#include <iostream>
#include <unistd.h>
#include <vector>

namespace
{
  const float NO_MOVEMENT(-1);
  const uint32_t SLEEP_TIME_US(100);
  const uint32_t NUM_POINTS_DEFAULT(10);
}


//*****************************************************************************
Simulator::SimulatorArm::SimulatorArm
(
  Pathing::Point home,
  Pathing::Point start,
  uint32_t armLength,
  uint32_t forarmLength,
  std::shared_ptr<Simulator::SimulatorMotor> baseMotor,
  std::shared_ptr<Simulator::SimulatorMotor> shoulderMotor,
  std::shared_ptr<Simulator::SimulatorMotor> elbowMotor
)
:m_baseMotor(baseMotor),
 m_shoulderMotor(shoulderMotor),
 m_elbowMotor(elbowMotor),
 m_armLength(armLength),
 m_forarmLength(forarmLength),
 m_running(true),
 m_backgroundThread(&Simulator::SimulatorArm::backgroundHandle, this),
 m_home(home),
 m_currentPosition(start)
{

}


//*****************************************************************************
Simulator::SimulatorArm::~SimulatorArm()
{
  m_queue.push(std::shared_ptr<ActionMessage::KillAction>(new ActionMessage::KillAction));
  m_backgroundThread.join();
}


//*****************************************************************************
void Simulator::SimulatorArm::actionSend
(
  std::shared_ptr<ActionMessage::Action> nextAction
)
{
  m_queue.push(nextAction);
}


//*****************************************************************************
//This function should not be used
shared_ptr<ActionMessage::Action> Simulator::SimulatorArm::actionSendReply
(
  shared_ptr<ActionMessage::Action> action
)
{
  return shared_ptr<ActionMessage::Action>();
}


//*****************************************************************************
void Simulator::SimulatorArm::anglesPrint()
{
  std::cout << "angles: " << std::endl;
  std::cout << "\tbaseAngle: " << m_baseMotor->angleGet() << std::endl;
  std::cout << "\tshoulderAngle: " << m_shoulderMotor->angleGet() << std::endl;
  std::cout << "\telbowAngle: " << m_elbowMotor->angleGet() << std::endl;
}


//*****************************************************************************
void Simulator::SimulatorArm::backgroundHandle()
{
  while(m_running)
  {
    std::shared_ptr<ActionMessage::Action> action = m_queue.pop();
    if(action->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
    {
      std::shared_ptr<ActionMessage::MoveAction> move =
        std::dynamic_pointer_cast<ActionMessage::MoveAction>(action);
      moveHandle(move);
    }
    else if(action->messageTypeGet() == ActionMessage::HomeAction::TYPE_ID)
    {
      std::shared_ptr<ActionMessage::MoveAction> home =
        std::shared_ptr<ActionMessage::MoveAction>(
          new ActionMessage::MoveAction(
            m_home.xGet(),
            m_home.yGet(),
            m_home.zGet()));

      moveHandle(home);
    }
    else if(action->messageTypeGet() == ActionMessage::PowerDownAction::TYPE_ID)
    {
      powerDown();
    }
    else if(action->messageTypeGet() == ActionMessage::PowerUpAction::TYPE_ID)
    {
      powerUp();
    }
    else if(action->messageTypeGet() == ActionMessage::KillAction::TYPE_ID)
    {
      m_running = false;
    }
  }
}


//*****************************************************************************
void Simulator::SimulatorArm::moveHandle
(
  std::shared_ptr<ActionMessage::MoveAction> moveAction
)
{
  Pathing::Point goalPoint(
    moveAction->xGet(),
    moveAction->yGet(),
    moveAction->zGet());
  std::cout << "moving to goal" << std::endl;

  /*Pathing::Path path = Pathing::straightPathGenerate(
    m_currentPosition,
    goalPoint);//,
    //NUM_POINTS_DEFAULT);*/

  /*for(const Pathing::Point& next : path)
  {
    std::cout << "next: " << next.xGet() << " " << next.yGet() << " " << next.zGet() << std::endl;
    moveTo(next);
  }*/
  moveTo(goalPoint);
}


//*****************************************************************************
void Simulator::SimulatorArm::moveTo
(
  Pathing::Point goal
)
{
  std::cout << goal.xGet() << " " << goal.yGet() << " " << goal.zGet() << std::endl;

  if(goal.xGet() == NO_MOVEMENT)
  {
    goal.xSet(m_currentPosition.xGet());
  }
  if(goal.yGet() == NO_MOVEMENT)
  {
    goal.ySet(m_currentPosition.yGet());
  }
  if(goal.zGet() == NO_MOVEMENT)
  {
    goal.zSet(m_currentPosition.zGet());
  }

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
  bool validAngle = m_baseMotor->angleSet(baseAngle) &&
    m_shoulderMotor->angleSet(shoulderAngle) &&
    m_elbowMotor->angleSet(elbowAngle);

  if(validAngle)
  {
    bool angleMatch(false);
    while(!angleMatch)
    {
      baseAngle = m_baseMotor->nextAngleGet(SLEEP_TIME_US);
      shoulderAngle = m_shoulderMotor->nextAngleGet(SLEEP_TIME_US);
      elbowAngle = m_elbowMotor->nextAngleGet(SLEEP_TIME_US);

      // tests the next angle location. If any of the angles are invalid
      // or if a position is invalid, it updates ti
      float newX;
      float newY;
      float newZ;
      Utils::positionCalculate(
        baseAngle,
        shoulderAngle,
        elbowAngle,
        m_armLength,
        m_forarmLength,
        newX,
        newY,
        newZ);
      Pathing::Point nextPosition = Pathing::Point(newX, newY, newZ);
      if(!nextPosition.valid())
      {
        std::cout << "position impossible. Bailing." << std::endl;
        std::cout << newX << " " << newY << " " << newZ << std::endl;
        angleMatch = true;
      }
      else
      {
        m_baseMotor->step(SLEEP_TIME_US);
        m_shoulderMotor->step(SLEEP_TIME_US);
        m_elbowMotor->step(SLEEP_TIME_US);

        angleMatch = m_baseMotor->angleMatch() &&
          m_shoulderMotor->angleMatch() &&
          m_elbowMotor->angleMatch();
          m_currentPosition = nextPosition;

        anglesPrint();
        positionPrint();

        usleep(1000);
        //usleep(SLEEP_TIME_US);
      }
    }
  }
  else
  {
    std::cout << "Angle outside of valid area" << std::endl;
    std::cout << baseAngle << " " << shoulderAngle << " " << elbowAngle << std::endl;
  }
}


//*****************************************************************************
void Simulator::SimulatorArm::positionPrint()
{
  std::cout << "position: " << std::endl;
  std::cout << "\tx: " << m_currentPosition.xGet() << std::endl;
  std::cout << "\ty: " << m_currentPosition.yGet() << std::endl;
  std::cout << "\tz: " << m_currentPosition.zGet() << std::endl;
}


//*****************************************************************************
void Simulator::SimulatorArm::powerDown()
{
  m_baseMotor->powerDown();
  m_shoulderMotor->powerDown();
  m_elbowMotor->powerDown();
}


//*****************************************************************************
void Simulator::SimulatorArm::powerUp()
{
  m_baseMotor->powerUp();
  m_shoulderMotor->powerUp();
  m_elbowMotor->powerUp();
}


//*****************************************************************************
void Simulator::SimulatorArm::powerDownSend()
{
  m_queue.push(std::shared_ptr<ActionMessage::PowerDownAction>(new ActionMessage::PowerDownAction));
}


//*****************************************************************************
void Simulator::SimulatorArm::powerUpSend()
{
  m_queue.push(std::shared_ptr<ActionMessage::PowerUpAction>(new ActionMessage::PowerUpAction));
}

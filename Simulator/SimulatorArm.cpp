#include "Simulator/SimulatorArm.h"

#include "ActionMessage/HomeAction.h"
#include "ActionMessage/KillAction.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerUpAction.h"
#include "ActionMessage/SuccessAction.h"
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
template<typename T>
Simulator::SimulatorArm<T>::SimulatorArm
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
 m_backgroundThread(&Simulator::SimulatorArm<T>::backgroundHandle, this),
 m_home(home),
 m_currentPosition(start)
{

}


//*****************************************************************************
template<typename T>
Simulator::SimulatorArm<T>::~SimulatorArm()
{
  m_queue.push(std::shared_ptr<ActionMessage::KillAction>(new ActionMessage::KillAction));
  m_backgroundThread.join();
}


//*****************************************************************************
//This function should not be used
template<typename T>
void Simulator::SimulatorArm<T>::actionSend
(
  std::shared_ptr<ActionMessage::Action> nextAction
)
{
  m_queue.push(nextAction);
}


//*****************************************************************************
template<typename T>
shared_ptr<ActionMessage::Action> Simulator::SimulatorArm<T>::actionSendReply
(
  shared_ptr<ActionMessage::Action> nextAction
)
{
  m_queue.push(nextAction);

  //wait for action to finish
  m_actionWaitSemaphore.wait();

  return m_reply;
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::anglesPrint()
{
  std::cout << "angles: " << std::endl;
  std::cout << "\tbaseAngle: " << m_baseMotor->angleGet() << std::endl;
  std::cout << "\tshoulderAngle: " << m_shoulderMotor->angleGet() << std::endl;
  std::cout << "\telbowAngle: " << m_elbowMotor->angleGet() << std::endl;
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::backgroundHandle()
{
  while(m_running)
  {
    std::shared_ptr<ActionMessage::Action> action = m_queue.pop();
    if(action->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
    {
      std::shared_ptr<ActionMessage::MoveAction> move =
        std::dynamic_pointer_cast<ActionMessage::MoveAction>(action);
      moveHandle(move);

      m_reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
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

      m_reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
    }
    else if(action->messageTypeGet() == ActionMessage::PowerUpAction::TYPE_ID)
    {
      powerUp();

      m_reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
    }
    else if(action->messageTypeGet() == ActionMessage::KillAction::TYPE_ID)
    {
      m_running = false;

      m_reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
    }

    m_actionWaitSemaphore.signal();
  }
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::moveHandle
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
template<typename T>
void Simulator::SimulatorArm<T>::moveTo
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
  bool validAngle = m_baseMotor->angleSet(baseAngle)
    && m_shoulderMotor->angleSet(shoulderAngle)
    && m_elbowMotor->angleSet(elbowAngle);

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
template<typename T>
void Simulator::SimulatorArm<T>::positionPrint()
{
  std::cout << "position: " << std::endl;
  std::cout << "\tx: " << m_currentPosition.xGet() << std::endl;
  std::cout << "\ty: " << m_currentPosition.yGet() << std::endl;
  std::cout << "\tz: " << m_currentPosition.zGet() << std::endl;
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::powerDown()
{
  m_baseMotor->powerDown();
  m_shoulderMotor->powerDown();
  m_elbowMotor->powerDown();
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::powerUp()
{
  m_baseMotor->powerUp();
  m_shoulderMotor->powerUp();
  m_elbowMotor->powerUp();
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::powerDownSend()
{
  m_queue.push(std::shared_ptr<ActionMessage::PowerDownAction>(new ActionMessage::PowerDownAction));
}


//*****************************************************************************
template<typename T>
void Simulator::SimulatorArm<T>::powerUpSend()
{
  m_queue.push(std::shared_ptr<ActionMessage::PowerUpAction>(new ActionMessage::PowerUpAction));
}


// forward declaration trick to allow separate template h/cpp files
template class Simulator::SimulatorArm<float>;
template class Simulator::SimulatorArm<Fix16>;

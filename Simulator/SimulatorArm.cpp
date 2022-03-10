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
 m_home(home),
 m_currentPosition(start)
{

}


//*****************************************************************************
template<typename T>
Simulator::SimulatorArm<T>::~SimulatorArm()
{

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
void Simulator::SimulatorArm<T>::home()
{
  moveTo(m_home);
}


//*****************************************************************************
template<typename T>
const Pathing::Point& Simulator::SimulatorArm<T>::moveTo
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

  return m_currentPosition;
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


// forward declaration trick to allow separate template h/cpp files
template class Simulator::SimulatorArm<float>;
template class Simulator::SimulatorArm<Fix16>;

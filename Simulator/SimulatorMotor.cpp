#include "Simulator/SimulatorMotor.h"

#include <iostream>
#include <math.h>

namespace
{
  const float ANGLE_PRESISION(1e-1);
  const float MICRO_SECONDS(1e-6);


  //***************************************************************************
  bool about
  (
    float angle,
    float current,
    float presision
  )
  {
    return std::abs(angle - current) < presision;
  }


  //***************************************************************************
  uint32_t posGet
  (
    float angle,
    float minAngle,
    float maxAngle,
    uint32_t minPos,
    uint32_t maxPos
  )
  {
    float tmp = (angle - minAngle) / (minAngle - maxAngle);
    return static_cast<uint32_t>(angle * (minPos - maxPos) + minPos);
  }
}

//*****************************************************************************
Simulator::SimulatorMotor::SimulatorMotor
(
  float startAngle,
  float minAngle,
  float maxAngle,
  float speed
)
:m_minAngle(minAngle),
 m_maxAngle(maxAngle),
 m_currentAngle(startAngle),
 m_speed(speed)
{

}


//*****************************************************************************
Simulator::SimulatorMotor::~SimulatorMotor()
{

}


//*****************************************************************************
float Simulator::SimulatorMotor::angleGet()
{
  return m_currentAngle;
}


//*****************************************************************************
bool Simulator::SimulatorMotor::angleMatch()
{
  return about(m_angle, m_currentAngle, ANGLE_PRESISION);
}


//*****************************************************************************
bool Simulator::SimulatorMotor::angleSet
(
  float angle
)
{
  bool success(false);
  if(angle <= m_maxAngle && angle >= m_minAngle)
  {
    m_angle = angle;
    success = true;
  }

  return success;
}


//***************************************************************************
float Simulator::SimulatorMotor::nextAngleGet
(
  uint32_t timeStep_us
)
{
  float direction = m_angle > m_currentAngle ? 1 : -1;
  float timeStep = timeStep_us * MICRO_SECONDS;
  return m_currentAngle + direction * m_speed * timeStep;
}


//*****************************************************************************
void Simulator::SimulatorMotor::powerDown()
{
  m_powered = false;
}


//*****************************************************************************
void Simulator::SimulatorMotor::powerUp()
{
  m_powered = true;
}


//*****************************************************************************
bool Simulator::SimulatorMotor::step
(
  uint32_t timeStep_us
)
{
  bool success(false);
  if(!m_powered)
  {
    if(!angleMatch())
    {
      m_currentAngle = nextAngleGet(timeStep_us);
    }

    success = true;
  }
  else
  {
    std::cout << "failed to step. Motor powered off." << std::endl;
  }

  return success;
}

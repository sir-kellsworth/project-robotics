#ifndef SIMULATOR_SIMULATORMOTOR_H
#define SIMULATOR_SIMULATORMOTOR_H

#include <atomic>
#include <cstdint>

namespace Simulator
{

class SimulatorMotor
{
public:
  SimulatorMotor(
    float startAngle,
    float minAngle,
    float maxAngle,
    float speed);

  ~SimulatorMotor();

  float angleGet();

  bool angleMatch();

  bool angleSet(
    float angle);

  float nextAngleGet(
    uint32_t timeStep_us);

  void powerDown();

  void powerUp();

  bool testStep(
    uint32_t timeStep);

  bool step(
    uint32_t timeStep);
private:
  float m_minAngle;
  float m_maxAngle;
  float m_angle;
  float m_currentAngle;
  uint32_t m_speed;
  std::atomic<bool> m_powered;
};

}

#endif

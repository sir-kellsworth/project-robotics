#ifndef SIMULATOR_SIMULATORARM_H
#define SIMULATOR_SIMULATORARM_H

#include "Simulator/SimulatorMotor.h"
#include "Pathing/Point.h"

#include <queue>
#include <thread>

namespace Simulator
{

template <typename T>
class SimulatorArm
{
public:
  SimulatorArm(
    Pathing::Point home,
    Pathing::Point start,
    uint32_t armLength,
    uint32_t forarmLength,
    std::shared_ptr<Simulator::SimulatorMotor> baseMotor,
    std::shared_ptr<Simulator::SimulatorMotor> shoulderMotor,
    std::shared_ptr<Simulator::SimulatorMotor> elbowMotor);

  virtual ~SimulatorArm();

  void anglesPrint();

  void home();

    const Pathing::Point& moveTo(
      Pathing::Point goal);

  void positionPrint();

  void powerDown();

  void powerUp();

private:
  std::shared_ptr<Simulator::SimulatorMotor> m_baseMotor;
  std::shared_ptr<Simulator::SimulatorMotor> m_shoulderMotor;
  std::shared_ptr<Simulator::SimulatorMotor> m_elbowMotor;

  uint32_t m_armLength;
  uint32_t m_forarmLength;
  Pathing::Point m_home;
  Pathing::Point m_currentPosition;
};

}

#endif

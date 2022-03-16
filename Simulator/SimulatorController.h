#ifndef SIMULATOR_SIMULATORCONTROLLER_H
#define SIMULATOR_SIMULATORCONTROLLER_H

#include "Simulator/SimulatorArm.h"
#include "Simulator/SimulatorMotor.h"
#include "ControlInterface/Device.h"

#include "fix16.h"
#include <memory>

namespace Simulator
{

class SimulatorController : public ControlInterface::Device
{
public:
  SimulatorController(
    Pathing::Point home,
    Pathing::Point start,
    uint32_t armLength,
    uint32_t forarmLength,
    std::shared_ptr<Simulator::SimulatorMotor> baseMotor,
    std::shared_ptr<Simulator::SimulatorMotor> shoulderMotor,
    std::shared_ptr<Simulator::SimulatorMotor> elbowMotor);

  virtual ~SimulatorController();

  bool about(
    const Pathing::Point& a,
    const Pathing::Point& b);

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    shared_ptr<ActionMessage::Action> action);
private:
  Simulator::SimulatorArm<float> m_masterSimulator;
  Simulator::SimulatorArm<Fix16> m_testerSimulator;
};

}

#endif

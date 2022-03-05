#ifndef SIMULATOR_SIMULATORARM_H
#define SIMULATOR_SIMULATORARM_H

#include "ActionMessage/MoveAction.h"
#include "ControlInterface/Device.h"
#include "Utils/SafeQueue.h"
#include "Simulator/SimulatorMotor.h"
#include "Pathing/Point.h"

#include <queue>
#include <thread>

namespace Simulator
{

class SimulatorArm : public ControlInterface::Device
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

  virtual void actionSend(
    std::shared_ptr<ActionMessage::Action> nextAction);

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    shared_ptr<ActionMessage::Action> action);

  virtual void powerDownSend();

  virtual void powerUpSend();
private:
  void anglesPrint();

  void backgroundHandle();

  void home();

  void moveHandle(
    std::shared_ptr<ActionMessage::MoveAction> moveAction);

    void moveTo(
      Pathing::Point goal);

  void positionPrint();

  void powerDown();

  void powerUp();

  std::shared_ptr<Simulator::SimulatorMotor> m_baseMotor;
  std::shared_ptr<Simulator::SimulatorMotor> m_shoulderMotor;
  std::shared_ptr<Simulator::SimulatorMotor> m_elbowMotor;

  uint32_t m_armLength;
  uint32_t m_forarmLength;
  bool m_running;
  std::thread m_backgroundThread;
  Utils::SafeQueue<std::shared_ptr<ActionMessage::Action>> m_queue;
  Pathing::Point m_home;
  Pathing::Point m_currentPosition;
};

}

#endif

#include "Simulator/SimulatorController.h"

#include "ActionMessage/FailedAction.h"
#include "ActionMessage/HomeAction.h"
#include "ActionMessage/KillAction.h"
#include "ActionMessage/MoveAction.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerUpAction.h"
#include "ActionMessage/SuccessAction.h"

#include <iostream>


namespace
{
    const float ERROR_MARGIN(0.1);

    bool within
    (
      float a,
      float b,
      float margin
    )
    {
      return std::abs(a - b) < margin;
    }
};


//*****************************************************************************
Simulator::SimulatorController::SimulatorController
(
  Pathing::Point home,
  Pathing::Point start,
  uint32_t armLength_mm,
  uint32_t forarmLength_mm,
  std::shared_ptr<Simulator::SimulatorMotor> baseMotor,
  std::shared_ptr<Simulator::SimulatorMotor> shoulderMotor,
  std::shared_ptr<Simulator::SimulatorMotor> elbowMotor
)
:m_masterSimulator(
  home,
  start,
  armLength_mm,
  forarmLength_mm,
  baseMotor,
  shoulderMotor,
  elbowMotor),
 m_testerSimulator(
   home,
   start,
   armLength_mm,
   forarmLength_mm,
   baseMotor,
   shoulderMotor,
   elbowMotor)
{

}


//*****************************************************************************
Simulator::SimulatorController::~SimulatorController()
{

}


//*****************************************************************************
bool Simulator::SimulatorController::about
(
  const Pathing::Point& a,
  const Pathing::Point& b
)
{
  return within(a.xGet(), b.xGet(), ERROR_MARGIN)
    && within(a.yGet(), b.yGet(), ERROR_MARGIN)
    && within(a.zGet(), b.zGet(), ERROR_MARGIN);
}


//*****************************************************************************
void Simulator::SimulatorController::actionSend
(
  std::shared_ptr<ActionMessage::Action> nextAction
)
{

}


//*****************************************************************************
shared_ptr<ActionMessage::Action> Simulator::SimulatorController::actionSendReply
(
  shared_ptr<ActionMessage::Action> action
)
{
  shared_ptr<ActionMessage::Action> reply(new ActionMessage::FailedAction());

  if(action->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
  {
    std::shared_ptr<ActionMessage::MoveAction> moveAction =
      std::dynamic_pointer_cast<ActionMessage::MoveAction>(action);
    Pathing::Point goalPoint(
      moveAction->xGet(),
      moveAction->yGet(),
      moveAction->zGet());
    Pathing::Point masterPosition = m_masterSimulator.moveTo(goalPoint);
    Pathing::Point testerPosition = m_testerSimulator.moveTo(goalPoint);

    std::cout << "float final value: " << std::endl;
    std::cout << "\tx: " << masterPosition.xGet() << std::endl;
    std::cout << "\ty: " << masterPosition.yGet() << std::endl;
    std::cout << "\tz: "  << masterPosition.zGet() << std::endl;
    std::cout << "fixed final value: " << std::endl;
    std::cout << "\tx: " << testerPosition.xGet() << std::endl;
    std::cout << "\ty: " << testerPosition.yGet() << std::endl;
    std::cout << "\tz: "  << testerPosition.zGet() << std::endl;
    if(about(testerPosition, masterPosition))
    {
      reply = shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
    }
    else
    {
      reply = shared_ptr<ActionMessage::Action>(new ActionMessage::FailedAction());
    }
  }
  else if(action->messageTypeGet() == ActionMessage::HomeAction::TYPE_ID)
  {
    m_masterSimulator.home();
    m_testerSimulator.home();
  }
  else if(action->messageTypeGet() == ActionMessage::PowerDownAction::TYPE_ID)
  {
    m_masterSimulator.powerDown();
    m_testerSimulator.powerDown();

    reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
  }
  else if(action->messageTypeGet() == ActionMessage::PowerUpAction::TYPE_ID)
  {
    m_masterSimulator.powerUp();
    m_testerSimulator.powerUp();

    reply = std::shared_ptr<ActionMessage::Action>(new ActionMessage::SuccessAction());
  }

  return reply;
}


//*****************************************************************************
void Simulator::SimulatorController::powerDownSend()
{

}


//*****************************************************************************
void Simulator::SimulatorController::powerUpSend()
{

}

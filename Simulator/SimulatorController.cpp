#include "Simulator/SimulatorController.h"

#include "ActionMessage/FailedAction.h"
#include "ActionMessage/HomeAction.h"
#include "ActionMessage/KillAction.h"
#include "ActionMessage/MoveAction.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerUpAction.h"
#include "ActionMessage/SuccessAction.h"


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

    if(testerPosition == masterPosition)
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

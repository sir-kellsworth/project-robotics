#include "ActionMessage/ActionFactory/ActionFactory.h"

#include "ActionMessage/FailedAction.h"
#include "ActionMessage/FailedActionDecoder.h"
#include "ActionMessage/FailedActionEncoder.h"
#include "ActionMessage/HomeAction.h"
#include "ActionMessage/HomeActionDecoder.h"
#include "ActionMessage/HomeActionEncoder.h"
#include "ActionMessage/KillAction.h"
#include "ActionMessage/KillActionDecoder.h"
#include "ActionMessage/KillActionEncoder.h"
#include "ActionMessage/MoveAction.h"
#include "ActionMessage/MoveActionDecoder.h"
#include "ActionMessage/MoveActionEncoder.h"
#include "ActionMessage/NoAction.h"
#include "ActionMessage/NoActionDecoder.h"
#include "ActionMessage/NoActionEncoder.h"
#include "ActionMessage/PowerDownAction.h"
#include "ActionMessage/PowerDownActionDecoder.h"
#include "ActionMessage/PowerDownActionEncoder.h"
#include "ActionMessage/PowerUpAction.h"
#include "ActionMessage/PowerUpActionDecoder.h"
#include "ActionMessage/PowerUpActionEncoder.h"
#include "ActionMessage/SuccessAction.h"
#include "ActionMessage/SuccessActionDecoder.h"
#include "ActionMessage/SuccessActionEncoder.h"


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
}


//*****************************************************************************
unique_ptr<ActionMessage::Action> ActionMessage::ActionFactory::messageGenerate
(
  vector<uint8_t> data
)
{
  unique_ptr<ActionMessage::Action> generatedAction;

  if(data[TYPE_ID_POSITION] == ActionMessage::FailedAction::TYPE_ID)
  {
    ActionMessage::FailedActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::HomeAction::TYPE_ID)
  {
    ActionMessage::HomeActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::KillAction::TYPE_ID)
  {
    ActionMessage::KillActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::MoveAction::TYPE_ID)
  {
    ActionMessage::MoveActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::NoAction::TYPE_ID)
  {
    ActionMessage::NoActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::PowerDownAction::TYPE_ID)
  {
    ActionMessage::PowerDownActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::PowerUpAction::TYPE_ID)
  {
    ActionMessage::PowerUpActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }
  else if(data[TYPE_ID_POSITION] == ActionMessage::SuccessAction::TYPE_ID)
  {
    ActionMessage::SuccessActionDecoder decoder(data);
    generatedAction = decoder.definitionGet();
  }

  return generatedAction;
}


//*****************************************************************************
unique_ptr<ActionMessage::ActionEncoder> ActionMessage::ActionFactory::encoderGet
(
  shared_ptr<ActionMessage::Action> action
)
{
  unique_ptr<ActionMessage::ActionEncoder> encoder;

  if(action->messageTypeGet() == ActionMessage::FailedAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::FailedActionEncoder,
      ActionMessage::FailedAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::HomeAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::HomeActionEncoder,
      ActionMessage::HomeAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::KillAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::KillActionEncoder,
      ActionMessage::KillAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::MoveAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::MoveActionEncoder,
      ActionMessage::MoveAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::NoAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::NoActionEncoder,
      ActionMessage::NoAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::PowerDownAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::PowerDownActionEncoder,
      ActionMessage::PowerDownAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::PowerUpAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::PowerUpActionEncoder,
      ActionMessage::PowerUpAction>(action);
  }
  else if(action->messageTypeGet() == ActionMessage::SuccessAction::TYPE_ID)
  {
    encoder = encoderGetSub<
      ActionMessage::SuccessActionEncoder,
      ActionMessage::SuccessAction>(action);
  }

  return encoder;
}

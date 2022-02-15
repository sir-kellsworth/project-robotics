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

  template<class T>
  shared_ptr<T> dynamicCast
  (
    shared_ptr<ActionMessage::Action> ptr
  )
  {
    #ifdef __linux__
    return std::dynamic_pointer_cast<T>(ptr);
    #else
    return shared_ptr<T>((T*)(ptr.get()));
    #endif
  }
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

  if(dynamicCast<ActionMessage::FailedAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::FailedActionEncoder(
        dynamicCast<ActionMessage::FailedAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::HomeAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::HomeActionEncoder(
        dynamicCast<ActionMessage::HomeAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::KillAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::KillActionEncoder(
        dynamicCast<ActionMessage::KillAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::MoveAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::MoveActionEncoder(
        dynamicCast<ActionMessage::MoveAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::NoAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::NoActionEncoder(
        dynamicCast<ActionMessage::NoAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::PowerDownAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::PowerDownActionEncoder(
        dynamicCast<ActionMessage::PowerDownAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::PowerUpAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::PowerUpActionEncoder(
        dynamicCast<ActionMessage::PowerUpAction>(action).get()));
  }
  else if(dynamicCast<ActionMessage::SuccessAction>(action).get() != 0)
  {
    encoder = unique_ptr<ActionMessage::ActionEncoder>(
      new ActionMessage::SuccessActionEncoder(
        dynamicCast<ActionMessage::SuccessAction>(action).get()));
  }

  return encoder;
}

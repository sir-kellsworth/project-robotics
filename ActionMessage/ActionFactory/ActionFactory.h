#ifndef ACTIONMESSAGE_ACTIONFACTORY_H
#define ACTIONMESSAGE_ACTIONFACTORY_H

#include "ActionMessage/Action.h"
#include "ActionMessage/ActionEncoder.h"

#include "Utils/memory.h"

namespace ActionMessage { namespace ActionFactory
{

unique_ptr<ActionMessage::Action> messageGenerate(
  vector<uint8_t> data);

unique_ptr<ActionMessage::ActionEncoder> encoderGet(
  shared_ptr<ActionMessage::Action> action);

template<class ActionEncoder, class ActionClass>
unique_ptr<ActionMessage::ActionEncoder> encoderGetSub(
  shared_ptr<ActionMessage::Action> action);

} }


template<class ActionEncoder, class ActionClass>
unique_ptr<ActionMessage::ActionEncoder> ActionMessage::ActionFactory::encoderGetSub
(
  shared_ptr<ActionMessage::Action> action
)
{
#ifdef __linux__
  return unique_ptr<ActionMessage::ActionEncoder>(
    reinterpret_cast<ActionMessage::ActionEncoder*>(
      new ActionEncoder(
        dynamic_cast<ActionClass*>(
          action.get()))));
#else
return unique_ptr<ActionMessage::ActionEncoder>(
  (ActionMessage::ActionEncoder*)
    new ActionEncoder(
      (ActionClass*)
        action.get()));
#endif
}

#endif

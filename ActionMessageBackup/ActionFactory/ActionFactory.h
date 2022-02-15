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

} }

#endif

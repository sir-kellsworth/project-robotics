#ifndef CONTROLINTERFACE_DEVICE_H
#define CONTROLINTERFACE_DEVICE_H

#include "ActionMessage/Action.h"

#include "Utils/shared_ptr.h"

namespace ControlInterface
{

class Device
{
public:
  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    shared_ptr<ActionMessage::Action> nextAction) = 0;
};

}

#endif

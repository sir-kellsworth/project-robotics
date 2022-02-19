#ifndef CONTROLINTERFACE_DEVICE_H
#define CONTROLINTERFACE_DEVICE_H

#include "ActionMessage/Action.h"

#include "Utils/shared_ptr.h"

namespace ControlInterface
{

class Device
{
public:
  virtual void actionSend(
    shared_ptr<ActionMessage::Action> nextAction) = 0;

  virtual shared_ptr<ActionMessage::Action> actionSendReply(
    std::shared_ptr<ActionMessage::Action> nextAction) = 0;

  virtual void powerDownSend() = 0;

  virtual void powerUpSend() = 0;
};

}

#endif

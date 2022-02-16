#ifndef REMOTE_INTERFACE_H
#define REMOTE_INTERFACE_H

#include "RoboticArm.h"

#include "Utils/unique_ptr.h"

namespace ActionMessage
{
  class Action;
  class MoveAction;
}

class RemoteInterface
{
public:
  RemoteInterface(
    RoboticArm& arm);

  ~RemoteInterface();

  bool actionGet(
    shared_ptr<ActionMessage::Action>& nextAction);

  void step();

private:
  RoboticArm& m_arm;
};

#endif

#ifndef REMOTE_INTERFACE_H
#define REMOTE_INTERFACE_H

#include "RoboticArm.h"

#include "Utils/unique_ptr.h"

class RemoteInterface
{
public:
  RemoteInterface(
    RoboticArm& arm);

  ~RemoteInterface();

  bool actionGet(
    unique_ptr<ActionMessage::Action>& nextAction);

  void step();

private:
  void moveHandle(
    unique_ptr<ActionMessage::MoveAction> moveAction);

  RoboticArm& m_arm;
};

#endif

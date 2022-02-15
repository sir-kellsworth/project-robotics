#ifndef ROBOTIC_ARM_H
#define ROBOTIC_ARM_H

#include "ControlInterface/Device.h"

class RoboticArm : public ControlInterface::Device
{
public:
  RoboticArm();

  virtual ~RoboticArm();

  virtual void actionSend(
    shared_ptr<ActionMessage::Action> action);

  virtual void powerDownSend();

  virtual void powerUpSend();
private:

};

#endif

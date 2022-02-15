#ifndef ACTIONMESSAGE_PowerUpAction_H
#define ACTIONMESSAGE_PowerUpAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class PowerUpAction : public ActionMessage::Action
{
public:
  PowerUpAction();

  virtual ~PowerUpAction();

  static const uint8_t TYPE_ID;

  static const uint8_t PACKET_SIZE;
  
private:

};

}

#endif

#ifndef ACTIONMESSAGE_PowerDownAction_H
#define ACTIONMESSAGE_PowerDownAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class PowerDownAction : public ActionMessage::Action
{
public:
  PowerDownAction();

  virtual ~PowerDownAction();

  static const uint8_t TYPE_ID;

  static const uint8_t PACKET_SIZE;
  
private:

};

}

#endif

#ifndef ACTIONMESSAGE_KillAction_H
#define ACTIONMESSAGE_KillAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class KillAction : public ActionMessage::Action
{
public:
  KillAction();

  virtual ~KillAction();
  
  

  virtual uint8_t messageTypeGet();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;

private:

};

}

#endif

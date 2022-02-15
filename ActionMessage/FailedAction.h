#ifndef ACTIONMESSAGE_FailedAction_H
#define ACTIONMESSAGE_FailedAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class FailedAction : public ActionMessage::Action
{
public:
  FailedAction();

  virtual ~FailedAction();
  
  

  virtual uint8_t messageTypeGet();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;

private:

};

}

#endif

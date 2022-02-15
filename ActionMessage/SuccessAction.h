#ifndef ACTIONMESSAGE_SuccessAction_H
#define ACTIONMESSAGE_SuccessAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class SuccessAction : public ActionMessage::Action
{
public:
  SuccessAction();

  virtual ~SuccessAction();
  
  

  virtual uint8_t messageTypeGet();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;

private:

};

}

#endif

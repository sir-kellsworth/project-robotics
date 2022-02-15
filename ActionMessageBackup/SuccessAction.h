#ifndef ACTIONMESSAGE_SUCCESSACTION_H
#define ACTIONMESSAGE_SUCCESSACTION_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class SuccessAction : public ActionMessage::Action
{
public:
  SuccessAction();

  virtual ~SuccessAction();

  static const uint8_t TYPE_ID;

  static const uint8_t PACKET_SIZE;

private:

};

}

#endif

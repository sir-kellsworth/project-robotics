#ifndef ACTIONMESSAGE_FAILEDACTION_H
#define ACTIONMESSAGE_FAILEDACTION_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class FailedAction : public ActionMessage::Action
{
public:
  FailedAction();

  virtual ~FailedAction();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;
private:

};

}

#endif

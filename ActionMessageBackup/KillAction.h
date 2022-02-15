#ifndef ACTIONMESSAGE_KILLACTION_H
#define ACTIONMESSAGE_KILLACTION_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class KillAction : public ActionMessage::Action
{
public:
  KillAction();

  virtual ~KillAction();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;
private:

};

}

#endif

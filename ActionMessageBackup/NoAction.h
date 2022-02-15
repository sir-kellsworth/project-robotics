#ifndef ACTIONMESSAGE_NoAction_H
#define ACTIONMESSAGE_NoAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class NoAction : public ActionMessage::Action
{
public:
  NoAction();

  virtual ~NoAction();

  static const uint8_t TYPE_ID;

  static const uint8_t PACKET_SIZE;

private:

};

}

#endif

#ifndef ACTIONMESSAGE_HomeAction_H
#define ACTIONMESSAGE_HomeAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class HomeAction : public ActionMessage::Action
{
public:
  HomeAction();

  virtual ~HomeAction();

  static const uint8_t TYPE_ID;

  static const uint8_t PACKET_SIZE;
  
private:

};

}

#endif

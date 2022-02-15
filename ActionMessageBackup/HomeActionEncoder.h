#ifndef ACTIONMESSAGE_HOMEACTIONENCODER_H
#define ACTIONMESSAGE_HOMEACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/HomeAction.h"

namespace ActionMessage
{

class HomeActionEncoder : public ActionMessage::ActionEncoder
{
public:
  HomeActionEncoder(
    HomeAction* action);

  virtual ~HomeActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::HomeAction* m_action;
};

}

#endif

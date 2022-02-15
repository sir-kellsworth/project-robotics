#ifndef ACTIONMESSAGE_KILLACTIONENCODER_H
#define ACTIONMESSAGE_KILLACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/KillAction.h"

namespace ActionMessage
{

class KillActionEncoder : public ActionMessage::ActionEncoder
{
public:
  KillActionEncoder(
    KillAction* action);

  virtual ~KillActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::KillAction* m_action;
};

}

#endif

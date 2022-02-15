#ifndef ACTIONMESSAGE_NOACTIONENCODER_H
#define ACTIONMESSAGE_NOACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/NoAction.h"

namespace ActionMessage
{

class NoActionEncoder : public ActionMessage::ActionEncoder
{
public:
  NoActionEncoder(
    NoAction* action);

  virtual ~NoActionEncoder();

  void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::NoAction* m_action;
};

}

#endif

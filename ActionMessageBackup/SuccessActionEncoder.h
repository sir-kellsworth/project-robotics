#ifndef ACTIONMESSAGE_SUCCESSACTIONENCODER_H
#define ACTIONMESSAGE_SUCCESSACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/SuccessAction.h"

namespace ActionMessage
{

class SuccessActionEncoder : public ActionMessage::ActionEncoder
{
public:
  SuccessActionEncoder(
    SuccessAction* action);

  virtual ~SuccessActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::SuccessAction* m_action;
};

}

#endif

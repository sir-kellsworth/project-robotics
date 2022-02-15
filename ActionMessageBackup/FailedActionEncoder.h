#ifndef ACTIONMESSAGE_FAILEDACTIONENCODER_H
#define ACTIONMESSAGE_FAILEDACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/FailedAction.h"

#include "Utils/vector.h"

namespace ActionMessage
{

class FailedActionEncoder : public ActionMessage::ActionEncoder
{
public:
  FailedActionEncoder(
    FailedAction* action);

  virtual ~FailedActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::FailedAction* m_action;
};

}

#endif

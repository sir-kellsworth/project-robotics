#ifndef ACTIONMESSAGE_FailedActionEncoder_H
#define ACTIONMESSAGE_FailedActionEncoder_H

#include "ActionMessage/FailedAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class FailedActionEncoder
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

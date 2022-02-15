#ifndef ACTIONMESSAGE_SuccessActionEncoder_H
#define ACTIONMESSAGE_SuccessActionEncoder_H

#include "ActionMessage/SuccessAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class SuccessActionEncoder
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

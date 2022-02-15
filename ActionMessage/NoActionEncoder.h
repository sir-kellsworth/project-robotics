#ifndef ACTIONMESSAGE_NoActionEncoder_H
#define ACTIONMESSAGE_NoActionEncoder_H

#include "ActionMessage/NoAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class NoActionEncoder
{
public:
  NoActionEncoder(
    NoAction* action);

  virtual ~NoActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::NoAction* m_action;
};

}

#endif

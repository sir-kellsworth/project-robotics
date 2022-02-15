#ifndef ACTIONMESSAGE_KillActionEncoder_H
#define ACTIONMESSAGE_KillActionEncoder_H

#include "ActionMessage/KillAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class KillActionEncoder
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

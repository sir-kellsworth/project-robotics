#ifndef ACTIONMESSAGE_MoveActionEncoder_H
#define ACTIONMESSAGE_MoveActionEncoder_H

#include "ActionMessage/MoveAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class MoveActionEncoder
{
public:
  MoveActionEncoder(
    MoveAction* action);

  virtual ~MoveActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::MoveAction* m_action;
};

}

#endif

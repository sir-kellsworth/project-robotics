#ifndef ACTIONMESSAGE_ACTION_H
#define ACTIONMESSAGE_ACTION_H

#include <stdint.h>

namespace ActionMessage
{

class Action
{
public:
  virtual ~Action();

  virtual void ActionMessage::KillAction::operator delete(
    void * p); // or delete(void *, std::size_t)
};

}

#endif

#ifndef ACTIONMESSAGE_HomeActionEncoder_H
#define ACTIONMESSAGE_HomeActionEncoder_H

#include "ActionMessage/HomeAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class HomeActionEncoder
{
public:
  HomeActionEncoder(
    HomeAction* action);

  virtual ~HomeActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::HomeAction* m_action;
};

}

#endif

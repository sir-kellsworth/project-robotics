#ifndef ACTIONMESSAGE_PowerDownActionEncoder_H
#define ACTIONMESSAGE_PowerDownActionEncoder_H

#include "ActionMessage/PowerDownAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerDownActionEncoder
{
public:
  PowerDownActionEncoder(
    PowerDownAction* action);

  virtual ~PowerDownActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::PowerDownAction* m_action;
};

}

#endif

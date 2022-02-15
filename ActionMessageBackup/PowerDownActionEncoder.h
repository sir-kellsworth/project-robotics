#ifndef ACTIONMESSAGE_POWERDOWNACTIONENCODER_H
#define ACTIONMESSAGE_POWERDOWNACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/PowerDownAction.h"

namespace ActionMessage
{

class PowerDownActionEncoder : public ActionMessage::ActionEncoder
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

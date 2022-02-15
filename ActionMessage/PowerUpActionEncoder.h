#ifndef ACTIONMESSAGE_PowerUpActionEncoder_H
#define ACTIONMESSAGE_PowerUpActionEncoder_H

#include "ActionMessage/PowerUpAction.h"
#include "Utils/shared_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerUpActionEncoder
{
public:
  PowerUpActionEncoder(
    PowerUpAction* action);

  virtual ~PowerUpActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::PowerUpAction* m_action;
};

}

#endif

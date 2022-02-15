#ifndef ACTIONMESSAGE_POWERUPACTIONENCODER_H
#define ACTIONMESSAGE_POWERUPACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/PowerUpAction.h"

namespace ActionMessage
{

class PowerUpActionEncoder : public ActionMessage::ActionEncoder
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

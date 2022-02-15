#ifndef ACTIONMESSAGE_POWERUPACTIONDECODER_H
#define ACTIONMESSAGE_POWERUPACTIONDECODER_H

#include "ActionMessage/PowerUpAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerUpActionDecoder
{
public:
  PowerUpActionDecoder(
    const vector<uint8_t>& data);

  virtual ~PowerUpActionDecoder();

  unique_ptr<ActionMessage::PowerUpAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

#ifndef ACTIONMESSAGE_PowerUpActionDecoder_H
#define ACTIONMESSAGE_PowerUpActionDecoder_H

#include "ActionMessage/PowerUpAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerUpActionDecoder
{
public:
  PowerUpActionDecoder(
    const vector<uint8_t>& data);

  virtual ~PowerUpActionDecoder();

  unique_ptr<PowerUpAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

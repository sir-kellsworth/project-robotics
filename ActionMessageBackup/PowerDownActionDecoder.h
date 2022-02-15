#ifndef ACTIONMESSAGE_POWERDOWNACTIONDECODER_H
#define ACTIONMESSAGE_POWERDOWNACTIONDECODER_H

#include "ActionMessage/PowerDownAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerDownActionDecoder
{
public:
  PowerDownActionDecoder(
    const vector<uint8_t>& data);

  virtual ~PowerDownActionDecoder();

  unique_ptr<ActionMessage::PowerDownAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

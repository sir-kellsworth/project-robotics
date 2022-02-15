#ifndef ACTIONMESSAGE_PowerDownActionDecoder_H
#define ACTIONMESSAGE_PowerDownActionDecoder_H

#include "ActionMessage/PowerDownAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class PowerDownActionDecoder
{
public:
  PowerDownActionDecoder(
    const vector<uint8_t>& data);

  virtual ~PowerDownActionDecoder();

  unique_ptr<PowerDownAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

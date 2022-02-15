#ifndef ACTIONMESSAGE_FAILEDACTIONDECODER_H
#define ACTIONMESSAGE_FAILEDACTIONDECODER_H

#include "ActionMessage/FailedAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class FailedActionDecoder
{
public:
  FailedActionDecoder(
    const vector<uint8_t>& data);

  virtual ~FailedActionDecoder();

  unique_ptr<ActionMessage::FailedAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

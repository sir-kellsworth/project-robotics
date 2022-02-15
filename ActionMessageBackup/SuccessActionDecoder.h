#ifndef ACTIONMESSAGE_SUCCESSACTIONDECODER_H
#define ACTIONMESSAGE_SUCCESSACTIONDECODER_H

#include "ActionMessage/SuccessAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class SuccessActionDecoder
{
public:
  SuccessActionDecoder(
    const vector<uint8_t>& data);

  virtual ~SuccessActionDecoder();

  unique_ptr<ActionMessage::SuccessAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

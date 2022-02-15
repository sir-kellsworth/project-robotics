#ifndef ACTIONMESSAGE_NOACTIONDECODER_H
#define ACTIONMESSAGE_NOACTIONDECODER_H

#include "ActionMessage/NoAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class NoActionDecoder
{
public:
  NoActionDecoder(
    const vector<uint8_t>& data);

  virtual ~NoActionDecoder();

  unique_ptr<ActionMessage::NoAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

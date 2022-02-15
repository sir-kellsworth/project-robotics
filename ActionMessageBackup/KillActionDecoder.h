#ifndef ACTIONMESSAGE_KILLACTIONDECODER_H
#define ACTIONMESSAGE_KILLACTIONDECODER_H

#include "ActionMessage/KillAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class KillActionDecoder
{
public:
  KillActionDecoder(
    const vector<uint8_t>& data);

  virtual ~KillActionDecoder();

  unique_ptr<ActionMessage::KillAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

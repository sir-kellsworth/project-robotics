#ifndef ACTIONMESSAGE_MOVEACTIONDECODER_H
#define ACTIONMESSAGE_MOVEACTIONDECODER_H

#include "ActionMessage/MoveAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class MoveActionDecoder
{
public:
  MoveActionDecoder(
    const vector<uint8_t>& data);

  virtual ~MoveActionDecoder();

  unique_ptr<ActionMessage::MoveAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

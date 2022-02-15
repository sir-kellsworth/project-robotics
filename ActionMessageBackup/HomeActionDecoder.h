#ifndef ACTIONMESSAGE_HOMEACTIONDECODER_H
#define ACTIONMESSAGE_HOMEACTIONDECODER_H

#include "ActionMessage/HomeAction.h"

#include "Utils/memory.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class HomeActionDecoder
{
public:
  HomeActionDecoder(
    const vector<uint8_t>& data);

  virtual ~HomeActionDecoder();

  unique_ptr<ActionMessage::HomeAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

#ifndef ACTIONMESSAGE_NoActionDecoder_H
#define ACTIONMESSAGE_NoActionDecoder_H

#include "ActionMessage/NoAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class NoActionDecoder
{
public:
  NoActionDecoder(
    const vector<uint8_t>& data);

  virtual ~NoActionDecoder();

  unique_ptr<NoAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

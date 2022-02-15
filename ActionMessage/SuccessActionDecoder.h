#ifndef ACTIONMESSAGE_SuccessActionDecoder_H
#define ACTIONMESSAGE_SuccessActionDecoder_H

#include "ActionMessage/SuccessAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class SuccessActionDecoder
{
public:
  SuccessActionDecoder(
    const vector<uint8_t>& data);

  virtual ~SuccessActionDecoder();

  unique_ptr<SuccessAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

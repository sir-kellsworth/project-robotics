#ifndef ACTIONMESSAGE_FailedActionDecoder_H
#define ACTIONMESSAGE_FailedActionDecoder_H

#include "ActionMessage/FailedAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class FailedActionDecoder
{
public:
  FailedActionDecoder(
    const vector<uint8_t>& data);

  virtual ~FailedActionDecoder();

  unique_ptr<FailedAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

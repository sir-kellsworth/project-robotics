#ifndef ACTIONMESSAGE_KillActionDecoder_H
#define ACTIONMESSAGE_KillActionDecoder_H

#include "ActionMessage/KillAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class KillActionDecoder
{
public:
  KillActionDecoder(
    const vector<uint8_t>& data);

  virtual ~KillActionDecoder();

  unique_ptr<KillAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

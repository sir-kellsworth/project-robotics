#ifndef ACTIONMESSAGE_MoveActionDecoder_H
#define ACTIONMESSAGE_MoveActionDecoder_H

#include "ActionMessage/MoveAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class MoveActionDecoder
{
public:
  MoveActionDecoder(
    const vector<uint8_t>& data);

  virtual ~MoveActionDecoder();

  unique_ptr<MoveAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

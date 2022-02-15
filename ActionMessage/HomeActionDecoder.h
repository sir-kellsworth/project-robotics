#ifndef ACTIONMESSAGE_HomeActionDecoder_H
#define ACTIONMESSAGE_HomeActionDecoder_H

#include "ActionMessage/HomeAction.h"
#include "Utils/unique_ptr.h"
#include "Utils/vector.h"

namespace ActionMessage
{

class HomeActionDecoder
{
public:
  HomeActionDecoder(
    const vector<uint8_t>& data);

  virtual ~HomeActionDecoder();

  unique_ptr<HomeAction> definitionGet();

private:
  vector<uint8_t> m_data;
};

}

#endif

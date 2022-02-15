#ifndef ACTIONMESSAGE_ACTIONENCODER_H
#define ACTIONMESSAGE_ACTIONENCODER_H

#include "Utils/vector.h"

#include <stdint.h>

namespace ActionMessage
{

class ActionEncoder
{
public:
  virtual ~ActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data) = 0;
};

}

#endif

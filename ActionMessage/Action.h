#ifndef ACTIONMESSAGE_ACTION_H
#define ACTIONMESSAGE_ACTION_H

#include <stdint.h>
#include <stdlib.h>

inline void operator delete(void* ptr, unsigned int size)
{
    free(ptr);
}

namespace ActionMessage
{

class Action
{
public:
  virtual ~Action();

  virtual uint8_t messageTypeGet() = 0;
};

}

#endif

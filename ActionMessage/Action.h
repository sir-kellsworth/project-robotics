#ifndef ACTIONMESSAGE_ACTION_H
#define ACTIONMESSAGE_ACTION_H

#include <stdint.h>
#include <stdlib.h>

#ifndef __linux__
inline void operator delete(void* ptr, unsigned int size)
{
    free(ptr);
}

inline void operator delete[](void* ptr, unsigned int size)
{
  void* next = ptr;
  for(int i = 0; i < size; ++i)
  {
    free(next);
    ++next;
  }
}
#endif

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

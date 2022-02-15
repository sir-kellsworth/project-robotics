#include "ActionMessage/Action.h"

#include <stdlib.h>

//*****************************************************************************
ActionMessage::Action::~Action()
{

}


//*****************************************************************************
void ActionMessage::Action::operator delete
(
  void * p
) // or delete(void *, std::size_t)
{
  free(p);
}

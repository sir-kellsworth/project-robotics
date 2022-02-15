#include "ActionMessage/KillActionDecoder.h"


#include "Pathing/Point.h"

//*****************************************************************************
ActionMessage::KillActionDecoder::KillActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::KillActionDecoder::~KillActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::KillAction> ActionMessage::KillActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::KillAction>(
    new ActionMessage::KillAction());
}

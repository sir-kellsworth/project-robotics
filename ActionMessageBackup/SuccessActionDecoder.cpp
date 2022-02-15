#include "ActionMessage/SuccessActionDecoder.h"


#include "Pathing/Point.h"

//*****************************************************************************
ActionMessage::SuccessActionDecoder::SuccessActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::SuccessActionDecoder::~SuccessActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::SuccessAction> ActionMessage::SuccessActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::SuccessAction>(
    new ActionMessage::SuccessAction());
}

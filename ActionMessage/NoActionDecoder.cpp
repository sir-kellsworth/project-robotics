#include "ActionMessage/NoActionDecoder.h"


namespace
{

}

//*****************************************************************************
ActionMessage::NoActionDecoder::NoActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::NoActionDecoder::~NoActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::NoAction> ActionMessage::NoActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::NoAction>(new ActionMessage::NoAction(
));
}

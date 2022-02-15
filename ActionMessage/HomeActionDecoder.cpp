#include "ActionMessage/HomeActionDecoder.h"


namespace
{

}

//*****************************************************************************
ActionMessage::HomeActionDecoder::HomeActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::HomeActionDecoder::~HomeActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::HomeAction> ActionMessage::HomeActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::HomeAction>(new ActionMessage::HomeAction(
));
}

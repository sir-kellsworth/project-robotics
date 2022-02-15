#include "ActionMessage/FailedActionDecoder.h"


namespace
{

}

//*****************************************************************************
ActionMessage::FailedActionDecoder::FailedActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::FailedActionDecoder::~FailedActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::FailedAction> ActionMessage::FailedActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::FailedAction>(new ActionMessage::FailedAction(
));
}

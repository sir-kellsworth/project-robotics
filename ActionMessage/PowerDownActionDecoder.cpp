#include "ActionMessage/PowerDownActionDecoder.h"


namespace
{

}

//*****************************************************************************
ActionMessage::PowerDownActionDecoder::PowerDownActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::PowerDownActionDecoder::~PowerDownActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::PowerDownAction> ActionMessage::PowerDownActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::PowerDownAction>(new ActionMessage::PowerDownAction(
));
}

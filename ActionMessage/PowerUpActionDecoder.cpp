#include "ActionMessage/PowerUpActionDecoder.h"


namespace
{

}

//*****************************************************************************
ActionMessage::PowerUpActionDecoder::PowerUpActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::PowerUpActionDecoder::~PowerUpActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::PowerUpAction> ActionMessage::PowerUpActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::PowerUpAction>(new ActionMessage::PowerUpAction(
));
}

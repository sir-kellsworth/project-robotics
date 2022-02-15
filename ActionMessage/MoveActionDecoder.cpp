#include "ActionMessage/MoveActionDecoder.h"


namespace
{
	const uint16_t INDEX_PARAM_0(2);
	const uint16_t INDEX_PARAM_1(INDEX_PARAM_0 + sizeof(ActionMessage::MoveAction::SIZE_PARAM_1));
	const uint16_t INDEX_PARAM_2(INDEX_PARAM_1 + sizeof(ActionMessage::MoveAction::SIZE_PARAM_2));

}

//*****************************************************************************
ActionMessage::MoveActionDecoder::MoveActionDecoder
(
  const vector<uint8_t>& data
)
:m_data(data)
{

}


//*****************************************************************************
ActionMessage::MoveActionDecoder::~MoveActionDecoder()
{

}


//*****************************************************************************
unique_ptr<ActionMessage::MoveAction> ActionMessage::MoveActionDecoder::definitionGet()
{
  return unique_ptr<ActionMessage::MoveAction>(new ActionMessage::MoveAction(
		*reinterpret_cast<float*>(&m_data[INDEX_PARAM_0]),
		*reinterpret_cast<float*>(&m_data[INDEX_PARAM_1]),
		*reinterpret_cast<float*>(&m_data[INDEX_PARAM_2])));
}

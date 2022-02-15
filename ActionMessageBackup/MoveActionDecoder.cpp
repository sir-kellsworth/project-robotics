#include "ActionMessage/MoveActionDecoder.h"


#include "Pathing/Point.h"

namespace
{
  const uint8_t DATA_X_POSITION(1);
  const uint8_t DATA_Y_POSITION(DATA_X_POSITION + sizeof(float));
  const uint8_t DATA_Z_POSITION(DATA_Y_POSITION + sizeof(float));
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
  int dataStart(1);
  return unique_ptr<ActionMessage::MoveAction>(
    new ActionMessage::MoveAction(
      Pathing::Point(
        *reinterpret_cast<float*>(&m_data[DATA_X_POSITION]),
        *reinterpret_cast<float*>(&m_data[DATA_Y_POSITION]),
        *reinterpret_cast<float*>(&m_data[DATA_Z_POSITION]))));
}

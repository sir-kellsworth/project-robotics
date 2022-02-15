#include "ActionMessage/MoveActionEncoder.h"

#include <string.h>


namespace
{
  const uint8_t TYPE_ID_POSITION(0);
  const uint8_t DATA_X_POSITION(1);
  const uint8_t DATA_Y_POSITION(DATA_X_POSITION + sizeof(float));
  const uint8_t DATA_Z_POSITION(DATA_Y_POSITION + sizeof(float));
}

//*****************************************************************************
ActionMessage::MoveActionEncoder::MoveActionEncoder
(
  MoveAction* action
)
:m_action(action)
{

}


//*****************************************************************************
ActionMessage::MoveActionEncoder::~MoveActionEncoder()
{

}


//*****************************************************************************
void ActionMessage::MoveActionEncoder::actionEncode
(
  vector<uint8_t>& data
)
{
  data.resize(ActionMessage::MoveAction::PACKET_SIZE);

  data[TYPE_ID_POSITION] = ActionMessage::MoveAction::TYPE_ID;
  Pathing::Point point = m_action->pointGet();
  float x = point.xGet();
  float y = point.yGet();
  float z = point.zGet();
  memcpy(&data[DATA_X_POSITION], &x, sizeof(float));
  memcpy(&data[DATA_Y_POSITION], &y, sizeof(float));
  memcpy(&data[DATA_Z_POSITION], &z, sizeof(float));
}

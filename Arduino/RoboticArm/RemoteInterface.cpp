#include "RemoteInterface.h"

#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "ActionMessage/MoveAction.h"

#include <Arduino.h>


namespace
{
  const uint8_t BUFFER_MAX_SIZE(20);
  const uint8_t NUM_END_BYTES(3);
  const uint8_t MESSAGE_END[3] = {0x44, 0x44, 0x44};
}


//*****************************************************************
RemoteInterface::RemoteInterface
(
  RoboticArm& arm
)
:m_buffer(BUFFER_MAX_SIZE),
 m_actionAvailable(false),
 m_bufferIndex(0),
 m_arm(arm)
{

}


//*****************************************************************
RemoteInterface::~RemoteInterface()
{

}


//*****************************************************************
bool RemoteInterface::actionGet
(
  shared_ptr<ActionMessage::Action>& nextAction
)
{
  bool success(false);
  if(m_actionAvailable)
  {
    nextAction = m_nextAction;
    success = true;
  }

  return success;
}


//*****************************************************************
bool RemoteInterface::endFound()
{
  bool success(false);
  if(m_bufferIndex > NUM_END_BYTES)
  {
    uint8_t* messagePtr = m_buffer.begin();
    uint8_t* messageEnd = m_buffer.end();
    uint8_t* endDataPtr = MESSAGE_END;
    while(messagePtr != messageEnd)
    {
      if(messagePtr != endDataPtr)
      {
        return false;
      }
      ++messagePtr;
      ++endDataPtr;
    }
    success = true;
  }

  return success;
}


//*****************************************************************
void RemoteInterface::send
(
  const shared_ptr<ActionMessage::Action>& response
)
{
  vector<uint8_t> data;
  unique_ptr<ActionMessage::ActionEncoder> encoder
    = ActionMessage::ActionFactory::encoderGet(response);
  encoder->actionEncode(data);

  Serial.write(data.data(), data.size());
}


//*****************************************************************
void RemoteInterface::step()
{
  if(Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      m_buffer[m_bufferIndex] = Serial.read();
      ++m_bufferIndex;
    }

    if(endFound())
    {
      m_nextAction.reset(
        ActionMessage::ActionFactory::messageGenerate(m_buffer).release());
      m_actionAvailable = true;
      for(uint8_t i = 0; i < m_bufferIndex; ++i)
      {
        m_buffer[i] = 0;
      }
      m_bufferIndex = 0;
    }
  }
}

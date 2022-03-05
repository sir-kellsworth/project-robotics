#include "RemoteInterface.h"

#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "ActionMessage/MoveAction.h"

#include <Arduino.h>


namespace
{
  const uint8_t BUFFER_MAX_SIZE(500);
  const uint8_t NUM_END_BYTES(3);
  const uint8_t MESSAGE_END[NUM_END_BYTES] = {0x44, 0x44, 0x44};
}


//*****************************************************************
RemoteInterface::RemoteInterface()
:m_buffer(BUFFER_MAX_SIZE),
 m_actionAvailable(false),
 m_bufferIndex(0)
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
    uint8_t bufferStartIndex = m_bufferIndex - NUM_END_BYTES;
    for(int i = 0; i < NUM_END_BYTES; ++i)
    {
      if(m_buffer[bufferStartIndex + i] != MESSAGE_END[i])
      {
        return false;
      }
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
  Serial.write(MESSAGE_END, NUM_END_BYTES);
  Serial.flush();
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
      m_buffer.resize(m_buffer.size() - NUM_END_BYTES);
      m_nextAction.reset(
        ActionMessage::ActionFactory::messageGenerate(m_buffer).release());
      m_actionAvailable = true;
      memset((volatile void *)m_buffer.data(), 0, m_bufferIndex);
      m_bufferIndex = 0;
    }
  }
}

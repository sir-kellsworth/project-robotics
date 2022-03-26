#include "RemoteInterface.h"

#include "SerialLogger.h"
#include "ActionMessage/ActionFactory/ActionFactory.h"
#include "ActionMessage/MoveAction.h"

#include <Arduino.h>


namespace
{
  const uint8_t BUFFER_MAX_SIZE(100);
}


//*****************************************************************
RemoteInterface::RemoteInterface()
:m_state(LENGTH_GET_STATE),
 m_messageLength(0),
 m_buffer(BUFFER_MAX_SIZE),
 m_actionAvailable(false),
 m_bufferIndex(0)
{

}


//*****************************************************************
RemoteInterface::~RemoteInterface()
{

}


#include "ActionMessage/SuccessAction.h"
//*****************************************************************
bool RemoteInterface::actionGet
(
  unique_ptr<ActionMessage::Action>& nextAction
)
{
  bool success(false);
  if(m_actionAvailable)
  {
    m_buffer.resize(m_bufferIndex);
    nextAction = ActionMessage::ActionFactory::messageGenerate(m_buffer);
    LOGGER_DEBUG("action ptr: %i", nextAction.get());
    success = true;
    m_actionAvailable = false;
    m_bufferIndex = 0;
    memset(m_buffer.data(), 0, m_bufferIndex);
    m_buffer.resize(BUFFER_MAX_SIZE);
  }

  return success;
}


//*****************************************************************
void RemoteInterface::send
(
  const unique_ptr<ActionMessage::Action>& response
)
{
  vector<uint8_t> data;
  unique_ptr<ActionMessage::ActionEncoder> encoder
    = ActionMessage::ActionFactory::encoderGet(response);
  encoder->actionEncode(data);

  uint16_t length(data.size());
  Serial.write((uint8_t*)&length, 2);
  Serial.write(data.data(), length);
}


//*****************************************************************
void RemoteInterface::step()
{
  if(m_state == MESSAGE_PROCESS_STATE)
  {
    m_actionAvailable = true;
    m_state = LENGTH_GET_STATE;
  }
  else if(Serial.available() > 0)
  {
    if(m_state == LENGTH_GET_STATE)
    {
      //only want to get the length when the entire uint16 is available
      if(Serial.available() >= 2)
      {
        m_messageLength = Serial.read() | (Serial.read() << 8);
        m_state = MESSAGE_GET_STATE;
      }
    }
    else if(m_state == MESSAGE_GET_STATE)
    {
      while(Serial.available() > 0)
      {
        m_buffer[m_bufferIndex] = Serial.read();
        ++m_bufferIndex;
      }

      if(m_bufferIndex >= m_messageLength)
      {
        m_state = MESSAGE_PROCESS_STATE;
      }
    }
  }
}

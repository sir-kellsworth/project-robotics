#ifndef REMOTE_INTERFACE_H
#define REMOTE_INTERFACE_H

#include "RoboticArm.h"

#include "Utils/unique_ptr.h"

namespace ActionMessage
{
  class Action;
  class MoveAction;
}

class RemoteInterface
{
public:
  RemoteInterface();

  ~RemoteInterface();

  bool actionGet(
    shared_ptr<ActionMessage::Action>& nextAction);

  void send(
    const shared_ptr<ActionMessage::Action>& response);

  void step();

private:
  enum SERIAL_STATE
  {
    LENGTH_GET_STATE = 0,
    MESSAGE_GET_STATE,
    MESSAGE_PROCESS_STATE,
  };

  SERIAL_STATE m_state;
  uint16_t m_messageLength;
  vector<uint8_t> m_buffer;
  shared_ptr<ActionMessage::Action> m_nextAction;
  bool m_actionAvailable;
  uint8_t m_bufferIndex;
};

#endif

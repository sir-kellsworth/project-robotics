#ifndef ACTIONMESSAGE_MOVEACTIONENCODER_H
#define ACTIONMESSAGE_MOVEACTIONENCODER_H

#include "ActionMessage/ActionEncoder.h"
#include "ActionMessage/MoveAction.h"

namespace ActionMessage
{

class MoveActionEncoder : public ActionMessage::ActionEncoder
{
public:
  MoveActionEncoder(
    MoveAction* action);

  virtual ~MoveActionEncoder();

  virtual void actionEncode(
    vector<uint8_t>& data);

private:
  ActionMessage::MoveAction* m_action;
};

}

#endif

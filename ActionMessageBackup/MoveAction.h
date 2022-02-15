#ifndef ACTIONMESSAGE_MoveAction_H
#define ACTIONMESSAGE_MoveAction_H

#include "ActionMessage/Action.h"
#include "Pathing/Point.h"

namespace ActionMessage
{

class MoveAction : public ActionMessage::Action
{
public:
  MoveAction(
	const Pathing::Point& point);

  virtual ~MoveAction();

Pathing::Point pointGet();

void pointSet(
	const Pathing::Point& point);

static const uint8_t TYPE_ID;
static const uint8_t PACKET_SIZE;

private:
  	Pathing::Point m_point;

};

}

#endif

#ifndef ACTIONMESSAGE_MoveAction_H
#define ACTIONMESSAGE_MoveAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class MoveAction : public ActionMessage::Action
{
public:
  MoveAction(
	float x,
	float y,
	float z);

  virtual ~MoveAction();

float xGet();

float yGet();

float zGet();


void xSet(
	const float& x);

void ySet(
	const float& y);

void zSet(
	const float& z);


  virtual uint8_t messageTypeGet();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;
	static const uint8_t SIZE_PARAM_0;
	static const uint8_t SIZE_PARAM_1;
	static const uint8_t SIZE_PARAM_2;

private:
	float m_x;
	float m_y;
	float m_z;

};

}

#endif

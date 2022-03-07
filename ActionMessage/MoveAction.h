#ifndef ACTIONMESSAGE_MoveAction_H
#define ACTIONMESSAGE_MoveAction_H

#include "ActionMessage/Action.h"

namespace ActionMessage
{

class MoveAction : public ActionMessage::Action
{
public:
  MoveAction(
	uint16_t x,
	uint16_t y,
	uint16_t z);

  virtual ~MoveAction();
  
uint16_t xGet();

uint16_t yGet();

uint16_t zGet();

  
void xSet(
	const uint16_t& x);

void ySet(
	const uint16_t& y);

void zSet(
	const uint16_t& z);


  virtual uint8_t messageTypeGet();

  static const uint8_t TYPE_ID;
  static const uint8_t PACKET_SIZE;
	static const uint8_t SIZE_PARAM_0;
	static const uint8_t SIZE_PARAM_1;
	static const uint8_t SIZE_PARAM_2;

private:
	uint16_t m_x;
	uint16_t m_y;
	uint16_t m_z;

};

}

#endif

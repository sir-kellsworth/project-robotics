#include "Simulator/Segment.h"


//*****************************************************************************
Simulator::Segment::Segment
(
  const Pathing::Point& startPoint,
  uint32_t segmentLength
)
:m_currentPosition(startPoint),
 m_segmentLength(segmentLength)
{

}


//*****************************************************************************
bool Simulator::Segment::moveTo
(
  const Pathing::Point& goal
)
{
  return m_parent->moveTo(goal);
}

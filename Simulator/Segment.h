#ifndef SIMULATOR_SEGMENT_H
#define SIMULATOR_SEGMENT_H

#include "Pathing/Point.h"

namespace Simulator
{

class Segment
{
public:
  Segment(
    const Pathing::Point& startPoint,
    uint32_t segmentLength);

  bool moveTo(
    const Pathing::Point& goal);
private:
  Pathing::Point m_currentPosition;
  uint32_t segmentLength;
  Segment* m_parent;
};

}

#endif

#ifndef PATHING_STRAIGHTPATH_H
#define PATHING_STRAIGHTPATH_H

#include "Pathing/Point.h"

namespace Pathing
{

class StraightPath : public Pathing::Path
{
public:
  StraightPath(
    const Pathing::Point& m_currentPosition,
    const Pathing::Point& goalPosition);

  virtual ~StraightPath();

  virtual const std::vector<Pathing::Point>& pointsGet();
private:
  std::vector<Pathing::Point> points;
};

}

#endif

#ifndef PATHING_PATH_H
#define PATHING_PATH_H

#include "Pathing/Point.h"

#include "Utils/vector.h"

namespace Pathing
{

typedef vector<Point> Path;

Path straightPathGenerate(
  const Pathing::Point& m_currentPosition,
  const Pathing::Point& goalPosition);

}

#endif

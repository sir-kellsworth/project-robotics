#include "Pathing/Path.h"


//*****************************************************************************
Pathing::Path Pathing::straightPathGenerate
(
  const Pathing::Point& currentPosition,
  const Pathing::Point& goalPosition
)
{
  Path path;

  float xM = (goalPosition.xGet() - currentPosition.xGet());
  float xC = currentPosition.xGet();
  float yM = (goalPosition.yGet() - currentPosition.yGet());
  float yC = currentPosition.yGet();
  float zM = (goalPosition.zGet() - currentPosition.zGet());
  float zC = currentPosition.zGet();

  path.push_back(currentPosition);
  for(int i = 0; i < 10; ++i)
  {
    float x = (xM * i) + xC;
    float y = (yM * i) + yC;
    float z = (zM * i) + zC;
    x = x > 0 ? x : -1;
    y = y > 0 ? y : -1;
    z = z > 0 ? z : -1;
    Pathing::Point next(x, y, z);

    path.push_back(next);
  }
  path.push_back(goalPosition);

  return path;
}

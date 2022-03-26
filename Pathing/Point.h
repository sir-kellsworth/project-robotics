#ifndef PATHING_POINT_H
#define PATHING_POINT_H

#include <stdint.h>

namespace Pathing
{

class Point
{
public:
  Point();

  Point(
    uint16_t x,
    uint16_t y,
    uint16_t z);

  ~Point();

  bool operator==(const Pathing::Point& p);

  bool valid();

  const uint16_t& xGet() const;

  void xSet(
    uint16_t x);

  const uint16_t& yGet() const;

  void ySet(
    uint16_t y);

  const uint16_t& zGet() const;

  void zSet(
    uint16_t z);

private:
  uint16_t m_x;
  uint16_t m_y;
  uint16_t m_z;
};

}

#endif

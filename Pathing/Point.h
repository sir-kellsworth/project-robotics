#ifndef PATHING_POINT_H
#define PATHING_POINT_H

namespace Pathing
{

class Point
{
public:
  Point();

  Point(
    float x,
    float y,
    float z);

  ~Point();

  bool operator==(const Pathing::Point& p);

  bool valid();

  const float& xGet() const;

  void xSet(
    float x);

  const float& yGet() const;

  void ySet(
    float y);

  const float& zGet() const;

  void zSet(
    float z);

private:
  float m_x;
  float m_y;
  float m_z;
};

}

#endif

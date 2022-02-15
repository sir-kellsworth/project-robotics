#include "Utils/TrigEquations.h"

#include <math.h>

namespace
{
    const float epsilon(1e-6);
}


//*****************************************************************************
void Utils::anglesCalculate
(
  float x,
  float y,
  float z,
  uint32_t armLength,
  uint32_t forarmLength,
  float& baseAngle,
  float& shoulderAngle,
  float& elbowAngle
)
{
  baseAngle = atan2(y, x + epsilon) * RADIANS_TO_DEGREES;
  float xy = sqrt(squared(x) + squared(y));
  float c = sqrt(squared(xy) + squared(z));
  float D1 = atan2(z, xy + epsilon);
  float D2 = lawOfCosines(c, armLength, forarmLength);
  shoulderAngle = (D1 + D2) * RADIANS_TO_DEGREES;
  elbowAngle = lawOfCosines(armLength, forarmLength, c) * RADIANS_TO_DEGREES;
}


//***************************************************************************
float Utils::lawOfCosines
(
  float a,
  float b,
  float c
)
{
  return acos((squared(a) + squared(b) - squared(c)) /
    (2 * a * b) + epsilon);
}


//*****************************************************************************
void Utils::positionCalculate
(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  uint32_t armLength,
  uint32_t forarmLength,
  float& nextX,
  float& nextY,
  float& nextZ
)
{
  //angleA = D2, or shoulder angle - D1
  //sideA = forarm
  //angleB = elbow angle
  //sideB = imaginary straight line
  //angleC = imaginary angle between wrist and base
  //sideC = arm
  float sideA = forarmLength;
  float angleB = elbowAngle * DEGREES_TO_RADIANS;
  float sideC = armLength;
  float sideB = sqrt(squared(sideA) + squared(sideC) - (2 * sideA * sideC * cos(angleB)));
  float angleA = lawOfCosines(sideB, sideC, sideA);
  float D1 = (shoulderAngle * DEGREES_TO_RADIANS) - angleA;
  float xy = sideB * cos(D1);
  baseAngle = baseAngle * DEGREES_TO_RADIANS;
  nextX = xy * sin(baseAngle);
  nextY = xy * cos(baseAngle);
  nextZ = sideB * sin(D1);
}


//***************************************************************************
float Utils::squared
(
  float a
)
{
  return a * a;
}

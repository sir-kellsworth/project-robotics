#include "Utils/TrigEquations.h"

#include <math.h>


//*****************************************************************************
void Utils::anglesCalculate
(
  float x,
  float y,
  float z,
  uint16_t armLength,
  uint16_t forarmLength,
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


//*****************************************************************************
void Utils::anglesCalculate
(
  Fix16 x,
  Fix16 y,
  Fix16 z,
  uint16_t armLength,
  uint16_t forarmLength,
  Fix16& baseAngle,
  Fix16& shoulderAngle,
  Fix16& elbowAngle
)
{
  baseAngle = y.atan2(x + epsilon_fix) * RADIANS_TO_DEGREES;
  Fix16 xy = (squared(x) + squared(y)).sqrt();
  Fix16 c = (squared(xy) + squared(z)).sqrt();
  Fix16 D1 = z.atan2(xy + epsilon_fix);
  Fix16 D2 = lawOfCosines(c, armLength, forarmLength);
  shoulderAngle = (D1 + D2) * RADIANS_TO_DEGREES;
  elbowAngle = lawOfCosines(Fix16(armLength), Fix16(forarmLength), c) * RADIANS_TO_DEGREES;
}


//*****************************************************************************
bool Utils::boundsCheck
(
  float angle,
  float minAngle,
  float maxAngle
)
{
  return angle >= minAngle && angle <= maxAngle;
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


//***************************************************************************
Fix16 Utils::lawOfCosines
(
  Fix16 a,
  Fix16 b,
  Fix16 c
)
{
  return ((squared(a) + squared(b) - squared(c)).acos() /
    (a * b * 2) + epsilon_fix);
}


//*****************************************************************************
void Utils::positionCalculate
(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  uint16_t armLength,
  uint16_t forarmLength,
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
  const float& a
)
{
  return a * a;
}


//***************************************************************************
Fix16 Utils::squared
(
  const Fix16& a
)
{
  return a * a;
}


//***************************************************************************
void Utils::stepperPositionCalculate
(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  float degreeSteps,
  uint16_t& basePosition,
  uint16_t& shoulderPosition,
  uint16_t& elbowPosition
)
{
  basePosition = baseAngle * degreeSteps;
  shoulderPosition = shoulderAngle * degreeSteps;
  elbowPosition = elbowAngle * degreeSteps;
}

#ifndef UTILS_TRIGEQUATIONS_H
#define UTILS_TRIGEQUATIONS_H

#include <stdint.h>

namespace Utils
{

void anglesCalculate(
  float x,
  float y,
  float z,
  uint32_t armLength,
  uint32_t forarmLength,
  float& baseAngle,
  float& shoulderAngle,
  float& elbowAngle);

float lawOfCosines(
  float a,
  float b,
  float c);

void positionCalculate(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  uint32_t armLength,
  uint32_t forarmLength,
  float& nextX,
  float& nextY,
  float& nextZ);

  float squared(
    float a);

  const static float PI(3.1415);
  const static float DEGREES_TO_RADIANS(PI / 180);
  const static float RADIANS_TO_DEGREES(180 / PI);
}

#endif

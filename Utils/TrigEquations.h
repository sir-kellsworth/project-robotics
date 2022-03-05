#ifndef UTILS_TRIGEQUATIONS_H
#define UTILS_TRIGEQUATIONS_H

#ifndef __linux__
#include <Arduino.h>
#endif

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

bool boundsCheck(
  float angle,
  float minAngle,
  float maxAngle);

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

  void stepperPositionCalculate(
    float baseAngle,
    float shoulderAngle,
    float elbowAngle,
    float degreeSteps,
    uint16_t& basePosition,
    uint16_t& shoulderPosition,
    uint16_t& elbowPosition);

#ifdef __linux__
  const static float PI(3.1415);
#endif
  const static float DEGREES_TO_RADIANS(PI / 180);
  const static uint8_t NO_MOVEMENT(-1);
  const static float RADIANS_TO_DEGREES(180 / PI);
}

#endif

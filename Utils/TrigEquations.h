#ifndef UTILS_TRIGEQUATIONS_H
#define UTILS_TRIGEQUATIONS_H

#ifndef __linux__
#include <Arduino.h>
#endif

#include <math.h>
#include <stdint.h>

class Fix16;

namespace Utils
{

void anglesCalculate(
  float x,
  float y,
  float z,
  uint16_t armLength,
  uint16_t forarmLength,
  float& baseAngle,
  float& shoulderAngle,
  float& elbowAngle);

void anglesCalculate(
  Fix16 x,
  Fix16 y,
  Fix16 z,
  uint16_t armLength,
  uint16_t forarmLength,
  Fix16& baseAngle,
  Fix16& shoulderAngle,
  Fix16& elbowAngle);

bool boundsCheck(
  float angle,
  float minAngle,
  float maxAngle);

float lawOfCosines(
  float a,
  float b,
  float c);

Fix16 lawOfCosines(
  Fix16 a,
  Fix16 b,
  Fix16 c);

void positionCalculate(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  uint16_t armLength,
  uint16_t forarmLength,
  float& nextX,
  float& nextY,
  float& nextZ);

float squared(
  const float& a);

Fix16 squared(
  const Fix16& a);

void stepperPositionCalculate(
  float baseAngle,
  float shoulderAngle,
  float elbowAngle,
  float degreeSteps,
  uint16_t& basePosition,
  uint16_t& shoulderPosition,
  uint16_t& elbowPosition);

#ifdef __linux__
  const static float PI                 (3.1415);
#endif
  const static float DEGREES_TO_RADIANS (PI / 180);
  const static uint8_t NO_MOVEMENT      (-1);
  const static float RADIANS_TO_DEGREES (180 / PI);
}

#endif

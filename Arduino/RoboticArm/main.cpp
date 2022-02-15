#include "RoboticArm.h"
#include "RemoteInterface.h"

#include <Arduino.h>


RoboticArm arm;
RemoteInterface interface(arm);


//*****************************************************************************
void setup()
{

}


//*****************************************************************************
void loop()
{
  interface.step();
}

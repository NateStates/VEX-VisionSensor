/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\natha                                            */
/*    Created:      Tue Mar 29 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "visionExperiment.h"

using namespace vex;
using namespace std;

//headers for Vision Sensor
vex::vision VisionSensor (vex::PORT19); //DoombaPrime's empty Port is PORT19. Use PORT19 to use Vision Sensor

void VisionTest()
{
  //VisionSensor.takeSnapshot(color::blue);
  while (true)
  {
    Brain.Screen.clearLine();
    VisionSensor.takeSnapshot(RED_GOAL);
    if (VisionSensor.largestObject.exists)
    {
      Brain.Screen.print("Vision Sensor: x: %d", VisionSensor.largestObject.originX);
      Brain.Screen.print(" Y: %d", VisionSensor.largestObject.originY);
      Brain.Screen.print(" W %d", VisionSensor.largestObject.width);
      Brain.Screen.print(" H: %d", VisionSensor.largestObject.height);
    }
    else
    {
      Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
    }
    task::sleep(100);
    }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  VisionTest();
  
}

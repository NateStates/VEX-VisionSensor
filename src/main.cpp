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

void VisionTest1()
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

void VisionTest2()
{
  double xScale = 480.0/310;//Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0/212;
  int x = 0; int y=0; int height =0; int width = 0;
  while (true)
  {
    Brain.Screen.clearLine();
    Brain.Screen.clearScreen();
    VisionSensor.takeSnapshot(BLUE_GOAL);
    if (VisionSensor.largestObject.exists)
    {
      x = VisionSensor.largestObject.originX;
      y = VisionSensor.largestObject.originY;
      width = VisionSensor.largestObject.width;
      height = VisionSensor.largestObject.height;
      Brain.Screen.print (" x %d y%d Width %d Height %d ",x, y, width, height);
      Brain.Screen.setFillColor(color::blue);
      Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
    }
    else
    {
      Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
    }
    task::sleep(100);
  }
}


void VisionTest3()
{
  int x = 0;
  int center = 158;// The x coordinate for the center of the vision sensor
  int OKError = 50; //Used to set a range of values to count is being just in front.
  while (true)
  {
    VisionSensor.takeSnapshot(BLUE_GOAL);
    if (VisionSensor.largestObject.exists)
    {
      x = VisionSensor.largestObject.centerX;
      if(x< (center-OKError)) //If the object is to the left of center
      {
        //RightMotor.spin(directionType::rev, 25, velocityUnits::pct);
        //LeftMotor.spin(directionType::fwd, 25, velocityUnits::pct);
      } 
      else if (x> center + OKError) //If the object is to the right of center
      {
        //RightMotor.spin(directionType::fwd, 25, velocityUnits::pct);
        //LeftMotor.spin(directionType::rev, 25, velocityUnits::pct);
      } else //The object is not to the right of center and not to the left of center
      {
        //LeftMotor.stop(brakeType::brake);
        //RightMotor.stop(brakeType::brake);
      }
    }
  task::sleep(100);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //VisionTest1();
  VisionTest2();
  VisionTest3();

}

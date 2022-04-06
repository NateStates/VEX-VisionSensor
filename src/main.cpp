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
#include "functions.h"

using namespace vex;
using namespace std;

//headers for Vision Sensor
vex::vision VisionSensor (vex::PORT19); //DoombaPrime's empty Port is PORT19. Use PORT19 to use Vision Sensor

//Function prototypes
void VisionTest1();
void VisionTest2();
//void VisionTest3();

  //BLUE_GOAL for blue
  //RED_GOAL for red
void VisionTest3(vex::vision::signature colorOfGoal, double speed); //NOTE: LETTERS HAS TO BE EXACT. 

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //VisionTest1();
  //VisionTest2();
  //VisionTest3();

  //BLUE_GOAL for blue
  //RED_GOAL for red
  //VisionTest3(BLUE_GOAL, 25); //NOTE: LETTERS HAS TO BE EXACT. 
  VisionTest3(RED_GOAL, 25); //NOTE: LETTERS HAS TO BE EXACT. 
}


//OUTPUT: Turns toward a colored goal. If not centered, turn either left or right until centered. If centered, move towards the goal
void VisionTest3(vex::vision::signature colorOfGoal, double speed)
{
  int center = 158;// The x coordinate for the center of the vision sensor
  int OKError = 50; //Used to set a range of values to count is being just in front.
  double xScale = 480.0/310;//Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0/212;
  int targetCenter = 0; int x = 0; int y=0; int height =0; int width = 0;
  bool isTrue = true;
  while (isTrue)
  {
    Brain.Screen.clearLine();
    Brain.Screen.clearScreen();
    VisionSensor.takeSnapshot(colorOfGoal);
    if (VisionSensor.largestObject.exists)
    {
      targetCenter = VisionSensor.largestObject.centerX;
      x = VisionSensor.largestObject.originX;
      y = VisionSensor.largestObject.originY;
      width = VisionSensor.largestObject.width;
      printf("width: %d\n", width);
      height = VisionSensor.largestObject.height;
      printf("height: %d\n", height);
      Brain.Screen.print (" X: %d Y: %d Width: %d Height: %d ",x, y, width, height);
      if(VisionSensor.takeSnapshot(colorOfGoal) == VisionSensor.takeSnapshot(BLUE_GOAL))
      {
        Brain.Screen.setFillColor(color::blue);
      }
      else if(VisionSensor.takeSnapshot(colorOfGoal) == VisionSensor.takeSnapshot(RED_GOAL))
      {
        Brain.Screen.setFillColor(color::red);
      }
      Brain.Screen.drawRectangle(x*xScale, y*yScale, width*xScale, height*yScale);
      
      if(targetCenter < (center - OKError)) //If the object is to the left of center
      {
        //turn right
        rightWheels.spin(directionType::rev, speed, velocityUnits::pct);
        leftWheels.spin(directionType::fwd, speed, velocityUnits::pct);
        // rightWheels.spin(directionType::rev, 25, velocityUnits::pct);
        // leftWheels.spin(directionType::fwd, 25, velocityUnits::pct);
      } 
      else if (targetCenter > (center + OKError)) //If the object is to the right of center
      {
        //turn left
        rightWheels.spin(directionType::fwd, speed, velocityUnits::pct);
        leftWheels.spin(directionType::rev, speed, velocityUnits::pct);
        // rightWheels.spin(directionType::fwd, 25, velocityUnits::pct);
        // leftWheels.spin(directionType::rev, 25, velocityUnits::pct);
      } 
      else //The object is not to the right of center and not to the left of center
      {
        //turn stop
        leftWheels.stop(brakeType::brake);
        rightWheels.stop(brakeType::brake);

        if(width < 263+OKError && height < 145+OKError) //(width < 314+OKError) || (height < 145+OKError || height > 145-OKError)
        {
          printf("Attempting to get close enough to goal\n");
          moveForward(15,25,5);
        }
        else
        {
          printf("Attempt success: goal is close enough\n");
          leftWheels.stop(brakeType::brake);
          rightWheels.stop(brakeType::brake);
          isTrue = false;
        }
      }
    }
    else
    {
      Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
      turnClockwise(15, 15, 3);
    }
  task::sleep(100);
  }
}


//OUTPUT: Brain Screen displays x-y coordinate, width, height, and a colored box of the detected color
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
      Brain.Screen.print (" X: %d Y: %d Width: %d Height: %d ",x, y, width, height);
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


//OUTPUT: Brain Screen displays x-y coordinate, width, height
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



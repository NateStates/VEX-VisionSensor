#include "vex.h"
#include "robot-config.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//Driving motors
motor left1(PORT1, ratio18_1, false); //front left
motor left2(PORT11, ratio18_1, true); //back left

motor right1(PORT9, ratio18_1, false); //front right
motor right2(PORT20, ratio18_1, true); //back right

//Motor Groups
motor_group leftWheels(left1, left2);
motor_group rightWheels(right1, right2);

//extern vision VisionSensor;

void vexcodeInit(void) 
{
  
}
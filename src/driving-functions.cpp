#include "vex.h"
#include "functions.h"
#include "robot-config.h"

void arcadeDrive(){
  if(abs(controller1.Axis3.value())>5||abs(controller1.Axis1.value())){

    leftWheels.spin(fwd,controller1.Axis3.value()*0.75+controller1.Axis1.value()*0.4,pct);
    rightWheels.spin(fwd, controller1.Axis3.value()*0.75-controller1.Axis1.value()*0.4,pct);

  }else{
    leftWheels.stop(coast);
    rightWheels.stop(coast);
  }
}
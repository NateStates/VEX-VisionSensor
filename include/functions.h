#ifndef FUNCTIONS
#define FUNCTIONS

//Timeout function: time to do command until motor stops
void setMotorTimeout(int timeSeconds);

//Drive distance with specific distance
void moveForward(float distanceCM, int speedPCT, int timeSec);

//Turn Clockwise
void turnClockwise(float degree, int speedPCT, int timeSec);


#endif
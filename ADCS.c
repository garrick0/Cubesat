//ACDS
#include "main.h"
#include "Arduino.h"

//Returns a 3 int long array (x,y,z axis) of current attitude 
int* getAttitude() {
  
  return 0;
}
//Returns the system angular velocity (magnitude)
int getAngVel() {
  int rotationPin = A1;
  return analogRead(rotationPin);
}

//Take a target attitude and implement changes required to achieve this
void adjAttitude(int* targetAttitude) {
}

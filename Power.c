//power
#include "main.h"
#include "Arduino.h"

//Return battery capacity
int batteryCap() {
  int batteryPin = A0;
  return analogRead(batteryPin);
}


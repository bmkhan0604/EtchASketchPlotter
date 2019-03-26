#include "header.h"

// input string format:
// X:# Y:# @
// Input numbers: integer 64 bit;
// currently number of steps, not millimeters.
// only support line movements;

void setup() {
  Serial.begin(9600);
  //instruction.reserve(200);
  stepperX.setSpeed(xspeed);
  stepperY.setSpeed(yspeed);
}

void loop() {
  if(stringComplete == true)
  {
    stringComplete = false;
    stringParse();
    Serial.print("X:"+ (String)xpos);
    Serial.println(" Y:" + (String)ypos);
    Serial.println(moveMotor());
    instruction = "";
    Serial.println();
    
  }
}

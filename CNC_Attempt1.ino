#include "arduinoHeader.h"
#define PI 3.1415926535897932384626433832795

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
  // test code
  if(false)
  {
   for(int i = 0; i<(360);i++)
  {
    xnew = 1000*sin(i*PI*2/(360));
    ynew = 1000*sin(i*PI*2/(360));
    //delay(50);
    moveMotor();
  }  
    xnew = 0;
    ynew = 0;
    moveMotor();
  }
  else
  {
    xnew = 0;
    ynew = 0;
    moveMotor();
  } 
}

void loop() {
  if(stringComplete == true)
  {
    Serial.println("Wait");
    stringComplete = false;
    stringParse();
    //  Serial.print("X:"+ (String)xpos);
    //  Serial.println(" Y:" + (String)ypos);
    moveMotor();
    instruction = "";
    Serial.println("Done");
  }
}

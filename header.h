#include <Stepper.h>

#define STEPS 2048 // Steps Per Rev  ... 360/Stride Angle * Gear Ratio... (360/5.625)*64

void stringParse();
String moveMotor();  //moves x and y pos

Stepper stepperX(STEPS,12,10,11,13);
Stepper stepperY(STEPS,4,2,3,5);

String instruction = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
float xpos = 0, ypos = 0;       // current pos of respective motors
float xnew, ynew;              // position to move to
int xspeed=10, yspeed=10;

void serialEvent()
{
  char c;
  while(Serial.available() == true)
  {
     c = Serial.read();
     instruction += c;
     if ( c == '\n')
        stringComplete = true;
  }
}


void stringParse()
{
  Serial.println("Entering String Processing");
  String xchar = "";
  String ychar = "";
  int i = 0;
  while( i < instruction.length())
  {
   switch(instruction[i])
   {
     case 'X':
      // Serial.print("Found a X ");
       while(instruction[i] != ' ')
       {
          i++;
          xchar += instruction[i];
       }
      // Serial.println(xchar);
        break;
      case 'Y':
       // Serial.print("Found a Y ");
        while(instruction[i] != ' ')
        {
          i++;
          ychar += instruction[i];
        }
     //   Serial.println(ychar);
        break;
      case '@':
       // Serial.println("End of Line");
        i = instruction.length(); 
        break;
      default:
        i++;
    }
  }
  //Serial.println("Finished Processing Insturction Data");
  xnew = xchar.toInt();
  ynew = ychar.toInt();
  return NULL;
}

String moveMotor()
{
  int dx,dy;
  // gets the change needed to move for each motor
  dx = xnew - xpos;       
  dy = ynew - ypos;  
  Serial.println("Moving to X:" +String(dx)+" Y:" + String(dy));
  // 2 ways to accomplish.
  // 1. step speeds respectivly and move motors required steps
  // 2. move motors x axis the y axis, making a staircase

  //type 1...     // current wont work, because you cant drive both motors at the same time without hardware implementation
  /// Math comes out to.. if dx/dt is constant 
  // dy/dt = xspeed * slope.. dy/dt = dx/dt * dy/dx
  /*
  if(dx > dy)
  {
    xspeed = 1;
    yspeed = xspeed * slope;
  //  stepperX.setSpeed(xspeed);
  // stepperY.setSpeed(yspeed);
    stepperX.step(dx);
    stepperY.step(dy);
    return "Done";
  }
  else 
  {
    yspeed = 1;
    xspeed = yspeed * 1/slope;
   // stepperX.setSpeed(xspeed);
    //stepperY.setSpeed(yspeed);
    stepperX.step(dx);
    stepperY.step(dy);
    return "Done";
  }
//---------------------------------------------------------------------
  // type 2...
  // dy/dx = .5 then move x 2 times, then move y 1.... 
  // advantages... constant speed for x and y. 
  */
  while(dx != 0 | dy != 0)
  {
    if(abs(dy) > abs(dx))
    {
       if(dx != 0)   // if not moving in a vertical line
       {
          stepperY.step(dy/dx);
          dy -= dy/dx;
          if( dx > 0)
          {
            stepperX.step(1);
            dx -= 1;
          }
          else 
          {
            stepperX.step(-1);
            dx += 1;
          }
         }
         else {
            stepperY.step(dy);
            dy = 0;
       }
    }
    else 
    {
       if(dy != 0)   // if not moving in a vertical line
       {
          stepperX.step(dx/dy);
          dx -= dx/dy;
          if( dy > 0)
          {
            stepperY.step(1);
            dy -= 1;
          }
          else 
          {
            stepperY.step(-1);
            dy += 1;
          }
       }
       else {
          stepperX.step(dx);
          dx = 0;
       }
    }
  }
  return("Done");
}

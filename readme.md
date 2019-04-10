Plotter for Etch a Sketch.
=======
using Arduino Uno and 2 stepper motors


Project by: Basem Khan & Omer Khan

## GCodeSender:  (Mostly Complete)
   * Visual Studio 2017 C++ file
   * Used to transmit from a .txt file to the Arduino line by line
   * It creates a linked list of the information
   * Establishes a connection with an Arduino and a user defined port
   * Then sends each line 1 by 1, waiting for the Arduino to report "Done" after each command

## Arduino Code:
  * Currently Running only on X,Y coordinate basis
  * Example Input: X1000 Y1000 @
  * Where @ is the endline symbol and 1000 is the number of steps for the motor
  * Current Build is based on a XY coordinate system, where 0,0 is set when the Arduino Starts

## PCD Design:
  * Designed in Eagle, using SparksFun library
  * Rough Schematic Design to be used with the ULN2003 Darlington Array Transistors
  * Schematic Design still needs to be verified once more
  * Routing for the PCB needs to be improved on
  * Currently has connectors for the JST connectors that are on the StepperMotors
  * as well and designated traces for adding a dipSwitch and analogStick 
  * Needs to be Sized to fit the arduino, to be a proper Shield

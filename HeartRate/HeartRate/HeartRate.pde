// Shashank Nagaraja Gargeshwari
// OCAD | NID | April 2018 
// Body Centric Technologies

// Sketch to control and visualize a variable heart beat haptic motor

import processing.serial.*;

// Variable that sets the current heartRate
byte heartRate = 127;

// The port over which Serial communication with processing is running
Serial myPort;

void setup()
{
  // Set up size of the screen
  size(900,900);
  
  // Set textSize 
  textSize(64);
  
  // Set up Serial Communication with Arduino
  myPort = new Serial(this, "COM3", 9600);
}

void draw()
{
  clear();
  // Calculate heartRate based on Mouse Pointer
  heartRate = (byte)map(mouseX, 0 , 900 , 0 , 127);
  
  println(heartRate);
  text(heartRate+60,450,450, 300);
  // Send this byte-sized heartRate value over serial to Arduino so that it can update itself
  myPort.write(heartRate);
}
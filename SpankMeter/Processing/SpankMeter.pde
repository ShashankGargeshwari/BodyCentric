// SpankMeter
// Shashank Gargeshwari
// A Program to visualize the power of a spank.



import processing.serial.*;

// The port over which Serial communication with processing is running
Serial myPort;

// A string to store the data coming in from the serial port
String inBuffer;

// Scale factor to scale the Heart Sprite and Text
PImage heart;

void setup() {
  size(1000,1000);
  smooth();
  
 // Import heart image 
  heart = loadImage("heart.png");
 
 // Set up Serial Communication with Arduino
  myPort = new Serial(this, "COM3", 9600);
}

void draw() {
  background(255);


  // Get Data from Serial Port
  while (myPort.available() > 0) {
    inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println("Buffer" + inBuffer);
    image(heart, width/2 , height/2 , float(inBuffer)/150 , float(inBuffer)/150);
    }
  }
  

}
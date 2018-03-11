// The Nature of Code
// <http://www.shiffman.net/teaching/nature>
// Spring 2011
// Box2DProcessing example

// Basic example of falling rectangles

// Additions by Shashank Gargeshwari :
// this example has been repurposed to take inputs from an Arduino Board to control the game.
// Boxes will be spawned from the top and a player has to catch them by bouncing their legs around.
// A percentage score will be maintained for how many boxes were caught by the player


import shiffman.box2d.*;
import org.jbox2d.collision.shapes.*;
import org.jbox2d.common.*;
import org.jbox2d.dynamics.*;
import processing.serial.*;

// Class to represent knees in the Air Swipe Game
// A knee has a Boundary (Box2D)
class Knee
{
  // The boundary associated with a knee that will be used for collisions by the Box2D World
  Boundary b;
  
  // Width of the knee
  int w;
  
  // Height of the knee
  int h;
  
  // X Location of the knee
  int x;
  
  // y location of the knee
  int y;
  
  // Instantiate a knee with predefined data
  public Knee(int x, int y, int w , int h)
  {
    this.w = w;
    this.h = h;
    this.x = x;
    this.y = y;
    b = new Boundary(x+w/2,y,w,h);
  }
  
  // When the knee is activated, a boundary is added to the world
  public void activate()
  {
    b.y = y + 100;
  }
  
  // When the knee is deactivated, the boundary is removed from the world
  public void deactivate()
  {
    if(b != null)
    {
      b.y = y;
    }
  }
  
  // Function to display Knee
  public void display()
  {
    b.update();
    b.display();
  }
  
}

// A reference to our box2d world
Box2DProcessing box2d;

// A list we'll use to track fixed objects
ArrayList<Boundary> boundaries;
// A list for all of our rectangles
ArrayList<Box> boxes;
// A list of all the knees in the game
ArrayList<Knee> knees;


// The port over which Serial communication with processing is running
Serial myPort;

// A string to store the data coming in from the serial port
String inBuffer;

void setup() {
  size(600,360);
  smooth();

  // Initialize box2d physics and create the world
  box2d = new Box2DProcessing(this);
  box2d.createWorld();
  // We are setting a custom gravity
  box2d.setGravity(0, -10);

  // Create ArrayLists	
  boxes = new ArrayList<Box>();
  boundaries = new ArrayList<Boundary>();
  knees = new ArrayList<Knee>();
  // Add a bunch of fixed boundaries
  knees.add(new Knee(0,height-5,width/6,30));
  knees.add(new Knee(width/6 ,height-5,width/6,30));
  knees.add(new Knee(width/3,height-5,width/6,30));
  knees.add(new Knee(width/2,height-5,width/6,30));
  knees.add(new Knee(2 * width/3,height-5,width/6,30));
  knees.add(new Knee(5 * width / 6,height-5,width/6,30));
  
  knees.get(2).activate();
  
  //box2d.destroyBody(boundaries.get(1).b);
    
  // Set up Serial Communication with Arduino
  myPort = new Serial(this, "COM3", 9600);
}

void draw() {
  background(255);

  // We must always step through time!
  box2d.step();
  
  // Get Data from Serial Port
  while (myPort.available() > 3) {
    inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println("Buffer" + inBuffer);
    }
  }
  
  // Activate knees based on Serial data
  for(Knee k: knees)
  {
    k.deactivate();
    
    if(random(1) < 0.004)
    {
      //k.activate();
    }
  }
  
  // Check for activation status and activate knees
    if(inBuffer != null)
    {
      println("InBuffer Value Currenlty " + inBuffer + inBuffer + inBuffer);
      
      // Detect inputs from left knee and activate accordingly
      if(inBuffer.substring(0,2).equals("10"))
      {
        knees.get(0).activate();
        println("YAASS");
      }
      else
      if(inBuffer.substring(0,2).equals("11"))
      {
         knees.get(1).activate();
      }
      else
      if(inBuffer.substring(0,2).equals("01"))
      {
         knees.get(2).activate();
      }
      
      // Detect inputs from right knee and activate accordingly
      if(inBuffer.substring(2).equals("10"))
      {
        knees.get(3).activate();
        println("YAASS");
      }
      else
      if(inBuffer.substring(2).equals("11"))
      {
         knees.get(4).activate();
      }
      else
      if(inBuffer.substring(2).equals("01"))
      {
         knees.get(5).activate();
      }
    }
    else
    {
      print("Nahhh");
    }
  
  // Boxes fall from the top every so often
  if (random(1) < 0.01) {
    Box p = new Box(width/2,30);
    boxes.add(p);
  }

  // Display all the boundaries
  for (Boundary wall: boundaries) {
  wall.display();
  }
  
  for(Knee k : knees)
  {
    k.display();
  }

  // Display all the boxes
  for (Box b: boxes) {
    b.display();
  }

  // Boxes that leave the screen, we delete them
  // (note they have to be deleted from both the box2d world and our list
  for (int i = boxes.size()-1; i >= 0; i--) {
    Box b = boxes.get(i);
    if (b.done()) {
      boxes.remove(i);
    }
  }
}
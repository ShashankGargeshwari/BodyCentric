/***************************************************
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution


  Additions By Shashank Gargeshwari :
  The original file has been repurposed to detect input from a 9 key touchpad. 
  Since the capacitive sensor has only 8 capPads/Inputs, one might wrongly assume 
  that the maximum number of inputs one can get from the sensor is 8. Infact, for
  a sensor with n inputs, it is actually (2^n - 1). So this sensor can ideally detect 
  255 inputs. This is done by multiplexing each capacitive pad so that it can be 
  determined which location is being activated. 

  For this example, a 9 key has been selected to showcase the idea without the 
  increased complexity of actually implementing a 255 point input pad.
  4 capPad are needed to recieve inputs from a 9 key input system.
 ****************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
//Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

int capPad[8];

void setup() {
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
  pinMode(13, OUTPUT);

  // Reset the Capacitive Sensor
  digitalWrite(CAP1188_RESET,HIGH);
  digitalWrite(CAP1188_RESET,LOW);
}

void clear()
{
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
}
void loop() {

  // clear screen
  //clear();
  
  byte touched = cap.touched();
  
  //capture values of capacitive sensors in an array
  for (byte i = 0; i < 8; i++) {
    byte mask = 1 << i; 
    if (touched & mask) { 
      capPad[i] = 1;
    } else {
      capPad[i] = 0;
    }

    // Find out which key is being touched
    // Note that four capPads are being used. If they are p0, p1, p2 and p3, then the board is wired up to respond 
    // when the pads are activated in the following way
    // -------------------------------- 
    //|    p0    |    p3    |    p2    |
    // --------------------------------
    //|  p2,p3   |    p1    |  p1,p3   |
    // --------------------------------
    //|  p1,p2   | p1,p2,p3 |  p0,p2   |
    // --------------------------------
       //Serial.println("*");
    if(capPad[0] == 0 )
    {
      // If the capPad[0] is 0, that means that the pad is either not being touched or it is one of the 7 keys the 3 Caps can represent.
      int num = 4 * capPad[1] + 2 * capPad[2] + capPad[3];

      switch(num)
      {
        case 0 : Serial.println("000"); Serial.println("000"); Serial.println("000"); 
        break;
        case 1 : Serial.println("010"); Serial.println("000"); Serial.println("000"); 
        break;
        case 2 : Serial.println("001"); Serial.println("000"); Serial.println("000"); 
        break;
        case 3 : Serial.println("000"); Serial.println("100"); Serial.println("000"); 
        break;
        case 4 : Serial.println("000"); Serial.println("010"); Serial.println("000"); 
        break;
        case 5 : Serial.println("000"); Serial.println("001"); Serial.println("000"); 
        break;
        case 6 : Serial.println("000"); Serial.println("000"); Serial.println("100"); 
        break;
        case 7 : Serial.println("000"); Serial.println("000"); Serial.println("010"); 
        break;
      }
    }
    else
    {
      // If capPad[0] is 1, then it is either the key where all other capPads are zero, or the 9th key.
      switch(capPad[2])
      {
        case 0 : Serial.println("100"); Serial.println("000"); Serial.println("000"); 
        break;
        case 1 : Serial.println("000"); Serial.println("000"); Serial.println("001"); 
        break;
      }
    }
 
  }

  // Delay for apparently stability purposes
   delay(50);
}


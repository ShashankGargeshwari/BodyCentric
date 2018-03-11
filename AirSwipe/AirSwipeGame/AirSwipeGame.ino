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
  The original file has been repurposed to detect input from 4 Pad Hover sensors.
  These senors consist of large patches of aluminium foil hooked up to the capacitive sensor.
  The aluminium foil patches can be activated by bodies from a distance.

  This particular example is tailored to detect input from 4 sensors and push their activation
  state date onto the Serial line. 
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
  }
    // Find out which pad is being activated. For this case, the highest 8 bits are being used. 
    // Serial Data is being pushed in the order 8,7,6,5
    String activationPattern = String(capPad[7]) + String(capPad[6]) +  String(capPad[5]) +  String(capPad[4]);
    
    Serial.print(activationPattern);

  // Delay for apparently stability purposes
   delay(50);
}


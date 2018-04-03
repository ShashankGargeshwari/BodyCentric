#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

uint8_t effect = 1;

byte heartRate = 10;

float lastBeatMillis = 0;
float nextBeatMillis = 0;

void loop() 
{
  // Read the heartRate from the Processing sketch
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    heartRate = Serial.read();
    heartRate += 60;

    Serial.println(heartRate);
  }

  // If time is greater than scheduled beat, beat
  if(millis() > nextBeatMillis)
  {
    // set the effect to play
    drv.setWaveform(0, 10);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
  
    // play the effect!
    drv.go();
    lastBeatMillis = millis();
  
    int delayTime = ((60.0/heartRate)*1000);

    // Schedule next beat
    nextBeatMillis = lastBeatMillis + delayTime;
  }
  
}

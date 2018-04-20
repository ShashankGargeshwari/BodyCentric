#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <SoftwareSerial.h>
#include <SerialCommand.h>

SerialCommand sCmd;

Adafruit_DRV2605 drv;

void pingHandler(const char *command)
{
  Serial.println("PONG");
}

void echoHandler () {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL)
    Serial.println(arg);
  else
    Serial.println("nothing to echo");
}

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(1);
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 

  pinMode(LED_BUILTIN, OUTPUT);
  /* while (!Serial);
 
   sCmd.addCommand("PING" , pingHandler);*/
}

uint8_t effect = 1;

byte heartRate = 10;

float lastBeatMillis = 0;
float nextBeatMillis = 0;

void loop() 
{
  // Read the heartRate from the Processing sketch
  bool heartBeatChanged = false;
  /*if (Serial.available() > 0)
    sCmd.readSerial();*/

    if (Serial.available() > 0) {

      while(Serial.available() > 0)
        heartRate = Serial.read();
        heartBeatChanged = true;
         // read the incoming byte:
        // heartRate = Serial.read();

              if(heartRate != 0)
                 heartRate += 60;
                 else
                 heartRate = 1;
                    //echoHandler();
    //heartRate = 0;
    }

    //Serial.println(heartRate);
  
 int delayTime = 0;
  // If time is greater than scheduled beat, beat
  if(millis() > nextBeatMillis && heartRate != 1 || heartBeatChanged)
  {
    if( heartRate == 90) // Hurt
    {
    // set the effect to play
    drv.setWaveform(0, 1);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    }
    else
    if( heartRate == 80) // Attack
    {
    // set the effect to play
    drv.setWaveform(0, 52);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    }
    else
    if( heartRate == 110) // Attack
    {
    // set the effect to play
    drv.setWaveform(0, 44);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    }
    else
    if( heartRate == 100) // Jump
    {
    // set the effect to play
    drv.setWaveform(0, 47);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    }else
    {
    // set the effect to play
    drv.setWaveform(0, 10);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
     delayTime = ((60.0/heartRate)*1000);

    // Schedule next beata
    
    }
    
    // play the effect!
    drv.go();
    lastBeatMillis = millis();

    nextBeatMillis = lastBeatMillis + delayTime;
    
  }
  
}

#include<Wire.h>
#include "Adafruit_DRV2605.h"

// Sketch to take an input from the Capacitve sensor and 
//activate the vibrator motor according to preassure

int vibratorPin = 2;
int analogPin= 0;
int raw= 0;
int Vin= 5;
float Vout= 0;
float R1= 1000;
float R2= 0;
float buffer= 0;
float maxR;
float minR;
bool thresholdPassed;
bool maxReached;
float prevR;

void setup()
{
Serial.begin(9600);
minR = 900000;
maxR = 0;
thresholdPassed = false;
maxReached = false;
}

void loop()
{
raw= analogRead(analogPin);
if(raw) 
{
buffer= raw * Vin;
Vout= (buffer)/1024.0;
buffer= (Vin/Vout) -1;
R2= R1 * buffer;
int k=map(R2, 0, 1000, 0, 255);
analogWrite(vibratorPin,255);
Serial.println(R2);

}
delay(10);
}



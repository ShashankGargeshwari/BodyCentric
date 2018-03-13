int analogPin= 0;
int raw= 0;
int Vin= 5;
float Vout= 0;
float R1= 1000;
float R2= 0;
float buffer= 0;
float maxR;
float minR;
float threshold;
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
threshold = 100;
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
if(!thresholdPassed)
{
  if(R2>threshold)
  {
    thresholdPassed = true;
    prevR = R2;
  }
}
if(thresholdPassed)
{
  if(R2>=prevR)
  {
    prevR = R2;
    maxR = R2;
  }
  else
  {
    if(R2 > threshold)
    {
      if(!maxReached)
      {
        maxR = R2;
      }
           
    }
    else
    {
      Serial.println(maxR);
      maxR = 0;
      prevR = 0;
      
      thresholdPassed = false;
      maxReached = false;
    }
  }
  
}

}
delay(1);
}



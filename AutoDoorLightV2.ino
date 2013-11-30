//Name: AutoDoorLightV2
//Describe: Project for detect when door is open, auto bright the light when environment is under dark.
//Author: Josh Chen
//Change Log:
//  2013-11-30: Initial version

//Define Limit Value
#define CDS_DARK_LIMIT  700
#define RELAY_TIMEOUT  30

//Pin Assignment
const byte cdsPin = 3;
const byte reedPin = 0;
const byte relayPin = 2;

//Global Variable
boolean lightIsBright = false;
unsigned int lightCounter = 0;

//Function for start
void setup()
{
  pinMode(cdsPin, INPUT);
  pinMode(reedPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

//Function for detect briteness of environment
boolean envIsDark()
{
  unsigned int cdsRate = analogRead(cdsPin);
  return (cdsRate >= CDS_DARK_LIMIT);
}

//Function for detect is door opened
boolean doorIsOpen()
{
  boolean reedStatus = digitalRead(reedPin);
  if (reedStatus == false)
    return false;

  //Debounce after 10ms
  delay(10);
  reedStatus = digitalRead(reedPin);
  return reedStatus;
}

//Function for routing
void loop()
{
  if (doorIsOpen())  //When door is opened, go to detect environment
  {
    if ((lightIsBright == false) && envIsDark())  //When environment is under dark, go to turn on light
    {
      digitalWrite(relayPin, HIGH);
      lightIsBright = true;
    }
    lightCounter = 0;
  }
  else if (lightIsBright == true)  //When door is closed, go to detect lighting counter
  {
    if (lightCounter >= RELAY_TIMEOUT)  //When lighting counter over limit, go to turn off light
    {
      digitalWrite(relayPin, LOW);
      lightIsBright = false;
      lightCounter = 0;
    }
    lightCounter++;
  }
  delay(1000);  //Detect cycle = 1 second
}


// setting pins
const int ledPin = 13;  // led
const int bzzPin = 12;  // buzzer
const int mtrPin = 11;  // motor
const int dbgPin = 10;  // indicator that the PIR is high
const int inputPin = 2; // input of PIR

int PIRstate = LOW;    // state of sensor
int animation = LOW;   // animation flag
int val = 0;           // store the dig read of sensor
int animLength = 100;  // how long the animation runs for
int animCount = 0;     // counter

int ledState = LOW;    // initial state of led pin
int ledInterval = 10;  // interval of led (going to millis())
int ledCount = 0;      // counter for led (also going to millis())
int bzzState = LOW;    // etc...
int bzzInterval = 15;
int bzzCount = 0;
int mtrState = LOW;
int mtrInterval = 25;
int mtrCount = 0;

void setup()
{
  // set up pins
  pinMode(ledPin,OUTPUT);
  pinMode(bzzPin,OUTPUT);
  pinMode(mtrPin,OUTPUT);
  pinMode(dbgPin,OUTPUT);
  pinMode(inputPin,INPUT);

  // so we can trace out our values
  Serial.begin(9600);
}

void loop()
{
  // read if PIR senses something
  val = digitalRead(inputPin);

  if(val == HIGH)
  {
    // it does! kick off animation
    digitalWrite(dbgPin,HIGH);
    PIRstate = HIGH;
  }
  else
  {
    // sense timed out, 
    digitalWrite(dbgPin,LOW);
    PIRstate = LOW;
  }

  // turning on the animation
  if(PIRstate == HIGH && animation == LOW)
  {
    // this is the state where animation has not been running but PIR has sensed something
    animation = HIGH;        // set animation flag to running
    animCount = animLength;  // set the counter for the animation
    ledState = HIGH;         // turn on the flag for the led, etc...
    bzzState = HIGH;
    mtrState = HIGH;
    ledCount = ledInterval;  // set the counter for the led, etc...
    bzzCount = bzzInterval;
    mtrCount = mtrInterval;
  }
  else if(PIRstate == HIGH && animation == HIGH)
  {
    // PIR sensed something and the animation timer is running
  }
  else if(PIRstate == LOW && animation == HIGH )
  {
    // PIR stopped sensing and animation timer is running
  }
  else if(PIRstate == LOW && animation == LOW)
  {
    // PIR stopped sensing and animation timer is done
    ledState = LOW; // turn off the flag for the led, etc...
    bzzState = LOW;
    mtrState = LOW;
  }

  if(animation == HIGH)
  {
    // do animation
    doLEDAnimation();
    doBzzAnimation();
    doMtrAnimation();

    animCount--;  // subtract one from the animation counter
    if(animCount == 0) // if the counter has run out
    {
      animation = LOW; // set the animation flag to low
    }
  }
  else
  {
    // animation is over set everything to LOW
    animation = LOW;
    ledState = LOW;
    bzzState = LOW;
    mtrState = LOW;
  }

  Serial.print(PIRstate);
  Serial.print("::");
  Serial.print(animation);
  Serial.print("::");
  Serial.print(ledCount);
  Serial.print("::");
  Serial.print(ledState);
  Serial.print("::");
  Serial.print(count);
  Serial.println(" ");

  digitalWrite(ledPin,ledState);
  digitalWrite(bzzPin,bzzState);
  digitalWrite(mtrPin,mtrState);

}

void doLEDAnimation()
{
  // if the led counter has run out
  if(ledCount == 0)
  {
    ledState = !ledState;   // set the state of the led to its opposite
    ledCount = ledInterval; // reset the counter
  }
  ledCount--; // decrement the counter
}

void doBzzAnimation()
{
  if(bzzCount == 0)
  {
    bzzState = !bzzState;
    bzzCount = bzzInterval;
  }
  bzzCount--;
}

void doMtrAnimation()
{
  if(mtrCount == 0)
  {
    mtrState = !mtrState;
    mtrCount = mtrInterval;
  }
  mtrCount--;
}

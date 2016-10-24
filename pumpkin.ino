// setting pins
const int ledPin = 13;  // led
const int bzzPin = 12;  // buzzer
const int mtrPin = 11;  // motor
const int dbgPin = 10;  // indicator that the PIR is high
const int flmPin = 9;   // glow of pumpkin
const int inputPin = 2; // input of PIR

int PIRstate = LOW;    // state of sensor
int animation = LOW;   // animation flag
int val = 0;           // store the dig read of sensor
const long animLength = 10000;  // how long the animation runs for (10 seconds)
long animMillis = 0;     // counter

const long ledInterval = 100;  // duty cycle of led (.1 second)
long ledMillis = 0;            // holder for millis at trigger
int ledState = LOW;            // initial state of led pin

const long bzzInterval = 500;  // .5 seconds
long bzzMillis = 0;
int bzzState = LOW;

const long mtrInterval = 250;  // .25 seconds
long mtrMillis = 0;
int mtrState = LOW;

const long flmIntervalHigh = 1000; // 1 second on
const long flmIntervalLow = 250;   // .25 seconds off
long flmMillis = 0;
int flmState = LOW;

// counter to stagger the motor animation
int mtrCounter = 250;
int mtrAnim = HIGH;

void setup()
{
  // set up pins
  pinMode(ledPin,OUTPUT);
  pinMode(bzzPin,OUTPUT);
  pinMode(mtrPin,OUTPUT);
  pinMode(dbgPin,OUTPUT);
  pinMode(flmPin,OUTPUT);
  pinMode(inputPin,INPUT);

  // so we can trace out our values
  //Serial.begin(9600);
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
    animMillis = millis();   // set the current millis for the animation
    ledMillis = millis();    // set the current millis for the led, etc...
    bzzMillis = millis();
    mtrMillis = millis();
    flmMillis = millis();
    ledState = HIGH;         // turn on the flag for the led, etc...
    bzzState = HIGH;
    mtrState = HIGH;
    flmState = HIGH;
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
    // do calculations of states
    doLEDAnimation();
    doBzzAnimation();
    doMtrAnimation();
    doFlmAnimation();

    unsigned long currentMillis = millis();
    if(currentMillis - animMillis > animLength) // if the calculated period is greater than the set length
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
    flmState = LOW;
  }

  // write the states to the pins
  digitalWrite(ledPin,ledState);
  digitalWrite(bzzPin,bzzState);
  digitalWrite(mtrPin,mtrState);
  digitalWrite(flmPin,flmState);

}

void doLEDAnimation()
{
  unsigned long currentLedMillis = millis();
  if(currentLedMillis - ledMillis > ledInterval)  // if the elapsed period is greater than the set period
  {
    ledState = !ledState;   // set the state of the led to its opposite
    ledMillis = millis();   // reset to the current millis
  }
}

void doBzzAnimation()
{
  unsigned long currentBzzMillis = millis();
  if(currentBzzMillis - bzzMillis > bzzInterval)
  {
    bzzState = !bzzState;
    bzzMillis = millis();
  }
}

void doMtrAnimation()
{
  // stagger the animation of the motor with a counter and a flag
  if(mtrCounter > 0 && mtrAnim == HIGH)
  {
    unsigned long currentMtrMillis = millis();
    if(currentMtrMillis - mtrMillis > mtrInterval)
    {
      mtrState = !mtrState;
      mtrMillis = millis();
    }
  }

  if(mtrCounter == 0)
  {
    mtrAnim = !mtrAnim;
    mtrState = LOW;
    mtrCounter = 250;
  }

  mtrCounter--;
}

void doFlmAnimation()
{
  // we want the LED to have a long on time with a short flash off
  unsigned long currentFlmMillis = millis();
  if(flmState == HIGH)
  {
    if(currentFlmMillis - flmMillis > flmIntervalHigh)
    {
      flmState = LOW;
      flmMillis = millis();
    }
  }
  else
  {
    if(currentFlmMillis - flmMillis > flmIntervalLow)
    {
      flmState = HIGH;
      flmMillis = millis();
    }
  }
}

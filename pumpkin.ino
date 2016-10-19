// setting pins
const int ledPin = 13;  // led
const int bzzPin = 12;  // buzzer
const int mtrPin = 11;  // motor
const int dbgPin = 10;  // indicator that the PIR is high
const int inputPin = 2; // input of PIR

int PIRstate = LOW;    // state of sensor
int animation = LOW;   // animation flag
int val = 0;           // store the dig read of sensor
const long animLength = 10000;  // how long the animation runs for (10 seconds)
long animMillis = 0;     // counter

int ledState = LOW;    // initial state of led pin
const long ledInterval = 100;  // interval of led (going to millis())
long ledMillis = 0;      // counter for led (also going to millis())
int bzzState = LOW;    // etc...
const long bzzInterval = 500;
long bzzMillis = 0;
int mtrState = LOW;
const long mtrInterval = 250;
long mtrMillis = 0;

int mtrCounter = 250;
int mtrAnim = HIGH;

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
    animMillis = millis();   // set the counter for the animation
    ledState = HIGH;         // turn on the flag for the led, etc...
    bzzState = HIGH;
    mtrState = HIGH;
    ledMillis = millis();    // set the counter for the led, etc...
    bzzMillis = millis();
    mtrMillis = millis();
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

    unsigned long currentMillis = millis();
    if(currentMillis - animMillis > animLength) // if the counter has run out
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


  digitalWrite(ledPin,ledState);
  digitalWrite(bzzPin,bzzState);
  digitalWrite(mtrPin,mtrState);

}

void doLEDAnimation()
{
  // if the led counter has run out

  unsigned long currentLedMillis = millis();
  if(currentLedMillis - ledMillis > ledInterval)
  {
    ledState = !ledState;   // set the state of the led to its opposite
    ledMillis = millis(); // reset the counter
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
    mtrCounter = 250;
    mtrState = LOW;
    mtrAnim = !mtrAnim;
  }
Serial.print(mtrCounter);
Serial.print("::");
Serial.println(mtrAnim);
  mtrCounter--;
}

int ledPin = 13;
int bzzPin = 12;
int mtrPin = 11;
int dbgPin = 10;

int inputPin = 2;
int PIRstate = LOW;
int animation = LOW;
int val = 0;
int countLength = 100;
int count = 0;

int ledState = LOW;
int ledInterval = 10;
int ledCount = 0;
int bzzState = LOW;
int bzzInterval = 15;
int bzzCount = 0;
int mtrState = LOW;
int mtrInterval = 25;
int mtrCount = 0;

void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(bzzPin,OUTPUT);
  pinMode(mtrPin,OUTPUT);
  pinMode(dbgPin,OUTPUT);
  pinMode(inputPin,INPUT);

  Serial.begin(9600);
}

void loop()
{
  // read if PIR senses
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
    animation = HIGH;
    count = countLength;
    ledState = HIGH;
    bzzState = HIGH;
    mtrState = HIGH;
    ledCount = ledInterval;
    bzzCount = bzzInterval;
    mtrCount = mtrInterval;
  }
  else if(PIRstate == HIGH && animation == HIGH)
  {

  }
  else if(PIRstate == LOW && animation == HIGH )
  {
    
  }
  else if(PIRstate == LOW && animation == LOW)
  {
    ledState = LOW;
    bzzState = LOW;
    mtrState = LOW;
  }

  if(animation == HIGH)
  {
    // do animation
    doLEDAnimation();
    doBzzAnimation();
    doMtrAnimation();

    count--;
    if(count == 0)
    {
      animation = LOW;
    }
  }
  else
  {
    // set everything to LOW
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
  if(ledCount == 0)
  {
    ledState = !ledState;
    ledCount = ledInterval;
  }
  ledCount--;
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

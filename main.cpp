// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int greenLed = 13;
const int yelLed = 12;
const int redLed = 11;
const int  buttonPin = 2;
const long firstCheck = 2000;
const long secondCheck = 4000;
const long finalCheck = 5000;

enum State { green, yellow, red, critical };
State state = green;
unsigned long startTime=0;

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(yelLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  checkButton();
  determineState();
  switchLed();
}

void checkButton() {
  if(isButtonPressed()) {
    resetLights();
    delay(100); // debounce
  }
}

bool isButtonPressed() {
  return digitalRead(buttonPin) == true;
}

void determineState() {
  unsigned long timePassed = calcPassedTime(startTime);
  if(timePassed >= finalCheck)
  {
    state = critical;
  }
  else if(timePassed >= secondCheck)
  {
    state = red;
  }
  else if(timePassed >= firstCheck)
  {
    state = yellow;
  }
  else 
  {
    state = green;
  }
}

void switchLed() {
  switch(state)
  {
    case green : redOff(); yellowOff(); greenOn(); break;
    case yellow : redOff(); yellowOn(); greenOff(); break;
    case red : redOn(); yellowOff(); greenOff(); break;
  }
}

void greenOn() {
  digitalWrite(greenLed, true);
}

void greenOff() {
  digitalWrite(greenLed, false);
}

void yellowOn() {
  digitalWrite(yelLed, true);
}

void yellowOff() {
  digitalWrite(yelLed, false);
}

void redOn() {
  digitalWrite(redLed, true);
}

void redOff() {
   digitalWrite(redLed, false);
}

unsigned long calcPassedTime(unsigned long previous) {
  return (unsigned long)(millis() - previous);
}

void resetLights() {
  startTime = millis();
}

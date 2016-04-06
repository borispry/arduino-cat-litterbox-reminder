// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int greenLed = 13;
const int yelLed = 12;
const int redLed = 11;
const int  buttonPin = 2;
const long firstCheck = 2000;
const long secondCheck = 4000;
const long finalCheck = 5000;

unsigned long startTime = 0;
unsigned long previousMillisYel=0;
unsigned long previousMillisRed=0;
bool isYellowOn = false;
bool isRedOn = false;

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(yelLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  checkButton();
  checkGreenLed();
  checkYellowLed();
  checkRedLed();
}

void checkButton() {
  if( digitalRead(buttonPin) == true  ) {   // button is pressed
        resetLights();
        delay(100); // debounce
  }
}

void checkGreenLed() {
  if (needToTurnOnGreen()) {
      greenOn();
  }
}

bool needToTurnOnGreen() {
  return (!isYellowOn && !isRedOn);
}

void checkYellowLed() {
  if (needToTurnOnYellow()) {
      yellowOn();
  }
}

bool needToTurnOnYellow() {
  unsigned long timePassedYel = calcPassedTime(previousMillisYel);
  return (!isYellowOn && !isRedOn && timePassedYel >= firstCheck);
}

void checkRedLed() {
  if (needToTurnOnRed()) {
      redOn();
  }
}

bool needToTurnOnRed() {
  unsigned long timePassedRed = calcPassedTime(previousMillisRed);
  return (!isRedOn && timePassedRed >= secondCheck);
}

void greenOn() {
  digitalWrite(greenLed, true);
}

void greenOff() {
  digitalWrite(greenLed, false);
}

void yellowOn() {
  digitalWrite(yelLed, true);
  previousMillisYel = millis();
  isYellowOn = true; 
  greenOff();
}

void yellowOff() {
  digitalWrite(yelLed, false);
  previousMillisYel = millis();
  isYellowOn = false;
}

void redOn() {
  digitalWrite(redLed, true);
  previousMillisRed = millis();
  isRedOn = true;
  yellowOff(); 
  greenOff();
}

void redOff() {
   digitalWrite(redLed, false);
  previousMillisRed = millis();
  isRedOn = false; 
}

unsigned long calcPassedTime(unsigned long previous) {
  return (unsigned long)(millis() - previous);
}

void resetLights() {
  yellowOff();
  redOff();
}

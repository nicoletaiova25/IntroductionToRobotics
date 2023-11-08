// Declare all the ledsDisplay pins for the 7-segment display
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;

int ledsDisplay[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
/*
const int indexPinA = 0;
const int indexPinB = 1;
const int indexPinC = 2;
const int indexPinD = 3;
const int indexPinE = 4;
const int indexPinF = 5;
const int indexPinG = 6;
const int indexPinDP = 7;*/

///declare a matrix of movement based on the table in the document
///it contains the index of the pins that will light up if they are chosen
///using -1 to if there is no pin that can light up if that direction is chosen
const int directionCount = 4; //up, down, left, right

const int movementMatrix[segSize][directionCount] = {
///  up         down        left        right
 /* {indexPinA, indexPinG, indexPinF,  indexPinB}, //a
  {indexPinA, indexPinG, indexPinF,  indexPinB}, //b
  {indexPinG, indexPinD, indexPinE,  indexPinDP},  //c
  {indexPinG, indexPinD, indexPinE,  indexPinC}, //d
  {indexPinG, indexPinD, indexPinE,  indexPinC}, //e
  {indexPinA, indexPinG, indexPinF,  indexPinB}, //f
  {indexPinA, indexPinD, indexPinG,  indexPinG}, //g
  {indexPinDP,indexPinDP,indexPinC,  indexPinDP}, //dp*/
  {0, 6, 5, 1}, // a  (0)
  {0, 6, 5, 1}, // b  (1)
  {6, 3, 4, 7}, // c  (2)
  {6, 3, 4, 2}, // d  (3)
  {6, 3, 4, 2}, // e  (4)
  {0, 6, 5, 1}, // f  (5)
  {0, 3, 6, 6}, // g  (6)
  {7, 7, 2, 7}  // dp (7)
};
// declare variables for direction to avoid magic numbers
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

//declare the pins for the joystick
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 = analog pin connected to X output
const int pinY = A1; // A1 = analog pin connected to Y output

byte ledState[segSize] = {0}; //0 for OFF, 1 for ON
byte currentLedBlinking = 0;
bool lastButtonState = HIGH;
bool buttonState = HIGH;
bool buttonPressed = false;
unsigned long buttonPressStartTime = 0;
unsigned long lastJoystickTime = 0;
bool joyChangedState = true;
int currentPinIndex = 7; //we're starting on the dp 
const int startPosition = 7;

//declare the time variables
const int debounceInterval = 300;
const int blinkInterval = 500;
unsigned long lastTimeItBlinked = 0;
unsigned long lastTimeItDebounced = 0;
const int joystickTime = 800;
const int resetTime = 3000;

//declare variables for axis magic numbers
const int extremeHigh = 900; /// when hold to extreme right or up, either x or y become ~1023
const int extremeLow = 100; ///when hold to extreme left of down, either x or y become ~ 0 (under 10)
const int holdPositionLess = 400; 
const int holdPositionMore = 600;
/// for the last 2, they serve 3 cases, when on start position both x and y are about 514, 508
/// when taken to the right or up, either x or y go to 510, 515 so I decided to make intervals based on that


void setup() {
  // put your setup code here, to run once:
  for( int i = 0; i < segSize; i++){
    pinMode(ledsDisplay[i], OUTPUT);
  }

  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(pinSW), handleInterrupt, FALLING);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  
  Serial.begin(9600);

  digitalWrite(ledsDisplay[pinDP], HIGH); // Turn on the decimal point
}

void loop() {
  // put your main code here, to run repeatedly:
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);

  //deciding the direction based on the values registered on the joystick
  if (millis() - lastJoystickTime >= joystickTime){
    joyChangedState = false;
    if (xValue > extremeHigh && yValue > holdPositionLess && yValue < holdPositionMore){
      moveLed(movementMatrix[currentPinIndex][UP]); //move position up
      lastJoystickTime = millis();
      joyChangedState = true;
    }
    else if (xValue < extremeLow && yValue > holdPositionLess && yValue < holdPositionMore){
      moveLed(movementMatrix[currentPinIndex][DOWN]); //moves position down
      lastJoystickTime = millis();
      joyChangedState = true;
    }
    else if (yValue < extremeLow && xValue > holdPositionLess && xValue < holdPositionMore){
      moveLed(movementMatrix[currentPinIndex][LEFT]); //move position to the left
      lastJoystickTime = millis();
      joyChangedState = true;
    }
    else if (yValue > extremeHigh && xValue > holdPositionLess && xValue < holdPositionMore){
      moveLed(movementMatrix[currentPinIndex][RIGHT]); //move position to the right
      lastJoystickTime = millis();
      joyChangedState = true;
    }
    
  }

  if (buttonPressed) {
    if (millis() - buttonPressStartTime >= resetTime) {
      // Long press, reset display
      resetingFunc();
      buttonPressed = false;
      //buttonPressStartTime = millis();
    } 
    else if ((millis() - lastTimeItDebounced) > debounceInterval) { //short press
      lastTimeItDebounced = millis();      
      buttonState = digitalRead(pinSW);
      if (buttonState != lastButtonState) {
        ledState[currentPinIndex] = !ledState[currentPinIndex];
        lastButtonState = !lastButtonState;
        buttonPressed = false;
      }
    }
    
  } 
  else {
    buttonPressStartTime = millis();
    buttonPressed = false;
  }

  displayLeds();
  makeItBlink();
}


// Move the segment
void moveLed(int ledToMoveOn) {
  if (ledToMoveOn != currentPinIndex) { 
    currentLedBlinking = ledState[ledToMoveOn]; 
    currentPinIndex = ledToMoveOn;
  }
}

//applies the reseting of the display after the button has been pressed for 4 sec
void resetingFunc() {
  for (int i = 0; i < segSize; i++) {
    ledState[i] = 0; // makes the leds turn OFF
  }
  currentPinIndex = startPosition; // makes the current pin to go back to starting position on dp
}

// function to display the leds
void displayLeds() {
  for (int i = 0; i < segSize; i++) {
    if(i != currentPinIndex)
      digitalWrite(ledsDisplay[i], ledState[i]);
  }
}

// function to make the current led blink
void makeItBlink() {
  if (millis() - lastTimeItBlinked >= blinkInterval) {
    lastTimeItBlinked = millis();
    currentLedBlinking = !currentLedBlinking;
    digitalWrite(ledsDisplay[currentPinIndex], currentLedBlinking);
  }
}

// this is called when the button of the joystick is pressed and the isr occurs
void handleInterrupt() {
  buttonPressed = true;
}
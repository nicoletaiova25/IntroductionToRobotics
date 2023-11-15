// Define connections to the shift register
const int latchPin = 11; // Connects to STCP (latch pin) on the shift register
const int clockPin = 10; // Connects to SHCP (clock pin) on the shift register
const int dataPin = 12; // Connects to DS (data pin) on the shift register

// Define connections to the digit control pins for a 4-digit display
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

// Store the digits in an array for easy access
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; // Number of digits in the display

// Define byte encodings for the hexadecimal characters 0-9
byte byteEncodings[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

// Define a byte encoding for the decimal point (assuming it's controlled by a separate segment)
// made it separate, it didn't want to work when I put it in the byteEncodings[]
byte decimalPoint = B00000001; // Turn on the rightmost segment

//declaring the connection to the buttons and the led
const int buttonPinReset = 8;
const int buttonPinStartPause = 2;
const int buttonPinSaveCycle = 3;

//declare things for the reset button which does NOT have interrupts
byte buttonResetState = HIGH;
//declare things for the used led
const int ledPin = 13;
byte ledState = LOW;

//declaring flag variables to help on conditions
bool hasStarted = false; // keeps track of timer, if timer is counting it becomes true, if not, liike if it is paused, it stays false
bool inPauseMode = false; //remembers if the timer is in pause or not, could have used just hasStarted as well, but I was getting confused and the Arduino too
bool canDisplay = false; //shows if the laps can be displayed or not
bool hasReseted = false; //flags if it's been reseted or not

//declare variables used for interrupts and debounce shit
//for the start/pause button
bool buttonToStartOrPausePressed = false; //checks if the button was or not pressed, initially it isn't
unsigned long lastButtonStartPauseTime = 0; //remembers the time the button was pressed last time
const int startPauseInterval = 100; // debounce interval of button

//for the lap button
bool buttonToSaveAndCyclePressed = false; //checks if the button was or not pressed, initially it isn't
unsigned long lastButtonSaveAndCycleTime = 0; // remembers the time the button was pressed last time
const int saveAndCycleInterval = 500; // debounce interval of button

// Variables for controlling the display update timing
unsigned long lastIncrement = 0;
unsigned long delayCount = 100; // Delay between updates (milliseconds)
unsigned int number = 0; // The number being displayed

//declare variables for button 3, save laps and cycle through laps
const int lapsToSave = 4; 
int saveLap[lapsToSave] = {0}; // an array that will keep the values displayed when the save lap button is pressed while the counter is going
int countLaps = 0; //a counter for the array
int showSavedLap = 0; // a variable that will take the value of the array on a certain position to display 
int countLapPresses = -1; // counter for how many times the button has been pressed
bool inCycleMode = false; 
unsigned long waitingTimeAfterReset = 0;

void setup() {
  // put your setup code here, to run once:
  // Initialize the pins connected to the shift register as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(buttonPinReset, INPUT_PULLUP);
  pinMode(buttonPinStartPause, INPUT_PULLUP);
  pinMode(buttonPinSaveCycle, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPinStartPause), checkStartPause, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPinSaveCycle), checkLapButton, FALLING);

  // Initialize digit control pins and set them to LOW (off)
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  // Begin serial communication for debugging purposes
  Serial.begin(9600);

  // Set the initial state
  setInitialState();

}

void setInitialState() {
  number = 0;
  writeNumber(number);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if the current time is greater than 'lastIncrement' plus 'delayCount'
  if(hasStarted){
    if (millis() - lastIncrement > delayCount) {
      // Increment the number and reset 'lastIncrement'
      number++;
      // Ensure that 'number' wraps around after reaching 9999 to start over from 0
      number %= 10000; // Wrap around after 9999
      lastIncrement = millis();
    }
  }
  if (canDisplay){ // if the saved laps can be displayed
    if(ledState == HIGH){ //if the display has just been reseted and the led is ON, wait a bit to see the 000.0, display the first values, OFF the led
      if( millis() - waitingTimeAfterReset >= 3000){
      displaySavedLaps();
      ledState=LOW;
      digitalWrite(ledPin, ledState);
      waitingTimeAfterReset = millis();
      inCycleMode = true; //make inCycleMode true so the reset knows it can reset this state if button to Reset is pressed
      }
    }
    else{ 
      displaySavedLaps();
    }
  }
  else{
  // Display the incremented number on the 7-segment display using multiplexing
  writeNumber(number);}

  makeItReset();
}

void writeReg(int digit) {
  // Prepare to shift data by setting the latch pin low
  digitalWrite(latchPin, LOW);
  // Shift out the byte representing the current digit to the shift register
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  // Latch the data onto the output pins by setting the latch pin high
  digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  // Turn off all digit control pins to avoid ghosting
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // Turn on the current digit control pin
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {
  // Initialize necessary variables for tracking the current number and digit position
  int currentNumber = number;
  int displayDigit = displayCount - 1; // Start with the most significant digit
  int lastDigit = 0;

  // Loop through each digit of the current number
  while (displayDigit >= 0) {
    // Extract the last digit of the current number
    lastDigit = currentNumber % 10;

    // Activate the current digit on the display
    activateDisplay(displayDigit);

    // Output the byte encoding for the last digit to the display
    if (displayDigit == 2) {
      // Check if it's the D3 digit
      writeReg(byteEncodings[lastDigit] | decimalPoint); // Turn on the decimal point
    } else {
      writeReg(byteEncodings[lastDigit]); // No decimal point
    }

    // Implement a delay for multiplexing visibility
    delay(1); // A small delay to visualize multiplexing

    // Move to the next digit
    displayDigit--;

    // Update 'currentNumber' by removing the last digit
    currentNumber /= 10;

    // Clear the display to prevent ghosting between digit activations
    writeReg(B00000000); // Clear the register to avoid ghosting
  }
}

void checkStartPause(){
  if (millis() - lastButtonStartPauseTime >= startPauseInterval){
    buttonToStartOrPausePressed = true;   
  }
  lastButtonStartPauseTime = millis();   
  makeItStartAndPause();
}

void makeItStartAndPause(){
  if (buttonToStartOrPausePressed){
    hasStarted = !hasStarted; // keeps track of the state of the display, counter is going or not
    if(hasStarted == true){ //if it's going, turn some flags false
      inPauseMode = false;
      hasReseted = false;
      canDisplay = false;
      /*ledState = LOW; //in case the led has been turn ON in reset but we decided not to cycle the saved laps, we turn the led OFF again
      digitalWrite(ledPin, ledState);*/
    }
    else{ //if not it's in Pause Mode and can be reseted
      inPauseMode = true;
    }
    buttonToStartOrPausePressed = false;
  }
}

void makeItReset(){
  buttonResetState = digitalRead(buttonPinReset);
  if (buttonResetState == LOW){ //if button has been pressed it goes LOW because I used the internal pullup resistence and if it't not pressed it's HIGH
    if(inPauseMode){ //if it's in PAUSE mode, make the led ON, set the initial state back to 000.0
      hasReseted = true;
      setInitialState();
      inPauseMode = false;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
    if(inCycleMode){ // if it's in the lap viewing mode it resets, the array is set to initial state, the display goes back at 000.0, there's no more laps to display
      hasReseted = true;
      for(int i = 0; i < lapsToSave; i++){
        saveLap[i] = 0;
      }
      setInitialState();
      inCycleMode = false;
      canDisplay = false;
    }
  }
}

void checkLapButton(){
  if (millis() - lastButtonSaveAndCycleTime >= saveAndCycleInterval){
    buttonToSaveAndCyclePressed = true;  
    if (number == 0){ //count the presses after the reset has been done
      countLapPresses ++;
      countLapPresses %=4;
    }
    
  }
  lastButtonSaveAndCycleTime = millis();
  makeItSave();
}

void makeItSave(){
  if (buttonToSaveAndCyclePressed){
    Serial.println("Button to save and cycle pressed");
   if (hasStarted == true){ // if the counter is going, just save the laps in the array
      //save the number <3
      /*if (countLaps < 4){
        saveLap[countLaps] = number;
        Serial.println(number);
        Serial.println(saveLap[countLaps]);
        countLaps++;
      }
      else{
        countLaps = 0;
        saveLap[countLaps] = number;
        Serial.println(number);
        countLaps++;
      }*/
      saveLap[countLaps] = number;
      Serial.println(number);
      Serial.println(saveLap[countLaps]);
      countLaps++;
      countLaps %= 4;
    }

    if(ledState == HIGH){
      canDisplay = true;
    }
    buttonToSaveAndCyclePressed = false;

  }
}

void displaySavedLaps(){
  inCycleMode = true;
  showSavedLap = saveLap[countLapPresses];
  writeNumber(showSavedLap);
  Serial.println(showSavedLap);
}
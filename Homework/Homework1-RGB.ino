const int colorNumber = 3;
//set the convention 0 = red, 1 = green, 2 = blue

///declare the variables for the potentiometers
const int pinAnalogColor[colorNumber] ={A0, A1, A2};

///declare the variables for the LED
const int ledPinColor[colorNumber] = {11, 10, 9};

///declare variables for the values
float potValueColor[colorNumber] = {0};
int ledValueColor[colorNumber] = {0};

///declare variables to avoid magic numbers
const int inputAnalogMin = 0;
const int inputAnalogMax= 1023;
const int ledPinMin=0;
const int ledPinMax=255;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinColor[0], OUTPUT);
  pinMode(ledPinColor[1], OUTPUT);
  pinMode(ledPinColor[2], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < colorNumber; i++){
    potValueColor[i] = analogRead(pinAnalogColor[i]); //reads the input on the potentiometers
    mapingValue(potValueColor[i], i);
  }
}

//transforming the values read on the potentiometers to values for the LED
void mapingValue(float readPotValue, int position){
  ledValueColor[position] = map(readPotValue, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax); 
  displayColor(ledValueColor[position], position);
}

//activates the LED specific color based on the reading
void displayColor(int mappedLedValue, int pos){
  analogWrite(ledPinColor[pos], mappedLedValue);
}

// Declarare variabile
const int numberFloors = 3;
const int thisPin;
const int maximumIntensity=256;
byte reading;
//declarare array pentru leduri si butoane
const int buttonPinFloor[numberFloors] = {2,3,4}; 
const int ledPinFloor[numberFloors] = {12,10,9};
const int ledPinElevatorState = 6;

// declarari pentru buzzer
const int buzzerPin = 11;
int buzzerTone = 1000;
int currentTone = 0;
int toneTime = 500;

//Declarari debounce
const unsigned long debounceInterval = 500; //interval de debounce
unsigned long lastDebounceTime[numberFloors];

//variabile de timp
unsigned long lastActionTime = 0;
unsigned long waitingTime = 2500;  //Timp de asteptare
unsigned long interval = 1000;

//Declarari stari initiale 
byte buttonStateFloor[numberFloors];      //Starea initiala a butoanelor este LOW
byte lastButtonStateFloor[numberFloors];  //Ultima stare a butoanelor

int currentFloor = 1;
int targetFloor = -1;
int direction = 0; //0->inactiv, 1->urcare ,-1->coborare

//declarari pentru sunet
unsigned long soundStartTime = 0;
int soundState = 1;

void setup(){

  for(int currentPin = 0; currentPin < 3; currentPin++){
    pinMode(buttonPinFloor[currentPin], INPUT_PULLUP);
    pinMode(ledPinFloor[currentPin], OUTPUT);
  }
  pinMode(ledPinElevatorState, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  //debounce 
  for (int thisPin = 0; thisPin < numberFloors ; thisPin++){
    reading = digitalRead(buttonPinFloor[thisPin]);
    if(reading != lastButtonStateFloor[thisPin]){
      lastDebounceTime[thisPin] = millis();
    }
    if((millis() - lastDebounceTime[thisPin]) > debounceInterval){
      if(reading != buttonStateFloor[thisPin]){
        buttonStateFloor[thisPin] = reading;

        if(buttonStateFloor[thisPin] == LOW){
          targetFloor = thisPin + 1;
          if(targetFloor != currentFloor){ ///alegerea directiei liftului, -1 pentru coborare, 1 pentru urcare
            if(targetFloor > currentFloor){
              direction = 1;
            }
            else{
              direction = -1;
            }
            lastActionTime = millis();
            
          }
          
        }
      }
    }
    lastButtonStateFloor[thisPin] = reading;
  }
  
  if(soundState == 0){
      SoundMaker(); //functie pentru cele trei sunete, ajungerea liftului, deschiderea usilor, inchiderea lifturilor
  }

  digitalWrite(ledPinFloor[currentFloor - 1], HIGH);
  if(targetFloor != -1 && targetFloor != currentFloor && soundState == 1){
    movementElevator(targetFloor,direction);
  }
  
}

void movementElevator(int floor , int dir){
  digitalWrite(ledPinElevatorState, LOW);
  pulseLED(ledPinElevatorState);


  if (currentFloor != floor) {
    currentFloor += dir;
    updateFloorIndicators();
    pulseLED(ledPinElevatorState);
  }
  currentFloor = floor;
  if(currentFloor == floor){
    currentFloor = floor;
    updateFloorIndicators();
    digitalWrite(ledPinElevatorState, HIGH);
    soundState = 0;
  }
  lastActionTime = millis();
  digitalWrite(ledPinElevatorState, LOW);
}

void updateFloorIndicators() {
  
  for (int current = 0; current < numberFloors; current++){
    digitalWrite(ledPinFloor[current], currentFloor == current + 1);
  }
 
}
void pulseLED(int ledPin) {
  for (int thisLed= 0; thisLed < 256; thisLed++) {
    analogWrite(ledPin, thisLed);
    delay(1);
  }
  for (int thisLed = 255; thisLed >= 0; thisLed--) {
    analogWrite(ledPin, thisLed);
    delay(1);
  }
}

void SoundMaker(){
  
  if(millis() - soundStartTime >= waitingTime){
    tone(buzzerPin, buzzerTone, toneTime);
    buzzerTone +=500;
    currentTone++;
    soundStartTime = millis();
  }
  if (currentTone == 3){
    currentTone = 0;
    soundState = 1;
    buzzerTone =1000;
  }
}

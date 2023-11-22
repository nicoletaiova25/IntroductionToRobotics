#include <EEPROM.h>
//flag variables to keep tracks of things along the way
bool flagMenu = true; //flag when I am on the main menu
//flag for the subMenus, made true when user chooses to go on desired submenu
bool flagSensorSubMenu = false; //for sensor settings
bool flagResetMenu = false; //for reseting stuff
bool flagSystemMenu = false; //for system settings 
bool flagLedMenu = false; //for led control
//flags for led control stuff
bool flagLedManual = false;
bool flagLedAutomated = false;
//for other stuff
bool flagInterval = false; 
bool flagWriteContinue = false; // to write the readings from the sensors

// variables for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;
long duration = 0;
int distance = 0;
int ultrasonicThreshold;
int intervalUltrasonic;
int maxUltrasonic = 0;
int minUltrasonic = 0;
bool flagUltrasonic = false;
unsigned long ultrasonicMillis = 0;

//variables for ldr sensor
int photocellPin = A0;
int photocellValue;
int intervalLRD;
int lrdThreshold ;
bool flagLRD = false ;
int maxLrd = 0;
int minLrd = 0;

int eepromAddress = 0;

//variables for rgb led 
const int colorNumber = 3;
const int ledPinColor[colorNumber] = {4, 7, 8};
int ledValueColor[colorNumber];
int color = 4;
int automat = 0;

int i = 0;
int ultrasonicEEPROMAddress = 20;
int lrdEEPROMAddress = 40;  // Assuming each reading is 2 bytes, and you have 10 readings

void setup() {
  Serial.begin(9600);
  mainMenu();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPinColor[0], OUTPUT);
  pinMode(ledPinColor[1], OUTPUT);
  pinMode(ledPinColor[2], OUTPUT);
}

void mainMenu() {
  Serial.println(F("Select an option:"));
  Serial.println(F("1. \"Sensor Settings\" "));
  Serial.println(F("2. \"Reset logger data\" "));
  Serial.println(F("3. \"System status\" "));
  Serial.println(F("4. \"RGB LED Control\" "));
}
//fucntions for suboptions 
void printSensorSubMenu() { //sensor settings submenu
  Serial.println(F("Select an option:"));
  Serial.println(F("1. \"Sensor Sampling Interval\""));
  Serial.println(F("2. \"Ultrasonic Alert Threshold\""));
  Serial.println(F("3. \"LDR Alert Threshold\""));
  Serial.println(F("4. \"Back To Menu\""));
}

void resetSubMenu() { //reset logger data submenu
  Serial.println(F("Are you sure? Press:"));
  Serial.println(F("1. \"Yes\""));
  Serial.println(F("2. \"No\""));
}

void systemSubMenu() {//system status submenu
  Serial.println(F("Select an option:"));
  Serial.println(F("1. \"Current readings \""));
  Serial.println(F("2. \"Current sensors settings \""));
  Serial.println(F("3. \" Display logged data\""));
  Serial.println(F("4. \" Back to menu\""));
}

void ledSubMenu() { // led control submenu
  Serial.println(F("1. \"Manual color control \""));
  Serial.println(F("2. \"Automated ON/OFF \""));
  Serial.println(F("3. \" Back to menu\""));
}

//function to decide the submenu we are displaying based on the user's choise
void menuOption(int option) {
  switch (option) {
    case 1: //if option == 1 we display the sensor settings submenu make its flag true
      printSensorSubMenu();
      flagSensorSubMenu = true;
      break;
    case 2:
      flagResetMenu = true;
      resetSubMenu();
      break;
    case 3:
      flagSystemMenu = true;
      systemSubMenu();
      break;
    case 4:
      flagLedMenu = true;
      ledSubMenu();
      break;
    default:
      if(option > 4){
      Serial.println("Try again loser! That option doesn't exist!");
      }
  }
}

void intervalSettings() {
  if (flagInterval) {
    delay(1000); // Așteaptă un moment pentru a permite utilizatorului să introducă date

    if (Serial.available()) {
      int userValue = Serial.parseInt();

      if (userValue >= 1 && userValue <= 10) {
        intervalLRD = userValue;
        intervalUltrasonic = userValue;

        // Store the interval values in EEPROM
        EEPROM.update(eepromAddress, intervalLRD);
        eepromAddress += sizeof(intervalLRD);
        EEPROM.update(eepromAddress, intervalUltrasonic);
        eepromAddress += sizeof(intervalUltrasonic);

        //flagInterval = false;
        Serial.println(F("Interval for LRD"));
        Serial.println(intervalLRD);
        Serial.println(F("Interval for Ultrasonic"));
        Serial.println(intervalUltrasonic);
      } else {
        Serial.println(F("Invalid input. Please enter a value between 1 and 10 seconds."));
        intervalSettings();
      }
    }
    
  }
}

void setUltrasonicThreshold() {
  if (flagUltrasonic) {
    Serial.println(F("Enter the Ultrasonic Sensor Threshold value: "));
    delay(1000);
   
    if (Serial.available() > 0) {
      ultrasonicThreshold = Serial.parseInt();
      Serial.println("Ultrasonic Threshold set to: "+ String(ultrasonicThreshold));
    }
  }
}

void decideMinMaxUltrasonic(){
  int userChoice = 0;

    Serial.println(F("Do you want to set this value as:"));
    Serial.println(F("1. Minimum Threshold"));
    Serial.println(F("2. Maximum Threshold"));
    delay(1000);
      if (Serial.available() > 0) {
        userChoice = Serial.parseInt();
        flagUltrasonic = false;

      }
    

    if (userChoice == 1) {
      // Store as Minimum Threshold
      Serial.println("Ultrasonic Minimum Threshold set to: " + String(ultrasonicThreshold));
      minUltrasonic = ultrasonicThreshold;
    } else if (userChoice == 2) {
      // Store as Maximum Threshold
      maxUltrasonic = ultrasonicThreshold;
      Serial.println("Ultrasonic Maximum Threshold set to: " + String(ultrasonicThreshold));
    }

}

void setLrdThreshold() {
  if (flagLRD) {
    Serial.println(F("Enter the LRD Sensor Threshold value: "));
    delay(1000);

    if (Serial.available() > 0) {
      lrdThreshold = Serial.parseInt();
      Serial.println("LDR Threshold set to: " + String(lrdThreshold));
    } 
  }
}

void decideMinMaxLDR(){
  int userChoice = 0;

    Serial.println(F("Do you want to set this value as:"));
    Serial.println(F("1. Minimum Threshold"));
    Serial.println(F("2. Maximum Threshold"));

    if (userChoice != 1 && userChoice != 2) {
      delay(1000);
      if (Serial.available() > 0) {
        userChoice = Serial.parseInt();
      }
    }
    if (userChoice == 1) {
      // Store as Minimum Threshold
      Serial.println("LDR Minimum Threshold set to: " + String(lrdThreshold));
      minLrd = lrdThreshold;
    } else if (userChoice == 2) {
      // Store as Maximum Threshold
      maxLrd = lrdThreshold;
      Serial.println("LDR Maximum Threshold set to: " + String(lrdThreshold));
    }
}

void sensorSubMenuOption(int opt) {
  switch (opt) {
    case 1:
      flagSensorSubMenu = false;
      Serial.println(F("Enter a value between 1 and 10 seconds for the sampling rate: "));
      flagInterval = true;
      intervalSettings();
       if (intervalLRD != 0 && intervalUltrasonic != 0) {
        flagInterval = false;
        printSensorSubMenu();
        flagSensorSubMenu = true;
      }
      break;
    case 2:
      Serial.println(F("Alert for Ultrasonic"));
      flagSensorSubMenu = false;
      flagUltrasonic = true;
      setUltrasonicThreshold();
      decideMinMaxUltrasonic();
      if (minUltrasonic > 0 || maxUltrasonic > 0) {
      printSensorSubMenu();
      flagSensorSubMenu = true;
      }
      break;
    case 3:
      Serial.println(F("Alert for LDR"));
      flagLRD = true;
      flagSensorSubMenu = false;
      setLrdThreshold();
      decideMinMaxLDR();
      if (minLrd > 0 || maxUltrasonic > 0) {
      printSensorSubMenu();
      flagSensorSubMenu = true;;
      }
      break;
    case 4:
      Serial.println(F(" Return to main menu "));
      flagMenu = true;
      flagSensorSubMenu = false;
      mainMenu();
      break;
  }
}

void setResetYes(){
  if (Serial.available() > 0){
    int userChoice = 0;

    Serial.println(F("Choose one of the options:"));
    Serial.println(F("1. Reset just the Ultrasonic Sensor"));
    Serial.println(F("2. Reset just the LRD Sensor"));
    Serial.println(F("3. Reset both sensors"));

    
      delay(1000);
      if (Serial.available() > 0) {
        userChoice = Serial.parseInt();
      }
    

    if (userChoice == 1) {
      // Reset Threshold
      if (minUltrasonic != 0){
        Serial.println(F("Ultrasonic Minimum Threshold reseted"));
        minUltrasonic = 0;
      }
      if (maxUltrasonic != 0){
        Serial.println(F("Ultrasonic Maximum Threshold reseted"));
        maxUltrasonic = 0;
      }
      
    } else if (userChoice == 2) {
      // Reset Threshold
      if (minLrd != 0){
        Serial.println(F("Lrd Minimum Threshold reseted"));
        minLrd = 0;
      }
      if (maxLrd != 0){
        Serial.println(F("Lrd Maximum Threshold reseted"));
        maxLrd = 0;
      }
    }
    else if(userChoice == 3){
      if (minUltrasonic != 0){
        minUltrasonic = 0;
        Serial.print(F("Ultrasonic Minimum Threshold reseted "));
        Serial.println(minUltrasonic);
      }
      if (maxUltrasonic != 0){
        maxUltrasonic = 0;
        Serial.print(F("Ultrasonic Maximum Threshold reseted "));
        Serial.println(maxUltrasonic);
      }
      if (minLrd != 0){
        minLrd = 0;
        Serial.print(F("Lrd Minimum Threshold reseted "));
        Serial.println(minLrd);
      }
      if (maxLrd != 0){
        maxLrd = 0;
        Serial.print(F("Lrd Maximum Threshold reseted "));
        Serial.println(maxLrd);
    }
    }

    if (minUltrasonic == 0 || maxUltrasonic == 0 || minLrd == 0 || maxLrd == 0) {
      mainMenu();
      flagMenu = 1;
    }
    
  }
}

void subResetOption(int opt) {
  switch (opt) {
    case 1:
      Serial.println(F(" You chose yes : "));
      setResetYes();
      flagResetMenu = false;
      break;
    case 2:
      Serial.println(F("You chose no : "));
      flagResetMenu = false;
      flagMenu = true;
      mainMenu();
      break;
  }
}

void printSensorsReadings() {
  if (flagWriteContinue && ultrasonicMillis <= intervalUltrasonic*5) {
      if(color != 4){
        digitalWrite(ledPinColor[color-1], HIGH);
      }
      ultrasonicMillis ++ ;
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Sound wave reflects from the obstacle, so to calculate the distance we
      // consider half of the distance traveled.
      distance = duration * 0.034 / 2;
      // Prints the distance on the Serial Monitor
      photocellValue = analogRead(photocellPin);
      if(automat ==1){
        if (distance < minUltrasonic && photocellValue < minLrd && minUltrasonic != 0 && minLrd != 0){
          digitalWrite(ledPinColor[1], HIGH); 
          digitalWrite(ledPinColor[0], LOW);
        }
        else {
          digitalWrite(ledPinColor[0], HIGH); 
          digitalWrite(ledPinColor[1], LOW);
        }
        if (distance > maxUltrasonic && photocellValue > maxLrd && maxUltrasonic != 0 && maxLrd != 0){
          digitalWrite(ledPinColor[1], HIGH);
          digitalWrite(ledPinColor[0], LOW);
        }
        else {
          digitalWrite(ledPinColor[0], HIGH); 
          digitalWrite(ledPinColor[1], LOW);
        }
      }
      Serial.print(F("Distance for Ultrasonic: "));
      // Store Ultrasonic reading in EEPROM
      EEPROM.put(ultrasonicEEPROMAddress, distance);
      ultrasonicEEPROMAddress += sizeof(distance);
      Serial.println(distance);
      Serial.print(F("Photocell LDR reading: "));
      Serial.println(photocellValue);
      EEPROM.put(lrdEEPROMAddress, photocellValue);
      lrdEEPROMAddress += sizeof(photocellValue);
      delay(100);
  }
  if (Serial.available() > 0 ) {
        
        // Read the character from the Serial buffer
        char inputChar = Serial.read();

        // Check if the character is the exit character
        if (inputChar == 'q' || inputChar == 'Q') {
          Serial.println(F("Exiting loop. 'q' or 'Q' detected."));
          flagWriteContinue = false;
          ultrasonicMillis = 0;
          flagSystemMenu = 1;
          digitalWrite(ledPinColor[color-1], LOW);
          systemSubMenu();
        }
      }
    }

void printUserValues(){
  Serial.print(F("Sampling Interval for Ultrasonic sensor: "));
  Serial.println(intervalUltrasonic);
  Serial.print(F("Sample interval for LDR sensor"));
  Serial.println(intervalLRD);
  Serial.print(F("Threshold value for Ultrasonic sensor"));
  Serial.println(ultrasonicThreshold);
  Serial.print(F("Threshold value for LDR sensor"));
  Serial.println(lrdThreshold);
}

void retrieveLast10Readings() {
  Serial.println(F("Retrieving last 10 readings from EEPROM:"));

  Serial.println(F("Ultrasonic Readings:"));
  for (int i = 0; i < 10; ++i) {
    int value;
    EEPROM.get(ultrasonicEEPROMAddress - (i + 1) * sizeof(value), value);
    Serial.print(value);
    Serial.print(" ");
  }

  Serial.println(F("\n LRD Readings:"));
  for (int i = 0; i < 10; ++i) {
    int value;
    EEPROM.get(lrdEEPROMAddress - (i + 1) * sizeof(value), value);
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println();
}


void subSystemOption(int opt) {
  switch (opt) {
    case 1:
      // introdu valoare pentru senzori
      Serial.println(F(" Write the sensors readings "));
      Serial.println(F("Continuously printing sensor readings. Press 'q' to exit."));
      flagWriteContinue = true;
      break;
    case 2:
      flagSystemMenu = false;
      Serial.println(F("Displaying the values chosen by the user"));
      printUserValues();
      break;
    case 3:
      flagSystemMenu = false;
      Serial.println(F("Displaying the last 10 readings from the sensors"));
      retrieveLast10Readings();
      break;
    case 4:
      Serial.println(F("Going back to Main Menu"));
      flagMenu = true;
      flagSystemMenu = false;
      mainMenu();
      break;
  }
}

void setManualControl() {
  if(flagLedManual){
    if(Serial.available() > 0){
    Serial.println(F("Choose one of the options to light reading sensors:"));
    
    Serial.println(F("1. GREEN"));
    Serial.println(F("2. RED"));
    Serial.println(F("3. BLUE"));
    delayMicroseconds(50);
    color = Serial.parseInt();
    if(color!=4){
        Serial.println(color);
        flagLedMenu = true;
        ledSubMenu();
        flagLedManual = false;
      }
    }
  }
  
}

void setAutomateControl(){
  if (flagLedAutomated){
    if(Serial.available()){
      Serial.println(F("Choose option"));
      Serial.println(F("1.ON"));
      Serial.println(F("2.OFF"));
      automat = Serial.parseInt();
      //flagLedAutomated = false;
      decideAutomated();
    }
    if(automat == 1 || automat == 2){
        flagLedMenu = true;
        ledSubMenu();
        flagLedAutomated = false;
      }
  }
}

void decideAutomated(){
   if (automat == 2){
    Serial.println(F("In this mode, we use the values set on the Manual Control. Go back and set it there. You do not really have a choice. Not Sorry"));
    //setManualControl();
  }
}

void subLedOption(int opt) {
  switch (opt) {
    case 1:
      Serial.println(F(" Manual control LED "));
      flagLedManual = true;
      flagLedMenu = false;
      break;
    case 2:
      Serial.println(F(" Automated control LED "));
      flagLedAutomated = true;
      flagLedMenu = false;
      break;
    case 3:
      Serial.println(F("Going back to MAIN MENU"));
      flagMenu = true;
      flagLedMenu = false;
      mainMenu();
      break;
  }
}

//functions to make decisions based on options and flags
void decisionMainMenu() {
  if (flagMenu) {
    if (Serial.available()) {
      int choice = Serial.parseInt();
      menuOption(choice);
      if (choice != 0) {
        flagMenu = false;
      }
    }
  }
}

void decisionSensorSubMenu() {
  if (flagSensorSubMenu) {
    if (Serial.available()) {
      int choiceSensorSubMenu = Serial.parseInt();
      sensorSubMenuOption(choiceSensorSubMenu);
    }
  }
}

void decisionResetMenu() {
  if (flagResetMenu) {
    if (Serial.available()) {
      int choiceResetMenu = Serial.parseInt();
      subResetOption(choiceResetMenu);
    }
  }
}

void decisionSystemMenu() {
  if (flagSystemMenu) {
    if (Serial.available()) {
      int choiceSystemMenu = Serial.parseInt();
      subSystemOption(choiceSystemMenu);
    }
  }
}

void decisionLedMenu() {
  if (flagLedMenu) {
    if (Serial.available()) {
      int choiceLedMenu = Serial.parseInt();
      subLedOption(choiceLedMenu);
    }
  }
}

void loop() {
  decisionMainMenu();
  decisionSensorSubMenu();
  decisionResetMenu();
  decisionSystemMenu();
  printSensorsReadings();
  decisionLedMenu();
  setManualControl();
  setAutomateControl();
}
#include <LedControl.h>

//variables for driver conections
const int DIN_PIN = 12;
const int CLK_PIN = 11;
const int CS_PIN = 10;
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

//variables regarding the joystick
const int JoyStickZoneZero = 50;
const int movementInterval = 200;
unsigned long lastMoveTime = 0;
const int matrixSize = 8;
const int xPin = A0;
const int yPin = A1;
const int joystickButton = 2;

// variables to define the player position
int playerX = 0;
int playerY = 0;

bool walls[matrixSize][matrixSize]; //matrix true/false to keep track of the leds state
bool wallsGenerated = false; //flag if the map of walls was generated or not
bool displayHiFlag = true; //flag for displaying the greeting image, just this image worked

//variables for time
unsigned long previousMillis = 0;
const long interval = 200;

//variables for the bomb, yes, all of them were needed
const int intervalBomb = 50; //for blinking the bomb
unsigned long previousMillisBomb = 0; //for the time difference
bool bombPlaced = false; //flag to know if the bomb was placed
bool detonateFlag = false; //flag to know if the bomb was detonated
int bombX, bombY; // to remember where the bomb is
bool canPlaceBomb = false; //flag to know if the bomb can be placed
int countPresses = 0; //to count how many times the button was pressed because I use the button for 3 things and arduino was doing all of them at the same time
bool canBlowTheBomb = false; //flag to detonate the bomb

const int ledPinBombPlaced = 7; //led that lights up when the bomb is placed end goes off when bomb is boom
const int buzzerBombBlown = 4; // buzzer to beep when bomb boom
const int bombFrequency = 1500;
const int boomBombSound = 500;

unsigned long gameStartTime = 0; //to keep track of time since the start of the game
int score = 0; // to remember the score

void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  pinMode(joystickButton, INPUT);
  digitalWrite(joystickButton, HIGH);

  randomSeed(analogRead(A2)); //to make sure the random is random everytime the Arduino resets, Arduino reference for more details
  pinMode(ledPinBombPlaced, OUTPUT);
  pinMode(buzzerBombBlown, OUTPUT);

  generateRandomWalls();
}

void loop() {
  if (displayHiFlag) { //displays the greeting image
    displayHi();
  } else {
    readPlayerDetails(); //reads the input from the joystick and updates the player position
    displayWalls(); //puts walls on the matrix
    displayBlinkingPlayer(); //make player blink
    displayBlinkingBomb(); //make bomb blink blink faster
    checkWalls(); //checks if there still exist walls or not
  }
  checkJoyStickButton(); // reads the button state and decides what to do
}

void decideToGenerateWalls() {
  if (!wallsGenerated) {
      generateRandomWalls(); //generates random walls
      wallsGenerated = true;
      displayHiFlag = false;
      countPresses = 0;
      gameStartTime = millis(); //starts the game time counter
    }
}
void decideToPlaceBomb(){
  if (canPlaceBomb && countPresses == 1 && !bombPlaced) {
      placeBomb();
    }
}

void decideToBlowTheBomb(){
  if (canBlowTheBomb && countPresses == 2) {
      if (bombPlaced && detonateFlag) {
        detonateBomb();
        canBlowTheBomb = false;
      }
    }
}

void readPlayerDetails(){
  int xValue = analogRead(xPin); //gets input
  int yValue = analogRead(yPin);

  if (abs(xValue - 512) > JoyStickZoneZero || abs(yValue - 512) > JoyStickZoneZero) { //if the player trully moved
    if (millis() - lastMoveTime >= movementInterval) { 
      updatePlayerPosition(xValue, yValue); //updates position
      lastMoveTime = millis();
    }
  }
}

void checkJoyStickButton(){
  static bool previousButtonState = HIGH; //variable for the button to make sure it was actually pressed
  bool currentButtonState = digitalRead(joystickButton);

  if (currentButtonState == LOW && previousButtonState == HIGH) { //if pressed
    countPresses++;
    decideToGenerateWalls();
    decideToPlaceBomb();
    decideToBlowTheBomb();
    countPresses %= 2;
  }
  previousButtonState = currentButtonState;
}

void checkWalls() {
  bool wallsExist = false;
  //checks if there are walls still standing on the map, if not, it restarts the game, if yes, does nothing
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      if (walls[i][j]) {
        wallsExist = true;
        break;
      }
    }
    if (wallsExist) {
      break;
    }
  }

  if (!wallsExist) {
    restartGame();
  }
}

void restartGame() {
  wallsGenerated = false;
  displayHiFlag = true; // to display the gretting message again
  countPresses = 0;
  unsigned long gameTime = millis() - gameStartTime;
  score += gameTime / 1000; // calculates the score
  Serial.print(F("For this game you scored:"));
  Serial.println(abs(score));
  score = 0;
}


void generateRandomWalls() {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      walls[i][j] = random(2) == 0; //there is 50% chance there is or not a wall
    }
  }

  do {
    playerX = random(matrixSize); //places the player random depending on the walls, while giving it space to move, to not be trapped between 4 walls
    playerY = random(matrixSize);
  } while (walls[playerY][playerX] || isPlayerSurrounded(playerX, playerY));
}

bool isPlayerSurrounded(int x, int y) { //checks if the player is surrounded
  if ((x > 0 && walls[y][x - 1]) || (x < matrixSize - 1 && walls[y][x + 1]) ||
      (y > 0 && walls[y - 1][x]) || (y < matrixSize - 1 && walls[y + 1][x])) {
    return true;
  }
  return false;
}

void displayWalls() { //shows the walls on the matrix
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      if (walls[i][j]) {
        lc.setLed(0, i, j, true);
      }
    }
  }
}

void displayBlinkingPlayer() { //makes player go blink on the matrix
  unsigned long currentMillis = millis();
  static bool playerLEDState = false;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    playerLEDState = !playerLEDState; 

    lc.setLed(0, playerY, playerX, false);
    lc.setLed(0, playerY, playerX, playerLEDState);
  }
}

void updatePlayerPosition(int xValue, int yValue) { //changes the position of the player based on input
  int deltaX = xValue - 512;
  int deltaY = yValue - 512;

  int previousX = playerX;
  int previousY = playerY;

  if (abs(deltaX) > JoyStickZoneZero) {
    lc.setLed(0, playerY, playerX, false);

    if (deltaX > 0 && playerX < matrixSize - 1 && !walls[playerY][playerX + 1]) {
      playerX++;
    } else if (deltaX < 0 && playerX > 0 && !walls[playerY][playerX - 1]) {
      playerX--;
    }
  }

  if (abs(deltaY) > JoyStickZoneZero) {
    lc.setLed(0, playerY, playerX, false);

    if (deltaY > 0 && playerY < matrixSize - 1 && !walls[playerY + 1][playerX]) {
      playerY++;
    } else if (deltaY < 0 && playerY > 0 && !walls[playerY - 1][playerX]) {
      playerY--;
    }
  }
  canBlowTheBomb = true;

  if (playerX != previousX || playerY != previousY) {
    lc.setLed(0, playerY, playerX, true);
    canPlaceBomb = true;
  }
}

void placeBomb() {
  if (!bombPlaced) {
    bombX = playerX; //bomb is placed on the position of the player, player should move after placing to actually see the bomb and if no desire to get blown away, player is imune anyway
    bombY = playerY;
    bombPlaced = true;
    detonateFlag = true;
    canPlaceBomb = false;
    digitalWrite(ledPinBombPlaced, HIGH); //output led goes ON
  }
}

void displayBlinkingBomb() { //makes bomb blink blink faster than the player
  unsigned long currentMillisBomb = millis();
  static bool bombLedState = false;

  if (bombPlaced) {
    if (currentMillisBomb - previousMillisBomb >= intervalBomb) {
      previousMillisBomb = currentMillisBomb;
      bombLedState = !bombLedState;
      lc.setLed(0, bombY, bombX, bombLedState);
    }
  }
}

void detonateBomb() { //blows the bomb 
  if (bombPlaced) { 
    eliminateFirstWallInDirection(bombX, bombY, 1, 0); //blows the bomb in all directions, right, left, down, up
    eliminateFirstWallInDirection(bombX, bombY, -1, 0);
    eliminateFirstWallInDirection(bombX, bombY, 0, 1);
    eliminateFirstWallInDirection(bombX, bombY, 0, -1);
    lc.setLed(0, bombY, bombX, false);
    digitalWrite(ledPinBombPlaced, LOW); //output led goes off
    bombPlaced = false;
    detonateFlag = false;
    playCrashSound(); //buzzer goes boom
  }
}

void eliminateFirstWallInDirection(int startX, int startY, int dirX, int dirY) {
  for (int x = startX + dirX, y = startY + dirY;
       x >= 0 && x < matrixSize && y >= 0 && y < matrixSize;
       x += dirX, y += dirY) {
    if (walls[y][x]) {
      // we find the first wall in the wanted direction, we blow it and break out of function
      walls[y][x] = false; 
      score += 10; //we add 10 to the score for every wall blown away
      lc.setLed(0, y, x, false);
      break;
    }
  }
}

void displayHi() {
  const uint64_t HI_IMAGE = 0x00b292beb232b200;

  unsigned long currentMillis = millis();
  if (millis() - currentMillis < interval) {
    displayImage(HI_IMAGE);
    lc.clearDisplay(0); // cleans the screen
  }
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte rowData = (image >> (i * 8)) & 0xFF;
    lc.setRow(0, i, rowData);
 }
}

void playCrashSound() {
  tone(buzzerBombBlown, bombFrequency, boomBombSound); 
  //delay(200); 
  //noTone(buzzerBombBlown);
}
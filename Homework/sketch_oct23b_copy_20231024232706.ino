///declaram variabilele
const int pinAnalogRosu=A0;
const int pinAnalogVerde=A1;
const int pinAnalogBlue=A2;

const int ledPinRosu=11;
const int ledPinVerde=10;
const int ledPinBlue=9;

float potValueRosu = 0;
float potValueVerde = 0;
float potValueBlue = 0;

float ledValueRosu = 0;
float ledValueVerde = 0;
float ledValueBlue = 0;

int inputAnalogMin = 0;
int inputAnalogMax= 1023;
int ledPinMin=0;
int ledPinMax=255;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRosu, OUTPUT);
  pinMode(ledPinVerde, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void citireAnalog()
{
  potValueRosu = analogRead(pinAnalogRosu);
  potValueVerde = analogRead(pinAnalogVerde);
  potValueBlue = analogRead(pinAnalogBlue);
}

void mapare()
{
  ledValueRosu = map(potValueRosu, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueVerde = map(potValueVerde, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueBlue = map(potValueBlue, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
}

void ScrieAnalog()
{
  analogWrite(ledPinRosu, ledValueRosu);
  analogWrite(ledPinVerde, ledValueVerde);
  analogWrite(ledPinBlue, ledValueBlue); 
}

void loop() {
  // put your main code here, to run repeatedly:
  citireAnalog();
  mapare();
  ScrieAnalog();
}
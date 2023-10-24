///declaram variabilele
///declaram pinii Analog
const int pinAnalogRosu=A0;
const int pinAnalogVerde=A1;
const int pinAnalogBlue=A2;

///declaram pinii digitali; am facut corespondenta intre culorile ledului si numarul pinului 
//dupa conventia pinilor ledului RGB, iar apoi am testat prin trial and error
const int ledPinRosu=11;
const int ledPinVerde=10;
const int ledPinBlue=9;

//declaram variabilele in care vom citi valoarea fiecarui potentiometru
float potValueRosu = 0;
float potValueVerde = 0;
float potValueBlue = 0;

//declaram variabilele in care vom retine valoarea mapata pentru afisare
float ledValueRosu = 0;
float ledValueVerde = 0;
float ledValueBlue = 0;

//declaram variabile pentru a evita folosirea numerelor magice 
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

//functie de citire a valorilor potentiometrelor inregistrate prin pinii analogi
void citireAnalog()
{
  potValueRosu = analogRead(pinAnalogRosu);
  potValueVerde = analogRead(pinAnalogVerde);
  potValueBlue = analogRead(pinAnalogBlue);
}

//functie in care mapam in functie de valoarea citita pe potentiometru si valorile declarate anterior
void mapare()
{
  ledValueRosu = map(potValueRosu, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueVerde = map(potValueVerde, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
  ledValueBlue = map(potValueBlue, inputAnalogMin, inputAnalogMax, ledPinMin, ledPinMax);
}

//functie de scriere pentru a afisa culorile ledului
void ScrieAnalog()
{
  analogWrite(ledPinRosu, ledValueRosu);
  analogWrite(ledPinVerde, ledValueVerde);
  analogWrite(ledPinBlue, ledValueBlue); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //apelarea functiilor
  citireAnalog();
  mapare();
  ScrieAnalog();
}

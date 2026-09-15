#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int block = 2;
byte blockcontent[16] = {"16CharacterStrng"};

byte readBackBlock[18];

#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4

int frequency = 0;

const int led1 = 6;
const int led2 = 7;

const int led3 = 3;
const int led4 = 2;

const int line = A5;

unsigned long currentMillis = 0;
unsigned long previousColourRed = 0;
unsigned long previousColourGreen = 0;
unsigned long previousColourBlue = 0;

const int button1 = 5;
const int button2 = 4;

bool rfidEnabled = true;



void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(line, INPUT);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);

  
  rfidUsingCheck();

  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(line);
  //flashLeds();
  //colourSensor();
  if (rfidEnabled) { // checks if the rfid is going to be used 
    rfidFunc();
  }

  if (digitalRead(button1)){ // this will be replaced with another trigger
  digitalWrite(led1, HIGH); // motor 1 and motor 2 forward
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  } else if (digitalRead(button2)){
    digitalWrite(led1, LOW); // motor 1 and motor 2 backwards
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } else {
    digitalWrite(led1, LOW); // both motors off
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}

void flashLeds() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(500);
}







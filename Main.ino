#include <SPI.h>
#include <MFRC522.h>
#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t SensorCount = 1;
uint16_t sensorValues[SensorCount];

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int block = 2;
byte blockContent[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10};

byte readBackBlock[18];

#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4
#define OE 0


int frequency = 0;




unsigned long currentMillis = 0;
unsigned long previousColourRed = 100;
unsigned long previousColourGreen = 200;
unsigned long previousColourBlue = 300;
unsigned long previousLineSensor = 0;


int colourRedInterval = 100;
int colourGreenInterval = 100;
int colourBlueInterval = 100;
int lineSensorInterval = 100;

const int motor2Forward = 7;
const int motor2Back = 6;
const int motor1Forward = 3;
const int motor1Back = 2;

const int lineSensor = A5;

bool rfidEnabled = true;


void setup() {

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){}, SensorCount);

  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Back, OUTPUT);
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Back, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);

  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  digitalWrite(OE, HIGH);

  pinMode(lineSensor, INPUT);

  Serial.begin(9600);


  if (rfidEnabled){
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Scan a card");
    for (byte i = 0; i < 6; i++){
      key.keyByte[i] == 0xFF;
    }
    
  }



}

void loop() {
  // delay(100);
  // turnLeftStat();
  // delay(100);
  // clearMotors();
  // turnRightStat();
  // delay(100);
  // clearMotors();
  // turnLeftStat();
  // delay(100);
  // clearMotors();
  // turnRightStat();
  // delay(100);
  // clearMotors();

  // delay(500);
  // clearMotors();
  // forward();
  // delay(500);
  // clearMotors();
  // reverse();

  //colourSensor();
  // currentMillis = millis();

  // RedMillis();
  // GreenMillis();
  // BlueMillis();
  // LineSensorMillis();

  RfidFunc();
  //ReadBlock(block, readBackBlock);
  

}

void ClearMotors(){
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Back, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Back, LOW);
}

void TurnLeftStat(){
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor2Back, HIGH);
}

void TurnRightStat(){
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor1Back, HIGH);
}

void Forward(){
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor2Forward, HIGH);
}

void Reverse(){
  digitalWrite(motor1Back, HIGH);
  digitalWrite(motor2Back, HIGH);
}





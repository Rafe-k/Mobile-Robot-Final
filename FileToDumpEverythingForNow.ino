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
byte blockcontent[16] = {"16CharacterStrng"};

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
  currentMillis = millis();

  RedMillis();
  GreenMillis();
  BlueMillis();
  LineSensorMillis();
  

}

void clearMotors(){
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Back, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Back, LOW);
}

void turnLeftStat(){
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor2Back, HIGH);
}

void turnRightStat(){
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor1Back, HIGH);
}

void forward(){
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor2Forward, HIGH);
}

void reverse(){
  digitalWrite(motor1Back, HIGH);
  digitalWrite(motor2Back, HIGH);
}

// void colourSensor()
// {
//   // red photodiodes
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, LOW);
//   // reading output frequency
//   frequency = pulseIn(sensorOut, LOW);
//   int red = map(frequency, 0, 1023, 0, 255);
//   // printing the value
//   Serial.print("R= ");
//   Serial.print(red); // prints red colour frequency
//   Serial.print(" ");
//   delay(100);
//   // green photodiodes
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, HIGH);
//   // reading output frequency
//   frequency = pulseIn(sensorOut, LOW);
//   int green = map(frequency, 0, 1023, 0, 255);
//   // printing the value
//   Serial.print("G= ");
//   Serial.print(green); // prints green colour frequency
//   Serial.print(" ");
//   delay(100);
//   // blue photodiodes
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, HIGH);
//   // reading output frequency
//   frequency = pulseIn(sensorOut, LOW);
//   int blue = map(frequency, 0, 1023, 0, 255);
//   // printing the value
//   Serial.print("B= ");
//   Serial.print(blue); // prints blue colour frequency
//   Serial.print(" ");
//   Serial.println("");
//   delay(1000);

  
// }

void AnalogArrayFunc(){
  qtr.read(sensorValues);

  for (uint8_t i = 0; i < SensorCount; i++){
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
}

void LineSensor(){
  int s1 = digitalRead(lineSensor);
  Serial.println(s1);
  // delay(100);
}

void MillisFunction(){
  currentMillis = millis();

  //event 1
  RedMillis();
}

void RedMillis(){
  if (currentMillis - previousColourRed >= colourRedInterval){

    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);

    // reading output frequency
    frequency = pulseIn(sensorOut, LOW);
    int red = map(frequency, 0, 1023, 0, 255);

    // printing the value
    Serial.print("R= ");
    Serial.print(red); // prints red colour frequency
    Serial.print(" ");

    previousColourRed = currentMillis;
  }
}

void GreenMillis(){
  if (currentMillis - previousColourGreen >= colourGreenInterval){

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);

    // reading output frequency
    frequency = pulseIn(sensorOut, LOW);
    int green = map(frequency, 0, 1023, 0, 255);

    // printing the value
    Serial.print("G= ");
    Serial.print(green); // prints green colour frequency
    Serial.print(" ");

    previousColourGreen = currentMillis;
  }
}

void BlueMillis(){
  if (currentMillis - previousColourBlue >= colourBlueInterval){

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);

    // reading output frequency
    frequency = pulseIn(sensorOut, LOW);
    int blue = map(frequency, 0, 1023, 0, 255);
    
    // printing the value
    Serial.print("B= ");
    Serial.print(blue); // prints blue colour frequency
    Serial.print(" ");
    Serial.println("");

    previousColourBlue = currentMillis;
  }
}

void LineSensorMillis(){
  if (currentMillis - previousLineSensor >= lineSensorInterval){
    if (digitalRead(lineSensor)){
      digitalWrite(lineSensor, LOW);
    } else {
      digitalWrite(lineSensor, HIGH);
    }
    previousLineSensor = currentMillis;
  }
}

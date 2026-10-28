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
byte blockContent[16] = {"16CharacterStrng"};

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
  currentMillis = millis();

  RedMillis();
  GreenMillis();
  BlueMillis();
  LineSensorMillis();

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

void RfidFunc() 
{
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.println("card selected");

  //the blockcontent array is written into the card block
  WriteBlock(block, blockContent);

  //read the block back
  ReadBlock(block, readBackBlock);
  //uncomment below line if you want to see the entire 1k memory with the block written into it.
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  //print the block contents
  Serial.print("read block: ");
  for (int j=0 ; j<16 ; j++)
  {
    Serial.write (readBackBlock[j]);
  }

  Serial.println("");
}

int WriteBlock(int blockNumber, byte arrayAdress[])
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number = blockNumber/4*4;
  int trailerBlock = largestModulo4Number + 3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber + 1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
  Serial.print(blockNumber);
  Serial.println(" is a data block:");

  

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 3;//return "3" as error message
  }

  

  //writing the block 
  status = mfrc522.MIFARE_Write(blockNumber, arrayAdress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);  
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 4;//return "4" as error message
  }
  Serial.println("block was written");
}

int ReadBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector


  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed (read): ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 3;//return "3" as error message
  }



  //reading a block
  byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 4;//return "4" as error message
  }
  Serial.println("block was read");

}

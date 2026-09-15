


void rfidUsingCheck() {
  do {
    if (rfidEnabled && digitalRead(button2)){
      rfidEnabled = false;
      digitalWrite(led1, HIGH); // change this to play a higher frequency noise with the buzzer
      digitalWrite(led2, LOW);
    } else if (digitalRead(button2)){
      rfidEnabled = true;
      digitalWrite(led1, LOW); // change this to play a lower frequency noise with the buzzer
      digitalWrite(led2, HIGH);
    }
  } while (digitalRead(button1) == false);
  
  if (rfidEnabled){
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("RFID line");
    for (byte i = 0; i < 6; i++) {

      key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
    }
  }

}


void rfidFunc() 
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
  writeBlock(block, blockcontent);

  //read the block back
  readBlock(block, readBackBlock);
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

int writeBlock(int blockNumber, byte arrayAdress[])
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

int readBlock(int blockNumber, byte arrayAddress[]) 
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

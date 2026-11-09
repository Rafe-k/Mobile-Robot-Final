void LineSensor(){
  int s1 = digitalRead(lineSensor);
  Serial.println(s1);
  // delay(100);
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

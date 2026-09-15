void colourSensor()
{
  // red photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // reading output frequency
  frequency = pulseIn(sensorOut, LOW);
  // printing the value
  Serial.print("R= ");
  Serial.print(frequency); // prints red colour frequency
  Serial.print(" ");
  delay(100);
  // green photodiodes
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // reading output frequency
  frequency = pulseIn(sensorOut, LOW);
  // printing the value
  Serial.print("G= ");
  Serial.print(frequency); // prints green colour frequency
  Serial.print(" ");
  delay(100);
  // blue photodiodes
    digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // reading output frequency
  frequency = pulseIn(sensorOut, LOW);
  // printing the value
  Serial.print("B= ");
  Serial.print(frequency); // prints blue colour frequency
  Serial.print(" ");
  Serial.println("");
  delay(1000);
}

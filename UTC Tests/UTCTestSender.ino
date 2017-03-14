char incomingByte;
void setup()
{

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.flush();
  Serial1.flush();
}

void loop()
{
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial1.println(incomingByte);
  }
}






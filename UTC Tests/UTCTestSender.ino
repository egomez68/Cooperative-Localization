/**
* This block is the Arduino unit number 1.)
* This block transmit the character received from the Python program over Serial1 to the Arduino unit that is being tested
*/
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






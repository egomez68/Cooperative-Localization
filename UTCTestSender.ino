#include <SD.h>
#include <SPI.h>

/*
 * miso -  50(digital)
 * scl - 52(digital)
 * mos1 - 51(digital)
 * cs - 53(digital)
 */

int CS_PIN = 53;

File file;
char incomingByte;
char str[2];
void setup()
{

  Serial.begin(9600);
  Serial.write(1);

  Serial1.begin(9600);

 //  Serial.write(1);
  // delay(10000);
  // Serial.write(1);
   
}

void loop()
{
  //while ( Serial1.available() > 0 ) {

   // incomingByte = Serial1.read();
   // if(incomingByte == '$'){
    //  Serial.println("");
    //}


 

  
  
    
  
  
}






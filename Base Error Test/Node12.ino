/* 
 *  File        : Node12.ino
 *  Description : Calculate and log 100 instances of node 12's base gps error.
 *  Author      : Edgar Gomez 
 */

//********** Library Includes **********//

#include <TinyGPS++.h>
#include <SD.h>
#include <SPI.h>

//********** Object Instantiation **********//

TinyGPSPlus gps;
File mySensorData;

//********** Variable Declaration **********//
 
double knownLng = -83.2785641700; // Known Longitude 
double knownLat =  40.7630277750; // Known Latitude
double lngError; // Calculated Longitude Error
double latError; // Calculated Latitude  Error
int CS_PIN = 53; // SD Module Chip-Select Pin
int count  = 0;  // Variable to keep track of loops


void setup()
{
  Serial.begin(115200); // Initialize Serial Communication
  Serial1.begin(9600);  // Initialize Serial 1 Communication
  initializeSD();
}

void loop()
{
  if(count < 100 ){
  mySensorData = SD.open("GPSData.txt", FILE_WRITE);

 while (Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
        getValues();

  Serial.print(lngError,6);
  mySensorData.print(lngError,6); // Write longitude value to SD card
  mySensorData.print(",");        // Write comma to SD card
  Serial.print(",");
  mySensorData.print(latError,6); // Write latitude value to SD card
  mySensorData.println("");       // Write comma to SD card
  Serial.println(latError,6);

  mySensorData.close();
  Serial.print("Count: "); Serial.println(count);
  count++;
  delay(100);
  }
  Serial.println("Done");
  }

//
void initializeSD()
{
  pinMode(10, OUTPUT); // Must declare 10 an output and reserve it to keep SD card happy
  SD.begin(CS_PIN);    // Initialize the SD card reader

  if (SD.exists("GPSData.txt")) { // Delete old data files to start fresh
      SD.remove("GPSData.txt");
  }
}

void getValues()
{
  if(gps.location.isValid()){
  lngError = knownLng - gps.location.lng(); // Calculate Longitude Error
  latError = knownLat - gps.location.lat(); // Calculate Latitude Error
  }
}

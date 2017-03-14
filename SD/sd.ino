//********** Library Includes **********//

#include <SD.h> // Must include the SD library

//********** Object Instantiation **********//

File myData;  // Instantiate a File object

//********** Variable Declaration **********//

int CS_PIN = 53; // Assign a pin for chip select

void setup(){
  initializeSD();  // Initialize the SD card reader
  
  mySensorData.print("This ");
  mySensorData.print("Is "); 
  mySensorData.print("How ");
  mySensorData.print("You ");
  mySensorData.print("Write ");
  mySensorData.print("To ");
  mySensorData.print("The ");
  mySensorData.print("SD ");
  mySensorData.println("Card."); // Notice the use of 'println' in order to start a new line
  mySensorData.print("Written By: Edgar Gomez");
  
  // Output:
  //    This Is How You Write To The SD Card.
  //    Written By: Edgar Gomez
}

void loop(){
}

void initializeSD(){
 pinMode(10, OUTPUT); // Must declare 10 an output to reserve it
 SD.begin(CS_PIN);    // Initialize the SD care reader
 
 if(SD.exists("myFile.txt")) // Delete old data files to start fresh
    SD.remove("myFile.txt");
}

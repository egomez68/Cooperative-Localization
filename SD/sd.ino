//********** Library Includes **********//

#include <SD.h> // Must include the SD library

//********** Object Instantiation **********//

File myData;  // Instantiate a File object

//********** Variable Declaration **********//

int CS_PIN = 53; // Assign a pin for chip select

void setup(){
  initializeSD();  // Initialize the SD card reader
  
  myData.print("This ");
  myData.print("Is "); 
  myData.print("How ");
  myData.print("You ");
  myData.print("Write ");
  myData.print("To ");
  myData.print("The ");
  myData.print("SD ");
  myData.println("Card."); // Notice the use of 'println' in order to start a new line
  myData.print("Written By: Edgar Gomez");
  
  // Output:
  //    This Is How You Write To The SD Card.
  //    Written By: Edgar Gomez
}

void loop(){
}

void initializeSD(){
 pinMode(10, OUTPUT); // Must declare 10 an output to reserve it
 SD.begin(CS_PIN);    // Initialize the SD care reader
 
 if(SD.exists("myData.txt")) // Delete old data files to start fresh
    SD.remove("myData.txt");
}

//********** Library Includes **********//

#include <EasyTransfer.h>


//********** Object Instantiation **********//

EasyTransfer ETin, ETout; 
#include <SD.h>
File mySensorData;

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int nodeID;
  double latErr;
  double lngErr;
};

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int nodeID;
  double latErr;
  double lngErr;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;

//********** Variable Declaration **********//

bool RSU = false,
     mobileNode1 = false,
     mobileNode2 = false;

int myArraySum = 0;
int myArray[3] = {0,0,0};
int CS_PIN = 53; // SD Module Chip-Select Pin

void setup(){
  Serial.begin(9600);
  delay(1000);
  //start the library, pass in the data details and the name of the serial port.
  ETin.begin(details(rxdata), &Serial);
  ETout.begin(details(txdata), &Serial);
  delay(1000);
  initializeSD();

  txdata.nodeID = 0;
}

void loop(){
  
    if (!RSU || !mobileNode1 || !mobileNode2){
      if(ETin.receiveData()){
        switch(rxdata.nodeID){
          case 1:
            RSU = true;
            break;
          case 2:
            mobileNode1 = true;
            break;
          case 3:
            mobileNode2 = true;
            }
           myArray[rxdata.nodeID] = rxdata.nodeID;
      }
    }

    //ETout.sendData();

    if(RSU && mobileNode1 && mobileNode2){
      for(int i = 0; i < 3 ; i++)
      myArraySum += myArray[i];
      Serial.print("It Worked! "); Serial.println(myArraySum);
      
      mySensorData = SD.open("GPSData.txt", FILE_WRITE);
      mySensorData.println(myArraySum); // Write longitude value to SD card
      mySensorData.close();
      
      RSU = false;
      mobileNode1 = false;
      mobileNode2 = false;
      }
}



void initializeSD()
{
  pinMode(10, OUTPUT); // Must declare 10 an output and reserve it to keep SD card happy
  SD.begin(CS_PIN);    // Initialize the SD card reader

  if (SD.exists("GPSData.txt")) { // Delete old data files to start fresh
      SD.remove("GPSData.txt");
  }
}

/* 
 *  File        : westRSU_Final.ino
 *  Description : Sketch implementing complete functionality of RSU
 *  Author      : Edgar Gomez 
 *  Date        : 10 March 2017
 *  Version     : 1.0
 */

//********** Library Includes **********//

#include <EasyTransfer.h>
#include <TinyGPS++.h>

//********** Object Instantiation**********//

EasyTransfer ETout; 
TinyGPSPlus gps;

struct SEND_DATA_STRUCTURE{
  double latErr;
  double lngErr;
};

SEND_DATA_STRUCTURE txdata;

//********** Variable Declaration **********//

double knownLat     =  40.7630776000,
       knownLng     = -83.8429966400;

int    interruptPin = 20,
       gpsPin       = 19;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ETout.begin(details(txdata), &Serial);
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(interruptPin), beginRIDE, RISING);  // Use this to start the R.I.D.E algorithm
  //attachInterrupt(digitalPinToInterrupt(gpsPin), receiveGPS, RISING);
  
}

void loop(){

  if (Serial1.available() > 0 ) {

    if (gps.encode(Serial1.read() ) ) {
      txdata.latErr = gps.location.lat() - knownLat;
      txdata.lngErr = gps.location.lng() - knownLng;
      //Serial.println("Sending data");
      ETout.sendData();
    }
  }
}

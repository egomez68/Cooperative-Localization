/* 
 *  File        : RSU_North_Rounds.ino
 *  Description : Sketch implementing complete functionality of RSU
 *  Author      : Edgar Gomez, Tim Coulter, Theodore Jantzen
 *  Date        : 31 March 2017
 *  Version     : 1.0
 */

//********** Library Includes **********//

#include <EasyTransfer.h>
#include <TinyGPS++.h>

//********** Object Instantiation**********//

EasyTransfer ETout; 
TinyGPSPlus gps;

struct SEND_DATA_STRUCTURE{
  int    nodeID;
  double latErr;
  double lngErr;
};

SEND_DATA_STRUCTURE txdata;

//********** Variable Declaration **********//

bool   ride = false;

double knownLat     =  40.7633224700,
       knownLng     = -83.8432279800;

int    interruptPin = 20,
       gpsPin       = 19;

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ETout.begin(details(txdata), &Serial);
  delay(1000);
  txdata.nodeID = 1;
  attachInterrupt(digitalPinToInterrupt(gpsPin), receiveGPS, RISING);
}

void loop(){

}

void receiveGPS(){
  txdata.latErr = gps.location.lat() - knownLat;
  txdata.lngErr = gps.location.lng() - knownLng;
  ETout.sendData();
}

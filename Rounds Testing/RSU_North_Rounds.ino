/* 
 *  File        : RSU_North_Rounds.ino
 *  Description : Sketch implementing complete functionality of RSU
 *  Author      : Edgar Gomez, Tim Coulter, Theodore Jantzen
 *  Date        : 31 March 2017
 *  Version     : 2.0
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

double knownLat     =  40.7633224700,
       knownLng     = -83.8429317700;

int gpsPin       = 19;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ETout.begin(details(txdata), &Serial);
  txdata.nodeID = 5;
}

void loop(){
  while (Serial1.available() > 0){
    if (gps.encode(Serial1.read())) {
        txdata.latErr = gps.location.lat() - knownLat;
        txdata.lngErr = gps.location.lng() - knownLng;
        ETout.sendData();
    }
  }

}

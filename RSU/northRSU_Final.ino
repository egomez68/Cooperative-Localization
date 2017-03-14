/* 
 *  File        : northRSU_Final.ino
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
  int latErr;
  int lngErr;
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
  attachInterrupt(digitalPinToInterrupt(interruptPin), beginRIDE, RISING);  // Use this to start the R.I.D.E algorithm
  attachInterrupt(digitalPinToInterrupt(gpsPin), receiveGPS, RISING);
  
}

void loop(){
  while(!ride){noInterrupts();}
  interrupts();
}

void receiveGPS(){
  txdata.latErr = gps.location.lat() - knownLat;
  txdata.lngErr = gps.location.lng() - knownLng;
  ETout.sendData();
}

/**
 * When Beacon is received, Begin R.I.D.E
 */
void beginRIDE() {
  ride = true;
  detachInterrupt(digitalPinToInterrupt(interruptPin));
}

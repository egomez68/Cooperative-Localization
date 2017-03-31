/* 
 *  File        : northRSU_Final.ino
 *  Description : Sketch implementing complete functionality of RSU
 *  Author      : Edgar Gomez 
 *  Date        : 10 March 2017
 *  Version     : 1.0
 */

//********** Library Includes **********//

#include <EasyTransfer.h>

//********** Object Instantiation**********//

EasyTransfer ETout; 

struct SEND_DATA_STRUCTURE{
  int    nodeID;
  double latErr;
  double lngErr;
};

SEND_DATA_STRUCTURE txdata;

//********** Variable Declaration **********//




void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ETout.begin(details(txdata), &Serial);
  delay(1000);
  txdata.nodeID = 1;
  delay(1000);
  ETout.sendData();
}

void loop(){

}


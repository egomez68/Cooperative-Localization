/* 
 *  File        : rttTestTX.ino
 *  Description : Used to find the RTT of a message with Easy Transfer 
 *  Author      : Edgar Gomez 
 *  Date        : 14 March 2017
 *  Version     : 1.0
 */

//********** Library Includes **********//

#include <EasyTransfer.h>

//********** Object Instantiation **********//

EasyTransfer ETin, ETout; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  double test;

};

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  double test;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;


  int i=1;
double startTime, stopTime, elapsedTime;

void setup(){
  Serial.begin(9600);
  delay(1000);
  //start the library, pass in the data details and the name of the serial port.
  ETin.begin(details(rxdata), &Serial);
  ETout.begin(details(txdata), &Serial);
  delay(1000);  
}

void loop(){

if(i == 1){
i++;
txdata.test = 0.0123;
startTime = micros();
ETout.sendData();
}

if(ETin.receiveData()){
stopTime = micros();
elapsedTime = stopTime - startTime;
Serial.print("Elapsed Time: "); Serial.println(elapsedTime/1000);
  
}
}

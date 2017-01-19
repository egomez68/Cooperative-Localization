// This module should: 
//  1) Receive messages sent by other nodes in the network.
//  2) Parse the messages to obtain gps (psuedo)errors. (These values will be strings!!!)
//  3) Convert the gps (psuedo)errors into a useable datatype (i.e float, double, int, etc)

#include <EasyTransfer.h>

// create object
EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE{
  float errorLat;
  float errorLng;
};

// name the data structure
RECEIVE_DATA_STRUCTURE neighData;

void setup(){
  Serial2.begin(9600);
  
  ET.begin(details(neighData),&Serial2);
}

void loop(){
  if(ET.receiveData()){
    float neighError = nodeData.errorLat;
    float neighError = nodeData.errorLng;
  }
}

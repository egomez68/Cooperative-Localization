// This module should broadcast gps (psuedo)errors.

#include <EasyTransfer.h>

// create EasyTransfer object
EasyTransfer ET;

struct SEND_DATA_STRUCTURE
{
  float errorLat;
  float errorLng;
  float timestamp;
}

// name the group of data contained in structure
SEND_DATA_STRUCTURE nodeData;

void setup()
{
  Serial2.begin(9600);
  // start EasyTrasfer on Serial2
  ET.begin(details(nodeData),&Serial2);
}

void loop()
{
  // must initialize these variables with respective values
  nodeData.errorLat = 
  nodeData.errorLng = 
  nodeData.timestamp = 

  // after the structure is created, we send the data
  ET.sendData();
}

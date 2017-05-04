## Overview
These are the libraries that must be included in all Arduino sketches.

### EG Transfer
EG Transfer is used to send data over the Xbee radio modules, with all of the checksums and parity bits taken out of the EasyTransfer library to speed up the performance of the library
so time is not wasted in the sending of data.

### EasyTransfer
The library used to send data over the Xbee radio modules

### TinyGPS++
The library used to return the latitude and longitude of the GPS reciever, connected to Seral1, or whatever Serial line is used by the GPS 
receiver.

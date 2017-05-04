// GPS module should provide functions that parse through a received NMEA sentence
// and extract relevant information. (Such as latitude and longitude.)

#include <TinyGPS++.h>

// Assign pins to connect gps to
int RXPin; // add value for pin
int TXPin; // add value for pin

// Instantiate TinyGPS++ object named "gps"
TinyGPSPlus gps;

// Instantiate integer with GPS baud rate I
int GPSBaud = 9600; // add value for baud rate

void setup()
{
  // Set baud rate for GPS serial communications
  Serial1.begin(GPSBaud);   
}

void loop()
{
  while (Serial1.available() > 0) // check for GPS data
  {
    if (gps.encode(Serial1.read())) // encode GPS data
    {
      float gpsLng,gpsLat;
      gpsLng = gps.location.lng(); // get longitude
      gpslat = gps.location.lat(); // get latitude
    }
  }
}
      
      
      

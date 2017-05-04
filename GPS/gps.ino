// GPS module should provide functions that parse through a received NMEA sentence
// and extract relevant information. (Such as latitude and longitude.)

#include <TinyGPS++.h>

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
      gpsLat = gps.location.lat(); // get latitude
      Serial.print("Lat: "); Serial.println(gpsLat);
      Serial.print("Lng: "); Serial.println(gpsLng);
    }
  }
}
      
      
      

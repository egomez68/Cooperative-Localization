//GPS Library
#include <TinyGPS++.h>

TinyGPSPlus gps; // create gps object

double knownLat,knownLng; 
double gpsLat,gpsLng,radius;
double errorLat, errorLng;
String errorX, errorY, error;


#define E_RADIUS 6378137 // Equatorial radius of Earth in meters according to NASA as of May 19, 2016
#define P_RADIUS 6356752 // Polar radius of Earth in meters according to NASA as of May 19, 2016

void setup() {
  Serial1.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  
  // If GPS Update
    while (Serial1.available() > 0) { // Check for data available in the receiver


    // Read and encode the data
    if (gps.encode(Serial1.read()) ) {
      gpsLat = gps.location.lat(); // store latitude into lat variable
      gpsLng = gps.location.lng(); // store longitude into the lng variable
      
      // Calculate the Error
      errorLat = knownLat - gpsLat; // Latitude Error 
      errorLng = knownLng - gpsLng; // Longitude Error

      // Transform longitude and latitude into cartesian coordinates
      errorToCart(errorLat, errorLng); 
      
      // Transmit the Known Error
      Serial2.write(error);
    }
  }
}

double toRadians (double degree) {
  return (degree * 2 * PI / 360);
}

double errorToCart(double errorLat, double errorLng) {
    radius = sqrt(sq(E_RADIUS * cos(toRadians(errorLat))) + sq(P_RADIUS * sin(toRadians(errorLat))));
    errorX = String(radius * cos(toRadians(errorLat)) * cos(toRadians(errorLng)),5);
    errorY = String(radius * cos(toRadians(errorLat)) * sin(toRadians(errorLng)),5);
    error = errorX + ";" + errorY;
}

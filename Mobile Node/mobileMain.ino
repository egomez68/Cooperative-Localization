/* 
 *  File        : mobileMain.ino
 *  Description : Implements the R.I.D.E localization algorithm. 
 *  Author      : Edgar Gomez 
 *  Date        : 14 March 2017
 *  Version     : 1.0
 */
 
/*** Make sure to incoroporate the "beginRide" function - See the RSU ***/

//********** Library Includes **********//

#include <EasyTransfer.h>
#include <TinyGPS++.h>
#include <SD.h>

//********** Object Instantiation **********//

EasyTransfer ETin, ETout; 
TinyGPSPlus gps;
File dataFile;

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int latErr;
  int lngErr;
};

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int latErr;
  int lngErr;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;

//********** Variable Declaration **********//

bool newErrorFlag = false;
int CS_PIN = 53;
int F = 2;
int i = 0;
int n_ii = 15;
int interruptPin = 20;
int gpsPin = 19;
double GPSReceiveTime; // Store the value of micros() in this variable and save it to the SD card
double gpsLat, gpsLng;
double x_prevLat, x_prevLng;
double x_newLat, x_newLng;
double neighLatError[15], neighLngError[15];
double myLatError,myLngError;

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  //start the library, pass in the data details and the name of the serial port.
 
  // Get rid of all uses of EZ transfer
  ETin.begin(details(rxdata), &Serial);
  ETout.begin(details(txdata), &Serial);
  initializeSD();
  //attachInterrupt(digitalPinToInterrupt(interruptPin), beginRIDE, RISING);  // Use this to start the R.I.D.E algorithm
  attachInterrupt(digitalPinToInterrupt(gpsPin), receiveGPS, RISING);
}

void loop(){
  // Make sure to change the name of the file in all of the locations that it is used
  //dataFile = SD.open("test.txt", FILE_WRITE);
  
  if(newErrorFlag == true){
     // I moved the opening of the dataFile here so we are only opening the file when we are going to write to it
  ` dataFile = SD.open("test.txt", FILE_WRITE);
    txdata.latErr = myLatError;
    txdata.lngErr = myLngError;
    ETout.sendData();
    newErrorFlag = false;
    dataFile.print(x_newLat,6);
    dataFile.print(",");
    dataFile.println(x_newLng,6);
    dataFile.close(); // I had to add this or else the data would not get wrote to the SD card. It would create the file but not write anything. Once I closed the file it started working properly
  }
  
 // Remember to clear all of the arrays and reset i back to 0 - I don't know where that should be done.
  if(newErrorFlag == false){
    if(ETin.receiveData()){
      neighLatError[i] = rxdata.latErr;
      neighLngError[i] = rxdata.lngErr;
      i++;
    }
  }
}

/**
 * Interrupt to receive the GPS readings every tenth of a second
 */
void receiveGPS() {
  while (Serial1.available () > 0) {
     GPSReceiveTime = micros(); // I got this working - I was able to make a function call to micros() in the ISR
     if (gps.encode(Serial1.read() ) ) {
      x_prevLat = gps.location.lat();
      x_prevLng = gps.location.lng();
    }
  }
 // These two function calls should not be here - they should be in the main loop or elsewhere - not in the ISR
  //x_newLat = positionEstimateUpdateLatitude(x_prevLat, neighLatError, n_ii, F);
  //x_newLng = positionEstimateUpdateLongitude(x_prevLng, neighLngError, n_ii, F);
  newErrorFlag = true;
}
/**
 * Compare function to be used by quicksort to arrange elements
 * in ascending order.
 */
int qsortCompare(const void * arg1, const void * arg2) {
  double * a = (double *)arg1;  // cast to pointers to doubles
  double * b = (double *)arg2;

  // a less than b? 
  if (*a < *b)
    return -1;

  // a greater than b?
  if (*a > *b)
    return 1;

  // must be equal
  return 0;
}

/*** Consider merging positionEstimateUpdateLatitude and Longitude ***/

/**
 * Performs the position estimate update stage in order to calculate
 * the new latitude of the mobile node.
 * 
 * @param x_prev
 * @param diff_error_set
 * @param n_ii
 * @param F
 * 
 * @returns x_new
 */
double positionEstimateUpdateLatitude(double x_prev, double* diff_error_set, int n_ii, int F) {

  // Initialize Local Variables
  int uprcount, lwrcount;

  // Sort error_set by Relative Bias and Estimated Relative Bias 
  qsort(diff_error_set, n_ii, sizeof(double), qsortCompare);
  double *srtd_neigh = diff_error_set;
  double x_new;
  
  //If Number of neighbors is greater than Redundency Parameter
  if (n_ii>F) {

    // Remove values smaller than 0 in the F smallest values
    int lwrcount = 0;
    while (lwrcount<F && srtd_neigh[lwrcount]<0)
      lwrcount = lwrcount + 1;

    // Remove values larger than 0 in the F largest values
    int uprcount = n_ii;
    while (uprcount > n_ii - F && srtd_neigh[uprcount] > 0) {
      uprcount = uprcount - 1;
    }

    // Dynamically Allocate Memory for kept_neigh Array
    int kept_neigh_size = uprcount - lwrcount;
    double* kept_neigh = 0;
    kept_neigh = new double[kept_neigh_size];


    // Remove up to 2F lowest and 2F highest gps error estimates 
    for (int i = 0; i < kept_neigh_size; i++)
      kept_neigh[i] = srtd_neigh[i + lwrcount];
    
    // Calculate number of kept neighbors
    int num_kept = uprcount - lwrcount;

    // Calculate Weight to Use in Update (m_k)
    double m_k = 1.0 / (num_kept + 1);

    // Calculate Sum of Pseudo Errors 
    double sumPseudoErrors = 0;
    for (int i = 0; i<num_kept; i++)
      sumPseudoErrors += kept_neigh[i];

    // Calculate Leaky-Average of GPS Errors
    myLatError = m_k*sumPseudoErrors;  
    
    // Calculate position estimate (x_new)
    x_new = x_prev - myLatError;

  }

  else
    x_new = x_prev;
    
  return x_new;
}

/**
 * Performs the position estimate update stage in order to calculate
 * the new longitude of the mobile node.
 * 
 * @param x_prev
 * @param diff_error_set
 * @param n_ii
 * @param F
 * 
 * @returns x_new
 */
double positionEstimateUpdateLongitude(double x_prev, double* diff_error_set, int n_ii, int F) {

  // Initialize Local Variables
  int uprcount, lwrcount;

  // Sort error_set by Relative Bias and Estimated Relative Bias 
  qsort(diff_error_set, n_ii, sizeof(double), qsortCompare);
  double *srtd_neigh = diff_error_set;
  double x_new;
  
  //If Number of neighbors is greater than Redundency Parameter
  if (n_ii>F) {

    // Remove values smaller than 0 in the F smallest values
    int lwrcount = 0;
    while (lwrcount<F && srtd_neigh[lwrcount]<0)
      lwrcount = lwrcount + 1;

    // Remove values larger than 0 in the F largest values
    int uprcount = n_ii;
    while (uprcount > n_ii - F && srtd_neigh[uprcount] > 0) {
      uprcount = uprcount - 1;
    }

    // Dynamically Allocate Memory for kept_neigh Array
    int kept_neigh_size = uprcount - lwrcount;
    double* kept_neigh = 0;
    kept_neigh = new double[kept_neigh_size];


    // Remove up to 2F lowest and 2F highest gps error estimates 
    for (int i = 0; i < kept_neigh_size; i++)
      kept_neigh[i] = srtd_neigh[i + lwrcount];
    
    // Calculate number of kept neighbors
    int num_kept = uprcount - lwrcount;

    // Calculate Weight to Use in Update (m_k)
    double m_k = 1.0 / (num_kept + 1);

    // Calculate Sum of Pseudo Errors 
    double sumPseudoErrors = 0;
    for (int i = 0; i<num_kept; i++)
      sumPseudoErrors += kept_neigh[i];

    // Calculate Leaky-Average of GPS Errors
    myLngError = m_k*sumPseudoErrors;  
    
    // Calculate position estimate (x_new)
    x_new = x_prev - myLngError;

  }

  else
    x_new = x_prev;
    
  return x_new;
}

/*** Consider merging positionEstimateUpdateLatitude and Longitude ***/

void initializeSD()
{
  pinMode(10, OUTPUT); // Must declare 10 an output and reserve it to keep SD card happy
  SD.begin(CS_PIN);    // Initialize the SD card reader

 // Make sure the name of the file is small enough 
  if (SD.exists("test.txt")) { // Delete old data files to start fresh
      SD.remove("test.txt");
  }
}


  

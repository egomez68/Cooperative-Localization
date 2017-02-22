/********** Library Imports **********/
#include <TinyGPS++.h>
#include <EasyTransfer.h>
/********** Object Instantiation **********/
EasyTransfer ETin, ETout;
TinyGPSPlus gps;

/********** Structure Instantiation **********/
struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  double rxError;
};

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  double txError;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;

/********** Global Variables **********/
static const int F = 2; // Redundancy Parameter

double gpsLat, gpsLng; // GPS Related Variable Initialization
double x_prev; // Previous Position Estimate
double x_new; // Current Position Estimate
int n_ii = 15;
double neigh_error_set[15];

int count = 0;



void setup() {
Serial.begin (9600);
ETin.begin(details(rxdata), &Serial);
ETout.begin(details(txdata), &Serial);
}

void loop() {


  while (Serial1.available () > 0) {
     if (gps.encode(Serial1.read() ) ) {
     gpsLat = gps.location.lat();
     gpsLng = gps.location.lng();
    }
  }


//if ET data is received, do this
  if(ETin.receiveData())
  {
    neigh_error_set[count] = rxdata.rxError; //add received Latitude error to error array
    count++; //increment index for next error
  }
 
/////////////////////////////////////////////////////////////////////
//////////// START OF CODE TO PUT INTO THE GPS INTERRUPT ////////////
/////////////////////////////////////////////////////////////////////
  // Execute the positionEstimateUpdate Stage of R.I.D.E
 x_new = positionEstimateUpdate(x_prev, neigh_error_set, n_ii, F);
 x_prev = x_new;
 ETout.sendData();
/////////////////////////////////////////////////////////////////////
//////////// END OF CODE TO PUT INTO THE GPS INTERRUPT //////////////
/////////////////////////////////////////////////////////////////////

}

/********** Function Definitions **********/


// positionEstimateUpdate: Performs Stage 3 of R.I.D.E (Position Estimate Update)  
// parameters:  x_prev: Previous position estimate
//              diff_error_set: Difference in pseudoerrors
//              n_ii: Number of neighbors
//              F: Redundancy Parameter
//              Vs: Velocity Measurement
//              Ts: Timestep
// returns: x_new: New postition estimate

double positionEstimateUpdate(double x_prev, double* diff_error_set, int n_ii, int F) {

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
      
    
    // Calculate position estimate (x_new)
    x_new = x_prev - m_k*sumPseudoErrors;

  }

  else
    x_new = x_prev;
  
  return x_new;
}

// quicksort function
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

}  // end of quicksort Function




///////////// MISC ////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FALSE 1
#define TRUE 0


///////////// DEFINE STATE INDEXES ///////////////////////////////////////////////////////////////////////////////////////////
#define RECEIVEMODE 0
#define CRITICALPOWERMODE 1
#define LOWPOWERMODE 2
#define TRANSMITMODE 3
#define DETUMBLEMODE 4
#define PROCESSINGMODE 5
#define THERMALCONTROLMODE 6
#define TRACKINGMODE 7
#define LAUNCHMODE 8

///////////// DEFINE THRESHOLDS //////////////////////////////////////////////////////////////////////////////////////////////////////

  //Time delay in ms
#define LAUNCHDELAY 1000  


  //Receive Signal Input (0 = no sigal, 1 = signal)
#define RECSIGNALTHRESHOLD 1

  //Crit Power Threshold
#define CRITPOWERTHRESHOLD 1000

  //Low Power threshold (1 = xKj)
#define LOWPOWERTHRESHOLD 500

  //Transmit Buffer capacity (0 = not-full, 1 = full)
#define TRANSMITBUFFERTHRESHOLD 1

  //Detumble Threshold (1 = xRad/sec)
#define DETUMBLETHRESHOLD 500

  //Memory Availability Threshold (1 = xkB)
#define MEMORYTHRESHOLD 500

  //Temperature Threshold
#define TEMPTHRESHOLD 500







//////////////////////////////////////////////////////  Function Definitions //////////////////////////////////////////////////////////////////




//Payload

//Get raw data from the sensor, store with time and attitude in SD card
void getRaw(int Attitude[], int Time);
//Gets raw data from SD card memory, process this and return in a form of your choosing to be transmitted. 
int* process();
//Returns the amount of memory stored in SD card
int memAvail();

  
//ACDS

//Returns a 3 int long array (x,y,z axis) of current attitude 
int* getAttitude();
//Returns the system angular velocity (magnitude)
int getAngVel();
//Take a target attitude and implement changes required to achieve this
void adjAttitude(int* targetAttitude);


//Comms

//Stores and processes data, returns high if transmit is required
int TransmitStore(int* data);

//Transmit data to ground
void TransmitData();

//Stores received data in preallocated memory
int* receive();

//power

//Return battery capacity
int batteryCap();

//Thermal

//Return temperature
int getTemp();

//OBCS
int getTime();
























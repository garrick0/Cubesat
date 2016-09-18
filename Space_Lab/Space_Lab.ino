
//Implement Timer state checking
//Written by Samuel Gleeson. This function checks the system states of our satellite based on generated test input
//and changes functionality accordingly
//Date: 18 Sep
//Version 8
//Changes
//      - Added payload processing stubs to main
//      - Created multi file program
//      - Created hardware model(Breadboard)
//      - Added ADCS processing
//      - Added Transmit processing

//Next steps 
//        - Add all inputs
//       - Create Git Repository
//      - Add ability to change target attitude from ground


//Known Bugs
//      - 




/////////////////////////////////////////////////// EXTERNAL FILE PUBLIC FUNCTIONS //////////////////////////////////////


#include "main.h"
#include "timers.c"
#include "states.c"
#include "payload.c"
#include "ADCS.c"
#include "Communications.c"
#include "Power.c"
#include "Thermal.c"


///////////////////////////////////////////// Main ////////////////////////////////////////////////////////////////////////

int counter2 = 0;
int ADCSCounter = 0;
int PayloadCounter = 0;
int counter0 = 0;





///////////////////  Main File Function Declarations //////////////////////


//Functions
int getStates(int* comparators, int* StateCheckFlag);

void getComparators(int* comparators);


//OBCS
int getTime() {
}






 //Current system state holder
 struct state CurrentState;


//Initialise Comparator Values
int power;
int rotation;
int memory;
int transBuf;
int recSig;




//Stores attitude out
int* attitude;
//Stores time out
int timestamp;

//Sampling flags from timers

//Payload Sampling Flag
int PayFlag = FALSE;

//ACDS Flag
int ADCSFlag = FALSE;

//StateCheck flag
int StateCheckFlag = FALSE;

//Transmit Flag
int TransmitFlag = FALSE;


//Buffer to store stringout
char buffer[100];

//Test string for transmit
int transArray[] = {0,0,0};

//Target Attitude
int targetAttitude[] = {0,0,0};



//Array to hold comparator values
int comparators[10];

//Value to store current time
int currentTime;

//Value to store current Attitude
int* currentAttitude;

//Buffer for processed data
int* processed_data;

//Input Data
int* inputData;





////////////////////////////////// SETUP FUNCTION //////////////////////////////////////////////////////////////////


//Setup function to init parameters
void setup() {

  //Disable Interrupts
  noInterrupts();
  
  //Initialise the operating state of each mode
  initModes(Modes);
  
  //Init system in Tracking Mode
  CurrentState = Modes[TRACKINGMODE];
  changeMode(CurrentState,0);

  
  // ENABLE SERIAL (Baud 9600)
  Serial.begin(9600);


  setupTimers();    //SETUP TIMERS

  //Switch on Timer Interrupts

  //Turn on state checking timer
  TIMSK1 = 0x01;        //Timer1 INT Reg: Timer2 Overflow Interrupt Enable

  //Turn on sampling timer
  TIMSK2 = 0x01;
  
  //TIMSK0 = 0x01;
  
  //Turn on interrupts
  Serial.print("\n");
  
  Serial.print(CurrentState.name);
  //Timer delay for launch mode
  delay(LAUNCHDELAY);

  //Enable interrupts
  interrupts();

}



///////////////////////////////////////////// MAIN LOOPING PROCEDURE //////////////////////////////////



void loop() { //Check state and output state to console


  ///////////////////////////////////// Check States ////////////////////////////////////
  //Change System State
  //StateCheckFlag = getStates(int* comparators, int* StateCheckFlag);

  
  if (StateCheckFlag == TRUE) {
    //Serial.print(TransmitFlag);
    
    getComparators(comparators);
    checkStates(comparators);
    StateCheckFlag = FALSE;
  }

  //////////////////////////////////// Get Payload Data ////////////////////////////////////
  
  //Get Payload Data
  if (PayFlag == TRUE) {

    //Serial.print("Here");
    //Only get in select mode
    if (CurrentState.payloadON == TRUE) {
      //store time
      currentTime = getTime();

      //store attitude
      currentAttitude = getAttitude();

      //get and store raw data
      getRaw(currentAttitude, currentTime);
      
      Serial.print("Getting raw data\n");
    }

    PayFlag = FALSE;
  }




  //////////////////////////////////// Adjust ADCS ////////////////////////////////////////////////////
  //Adjust ADCS
  if (ADCSFlag == TRUE) {
    //Adjust ADCS
    //Serial.print("adcs flag in fun\n");
    if (CurrentState.ADCSON == TRUE) {
      //Adjust ADCS
      adjAttitude(targetAttitude);
      Serial.print("Adjusting Attitude\n");
    }
    
    //turn off flag
    PayFlag = FALSE;
  }
  
  
  //////////////////////////////////// Process Raw Data ///////////////////////////////////////////////////////////////

 // Process raw data
  processed_data = process();
  

  /////////////////////////////// Transmit Raw Data  //////////////////////////////////////////////////////

//save to transmitflag and store in transmit buffer
  TransmitFlag = TransmitStore(processed_data);





  
  
  //Serial.print(CurrentState.name);
  Serial.print(".\n");
  delay(500);
  
}





















int getStates(int* comparators, int* StateCheckFlag) {
  return 0;
}




//Timer1 Overflow Interrupt Vector, called every 1s (checks states)
ISR(TIMER1_OVF_vect) {
  //Serial.print("\n");
  //Serial.print("hitTimer1");
  StateCheckFlag = TRUE;
  TCNT1 = TIMERRESOLUTION1-timerIncrements1;           //Reset Timer to value
  TIFR1 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  
};  





//Timer2 Overflow Interrupt Vector, called every 40Hz (use for sampling)
ISR(TIMER2_OVF_vect) {
  //Serial.print("\n");
  //Serial.print("hitTimer2");

  ADCSCounter = ADCSCounter +1;
  PayloadCounter = PayloadCounter+1;

  
  //Adjust attitude every 100ms
  if (ADCSCounter == 1000) {
    //adjAttitude(attitude);
    ADCSFlag = TRUE;
    ADCSCounter = 0;
  }
  
  //Get payload every 500ms
  if (PayloadCounter == 2000) {
    PayloadCounter = 0;
    //Serial.print("Toggling Payload Flag\n");
    //attitude = getAttitude();
    //timestamp = getTime();
    //getRaw(attitude, timestamp);
    PayFlag = TRUE;
    
  }
  
  
  //Reset interrupt
  TCNT2 = TIMERRESOLUTION2-timerIncrements2;
  TIFR2 = 0x00;
  
};  





  ///////////////////// CHECK FOR SYSTEM STATE TRIGGER ///////////////////////////
void checkStates(int* comparators) {

  
  //loop through each check variable
  //check with corresponding state
  int trackingCheck=0;
  
  for (int i = 0; i < 7; i++) {     //Loop through the 6 states that are controlled by thresholds in main

    // Check thresholds
    // Check priority
    if ((comparators[i] >= Modes[i].threshold)&&(Modes[i].priority <= CurrentState.priority)) {           //Change state if threshold is exceeded and state priority is higher than current                      
      if (CurrentState.name != Modes[i].name) {
        //Change state
         CurrentState = Modes[i];
         changeMode(CurrentState,power);
      }
        
  
    }
    else {
      trackingCheck++;
    }

  }
  //If no thresholds are exceeded move back to Tracking Mode
  if (trackingCheck ==7) {
    if (CurrentState.name != "Tracking") {
      CurrentState = Modes[TRACKINGMODE];
      changeMode(CurrentState,power);
        
    }
    
  }

}

void getComparators(int* comparators) {
    //Use public functions to get data
  
  //Receive
  comparators[0] = 0;
  //Low power
  comparators[1] = batteryCap();
  //Low Power
  comparators[2] = batteryCap();
  //Transmit
  comparators[3] = TransmitFlag;
  //Rotation
  comparators[4] = getAngVel();
  //Memory
  comparators[5] = memAvail();
  //Temp
  comparators[6] = getTemp();
  
  
  
 // Serial.print("First\n");
  
 // for (int i = 0; i < 6; i++) {
  //  Serial.print(comparators[i]);
  //  Serial.print("\n");
  //}
  //Serial.print("Second\n");
  //set in array, can use pointers later
  //comparators = {recSig,power,power,transBuf,rotation,memory};
  
  //recSig,power,power,transBuf,rotation,memor
  
}




////////////////////////////////////// CHANGE SYSTEM FUNCTIONALITY BASED ON STATE ///////////////////

void changeMode(struct state CurrentState, int power) {
  

  
  
  //set payload on if tracking
  //if (CurrentState.payloadON == TRUE) {
    //digitalWrite(payloadONOFF, HIGH);
  //}
  //else {
  // digitalWrite(payloadONOFF, LOW);
  //}
  
  if (CurrentState.name == "LowPower") {
 //   if (power > 1000) {
   //   CurrentState = Modes[CRITICALPOWERMODE];
   // }
  }
  
  
  //Read in data if mode is receive
  if (CurrentState.name == "Receive") {
    //readReceived();
  }
  sprintf (buffer, "Transitioning to mode %s",CurrentState.name);
  Serial.print(buffer);
}

///////////////////////////////////////////////////////////////////////////////////



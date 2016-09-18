///////////////////////////////// DEFINE STATE OPERATION ///////////////////////////////////////////

#include "main.h"
struct state
{
   const char* name;
   int priority;
   int payloadON;
   int threshold;
   int ADCSON;
};

//typedef struct state State;

  //Hold modes in array of state structs
 struct state Modes[8];



 
void initModes(struct state* Modes)
{

    Modes[RECEIVEMODE].name = "Receive";
    Modes[RECEIVEMODE].priority = 0;
    Modes[RECEIVEMODE].payloadON = FALSE;
    Modes[RECEIVEMODE].ADCSON = FALSE;
    Modes[RECEIVEMODE].threshold = RECSIGNALTHRESHOLD;
    
    
      //Low Power State
    Modes[LOWPOWERMODE].name =  "LowPower";
    Modes[LOWPOWERMODE].priority = 2;
    Modes[LOWPOWERMODE].payloadON = FALSE;
    Modes[LOWPOWERMODE].ADCSON = TRUE;
    Modes[LOWPOWERMODE].threshold = LOWPOWERTHRESHOLD;
     
      //Transmit Mode
    Modes[TRANSMITMODE].name = "Transmit";
    Modes[TRANSMITMODE].priority = 3;
    Modes[TRANSMITMODE].payloadON = FALSE;
    Modes[TRANSMITMODE].ADCSON = TRUE;
    Modes[TRANSMITMODE].threshold = TRANSMITBUFFERTHRESHOLD;
  
      //Detumble Mode
    Modes[DETUMBLEMODE].name = "DeTumble";
    Modes[DETUMBLEMODE].priority = 5;
    Modes[DETUMBLEMODE].payloadON = FALSE;
    Modes[DETUMBLEMODE].ADCSON = TRUE;
    Modes[DETUMBLEMODE].threshold = DETUMBLETHRESHOLD;
    
      //Processing Mode
    Modes[PROCESSINGMODE].name = "Processing";
    Modes[PROCESSINGMODE].priority = 6;
    Modes[PROCESSINGMODE].payloadON = FALSE;
    Modes[PROCESSINGMODE].ADCSON = TRUE;
    Modes[PROCESSINGMODE].threshold = MEMORYTHRESHOLD;
    
    
    //States below do not use comparators in the main loop
    
        //Crit Power Mode
    Modes[CRITICALPOWERMODE].name = "CritPower";
    Modes[CRITICALPOWERMODE].priority = 1;
    Modes[CRITICALPOWERMODE].payloadON = FALSE;
    Modes[CRITICALPOWERMODE].ADCSON = FALSE;
    Modes[CRITICALPOWERMODE].threshold = CRITPOWERTHRESHOLD;
  
        //THERMAL CONTROL
    Modes[THERMALCONTROLMODE].name = "ThermControl";
    Modes[THERMALCONTROLMODE].priority = 7;
    Modes[THERMALCONTROLMODE].payloadON = FALSE;  
    Modes[THERMALCONTROLMODE].ADCSON = TRUE;
    Modes[THERMALCONTROLMODE].threshold = TEMPTHRESHOLD;
   
    
      //Tracking Mode
    Modes[TRACKINGMODE].name = "Tracking";
    Modes[TRACKINGMODE].priority = 8;
    Modes[TRACKINGMODE].payloadON = TRUE;  
    Modes[TRACKINGMODE].ADCSON = TRUE;
    
    return;
}

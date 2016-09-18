
#include "Arduino.h"
#include "main.h"


//////////// TIMER DEFINITIONS ///////////////////////

//////////////TIMER 1 //////////
#define CPUFREQ1 16000000
#define TIMERRESOLUTION1 65536
#define PRESCALER1 1024
#define SAMPLEFREQ1 1 



////////////Timer 2 ////////// 10ms
#define CPUFREQ2 16000000
#define TIMERRESOLUTION2 255
#define PRESCALER2 1024
#define SAMPLEFREQ2 100




////////////Timer 0 //////////
#define CPUFREQ0 16000000
#define TIMERRESOLUTION0 255
#define PRESCALER0 1024
#define SAMPLEFREQ0 100



//Timer Variables
// Frequency at which an increment pulse is received
//const int pulseFreq = CPUFREQ2/PRESCALER2;
  
//How many timer increments for each timer

//Timer 1 length
const int timerIncrements1 = CPUFREQ1/SAMPLEFREQ1/PRESCALER1;
//Timer 2 length
const int timerIncrements2 = CPUFREQ2/SAMPLEFREQ2/PRESCALER2;





void setupTimers() {

  //////////////////////TIMER1 ////////////////////////
  
    TCCR1B = 0x00;        //Disbale Timer1 while we set it up
    TCNT1  = TIMERRESOLUTION1-timerIncrements1;       //Reset Timer Count (overflow on 65535)
    TIFR1  = 0x00;        //Timer1 INT Flag Reg: Clear Timer Overflow Flag
    TCCR1A = 0x00;        //Timer1 Control Reg A: Normal port operationq, Wave Gen Mode normal
    TCCR1B |= (1 << CS10);    //PRESCALER = 1024
    TCCR1B |= (1 << CS12);    //PRESCALER = 1024
  

  //Ensure timer is within resolution
  if (timerIncrements1 > TIMERRESOLUTION1) {
    //Serial.print("Timer 1 value is greater than total timer resolution");
    
  }
  
  
  //////////////////////TIMER2 ////////////////////////
  
    TCCR2B = 0x00;        //Disbale Timer1 while we set it up
    TCNT2  = TIMERRESOLUTION2-timerIncrements2;       //Reset Timer Count (overflow on 65535)
    TIFR2  = 0x00;        //Timer1 INT Flag Reg: Clear Timer Overflow Flag
    TCCR2A = 0x00;        //Timer1 Control Reg A: Normal port operationq, Wave Gen Mode normal
    TCCR2B |= (1 << CS20);    //PRESCALER = 1024
    TCCR2B |= (1 << CS22);    //PRESCALER = 1024
  

  //Ensure timer is within resolution
  if (timerIncrements2 > TIMERRESOLUTION2) {
    //Serial.print("Timer 2 value is greater than total timer resolution\n");
    //Serial.print(timerIncrements2);
    //Serial.print("\n");
    //Serial.print(TIMERRESOLUTION2);
    //Serial.print("\n");
     
  }    
}

#ifndef _LOCKKK_
#define _LOCKKK_

#include "Arduino.h"
#include "Command_parser.h"
#include "Board_Comms.h"
#include<math.h>

#define MOTOR 4
#define RED 7
#define ORANGE 3
#define GREEN 9
#define BUZZER 8
#define LIM_SWITCH1 6

class Lock{
  private:
  
  int STATUS,RIDE_STATUS;
  String USER,IMEI,DEV_CODE,TIME;
  char *LAT,*LONG;

  uint32_t unlocking,locking;        //time variables
  const uint32_t period = 300000 ;   //5 mins for gps  NOTE: millis() overflow period is 50 days
  uint32_t next_D0;
  
  Board_Comms comm1;

  public:

  Lock()
  {

  }

  void INIT()
  {
    STATUS=1;                      // status=1-> Locked   status=0->unlocked   
    RIDE_STATUS=0;                 //0-> Ride ended   1-> Ride Ongoing    2-> Ride Halted
    IMEI = "863158022988725";
    DEV_CODE = "OM";
    TIME = "1497689816";  //Default
    USER = "0.0.0.0.0";   //Default
    LAT="0.000000";
    LONG="0.000000";

    locking =0;     //Assume lock is locked at time=0
    unlocking=-1;   //-1 denotes lock is locked
    next_D0=period;
        
    pinMode(MOTOR,OUTPUT);
    pinMode(RED,OUTPUT);
    pinMode(ORANGE,OUTPUT);
    pinMode(GREEN,OUTPUT);
    pinMode(BUZZER,OUTPUT);
    
    pinMode(LIM_SWITCH1,INPUT);
//    pinMode(LIM_SWITCH2,INPUT);
    
    STATUS = get_lock_status();
    
    if(STATUS==0)
    {
      locking=-1;
      unlocking=0;
    }
  }
  
  int unlock();

  int on_lock();

  int lock();

  int halt();

  void LED();

  void buzzer(int n);

  String send_server(String command);

  int get_lock_status();

  void RFID_setup();

  int RFID_read();

  void com_par(String command);

  String package_creator();

  String Local_time();

  int bat_stat();

  String get_gps();

  int GPS_send(String loc);

  int GPS_periodic();

  void err_buzzer(int j);
  
};

#endif

#ifndef _LOCKKK_
#define _LOCKKK_

#include "Arduino.h"
#include "Command_parser.h"
#include "Board_Comms.h"

#define MOTOR 4
#define LED1 2
#define LED2 3
#define BUZZER 8
#define LIM_SWITCH1 6
#define LIM_SWITCH2 7

class Lock{
  private:
  
  int STATUS,RIDE_STATUS;
  int COMM_STATUS;
  String USER,IMEI,DEV_CODE,TIME;

  Board_Comms comm1;

  public:

  Lock()
  {

  }

  void INIT()
  {
    STATUS=1;                      // status=1-> Locked   status=0->unlocked
    RIDE_STATUS=0;                 //0-> Ride ended   1-> Ride Ongoing    2-> Ride Halted
    COMM_STATUS=0;                 //comm_status=0-> Not connected to server   comm_status=1-> Connected to server
    IMEI = "863158022988725";
    DEV_CODE = "OM";
    TIME = "1497689816";  //Default
    USER = "0.0.0.0.0";
    
    pinMode(MOTOR,OUTPUT);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(BUZZER,OUTPUT);
    
    pinMode(LIM_SWITCH1,INPUT);
    pinMode(LIM_SWITCH2,INPUT);
    
    STATUS = get_lock_status();
  }
  
  int unlock();

  int lock();

  int LED();

  int buzzer();

  String send_server(String command);

  int get_lock_status();

  void RFID_setup();

  int RFID_read();

  void com_par(String command);

  String package_creator();

  char* Local_time();
  
};

#endif

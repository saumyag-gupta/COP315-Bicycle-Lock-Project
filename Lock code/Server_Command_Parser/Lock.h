#ifndef _LOCKKK_
#define _LOCKKK_

#include "Arduino.h"
#include "Command_parser.h"
#include "Board_Comms.h"

#define MOTOR 1
#define LED1 2
#define LED2 3
#define BUZZER 4
#define LIM_SWITCH1 6
#define LIM_SWITCH2 7

class Lock{
  private:
  
  int STATUS;
  char *USER,*IMEI,*DEV_CODE;

  public:

  Lock()
  {
    STATUS=0;                      // status=0-> Locked   status=1->unlocked
    IMEI = "863158022988725";
    DEV_CODE = "SG";
    USER = "0,0,0,0,0";

    pinMode(MOTOR,OUTPUT);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(BUZZER,OUTPUT);
    
    pinMode(LIM_SWITCH1,INPUT);
    pinMode(LIM_SWITCH2,INPUT);

    STATUS = get_lock_status();
  }
  
  int unlock();

  int LED();

  int buzzer();

  int connect_server();

  int send_server(char command[]);

  char* receive_server();

  int get_lock_status();

  void RFID_setup();

  int RFID_read();

  void com_par(char command[]);

  char* package_creator();

  char* Local_time();
  
};

#endif

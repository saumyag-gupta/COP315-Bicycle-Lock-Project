#include "Lock.h"
#include "RFID.h"

  int Lock :: unlock()
  {
    digitalWrite(MOTOR,HIGH);
    delay(1000);
    digitalWrite(MOTOR,LOW);

  }

  int Lock :: LED()
  {
    
  }

  int Lock :: buzzer()
  {
    for(int i=0;i<3;i++)
    {
      digitalWrite(BUZZER,HIGH);
      delay(500);
      digitalWrite(BUZZER,LOW);
      delay(500);
    }
  }

  int Lock :: connect_server()
  {
    
  }

  int Lock :: send_server(char command[])
  {
    
  }

  char* Lock :: receive_server()
  {
    
  }

  int Lock :: get_lock_status()
  {
    //Limit switches logic
  }

  void Lock :: RFID_setup()
  {
    RFID_setup1();
  }

  int Lock :: RFID_read()
  {
    String s = loop1();
    if(s != "")
    {
      USER = (char*)s.c_str();
      return 0;
    }
    else
     return 1;
  }

  void Lock :: com_par(char command[])
  {
    Command_parser pars;

    switch(pars.parser(command))
    {
      case UNLOCK:
      unlock();
      break;
      case GPS_LOC:
      break;
      case BAT_STAT:
      break;
      case RESPONSE:
      break;
    }
    
  }

  char* Lock :: package_creator()
  {
    String str="";
    str+="CMDR";
    str+=DEV_CODE;
    str+=IMEI;
    str+="001497689816";  //write code for returning time here

    char* com = (char*)str.c_str();

    return com;
  }

  char* Lock :: Local_time()
  {
    
  }


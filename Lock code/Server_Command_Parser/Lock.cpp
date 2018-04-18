#include "Lock.h"
#include "RFID.h"

  int Lock :: unlock()
  {
  digitalWrite(MOTOR,HIGH);
  delay(3000);
  digitalWrite(MOTOR,LOW);
  delay(3000);

  }

  int Lock :: lock()
  {
    
  }

  
  int Lock :: get_lock_status()
  {
    //Limit switches logic
    Serial.print(digitalRead(LIM_SWITCH1));
    Serial.print(" ");
    Serial.println(digitalRead(LIM_SWITCH2));
    return 0;
  }

  int Lock :: LED()
  {
    
  }

  int Lock :: buzzer()
  {
    for(int i=0;i<3;i++)
    {
      digitalWrite(BUZZER,HIGH);
      delay(100);
      digitalWrite(BUZZER,LOW);
      delay(100);
    }
  }

  int Lock :: connect_server()
  {
    if(comm1.setup_(server,path))
    {
      Serial.println("Connected to Server");
      return 1;
    }
    else
    {
      Serial.println("Not Connected to Server...Retrying...");
      return 0;
    }
  }

  int Lock :: send_server(char command[])
  {
    return comm1.write_(command);
  }

  char* Lock :: read_server()
  {
    return comm1.read_();
  }

  void Lock :: RFID_setup()
  {
    RFID_setup1();
  }

  int Lock :: RFID_read()
  {
    String s = loop1();
    if(s != "" )
    {
      USER = (char*)s.c_str();
      Serial.println(USER);
      delay(1000);
      return 1;
    }
    else
     return 0;
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
    str+="CMDR,";
    str+=DEV_CODE;str+=",";
    str+=IMEI;str+=",";
    str+="001497689816";  //write code for returning time here
    str+=",";
    char* com = (char*)str.c_str();

    return com;
  }

  char* Lock :: Local_time()
  {
    
  }


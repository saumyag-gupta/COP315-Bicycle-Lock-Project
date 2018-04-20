#include "Lock.h"
#include "RFID.h"

  int Lock :: unlock()
  {
  digitalWrite(MOTOR,HIGH);
  delay(3000);
  digitalWrite(MOTOR,LOW);
  delay(3000);
  Serial.println("Unlocked");
  STATUS=0;   //Unlocked
  
  String command = package_creator();             // Lock-> Server  UNLOCK STATUS COMMAND

  command += "L0,";
  command += STATUS;command += ",";
  command += USER;command += ",";
  command += TIME;command += ",";
  command += "#<LF>";
  
  return send_server(command);

  }

  int Lock :: lock()
  {
    STATUS = 1;  // Locked
  }

  
  int Lock :: get_lock_status()
  {
    //Limit switches logic
    int switch1=digitalRead(LIM_SWITCH1));
    int switch2=digitalRead(LIM_SWITCH2));
    return 1;    //Locked
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

  int Lock :: send_server(String command)
  {
    return comm1.write_(command);
  }

  String Lock :: read_server()
  {
    return comm1.read_();
  }

  void Lock :: RFID_setup()
  {
    Serial.println("RFID setup");
    RFID_setup1();
  }

  int Lock :: RFID_read()
  {
    //Serial.println("RFID read");
    String s = loop1();
    if( s != "" )
    {
      USER = (char*)s.c_str();
      Serial.println(USER);
      delay(1000);
      
      String command = package_creator();             // Lock-> Server  RFID DETECTED COMMAND

      command += "R0,";
      command += USER;command += ",";
      command += TIME;command += ",";
      command += "#<LF>";
      
      return send_server(command);
    }
    else
     return 0;
  }

  void Lock :: com_par(String command)
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

  String Lock :: package_creator()
  {
    String str="*C";
    str+="MDR,";
    str+=DEV_CODE;str+=",";
    str+=IMEI;str+=",";
    str+=TIME;  //write code for returning time here
    str+=",";

    return str;
  }

  char* Lock :: Local_time()
  {
    
  }


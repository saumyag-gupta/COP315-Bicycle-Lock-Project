#include "Lock.h"
#include "RFID.h"

  int Lock :: unlock()
  {
  digitalWrite(MOTOR,HIGH);
  delay(1200);
  digitalWrite(MOTOR,LOW);
  Serial.println("Unlocked");
  STATUS=0;   //Unlocked
  RIDE_STATUS=1;   //Ride Started
  
  String command = package_creator();             // Lock-> Server  UNLOCK STATUS COMMAND

  command += "L0,";
  command += STATUS;command += ",";
  command += USER;command += ",";
  command += TIME;
  
  String rec= send_server(command);
  com_par(rec);
  return 1;

  }

  int Lock :: lock()
  {
  STATUS = 1;  // Locked
  USER = "0.0.0.0.0";

   //Halt Code
  String command = package_creator();             // Lock-> Server  UNLOCK STATUS COMMAND

  command += "L1,";
  command += USER;command += ",";
  command += TIME;
  
  String rec= send_server(command);
  com_par(rec);
  return 1;
  }

  
  int Lock :: get_lock_status()
  {
    //Limit switches logic
    int switch1=digitalRead(LIM_SWITCH1);
    int switch2=digitalRead(LIM_SWITCH2);
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

  String Lock :: send_server(String command)
  {
    return comm1.communicate(command);
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
      command += "0,";
      command += USER;command += ",";
      command += TIME;
      
      String rec= send_server(command);
      Serial.println(rec);
      Serial.println("Going into parser");
      com_par(rec);
      return 1;
    }
    else
     return 0;
  }

  void Lock :: com_par(String command)
  {
    Command_parser pars;
    Serial.println(command);
    Serial.println("Parsing command");

    int check=pars.parser(command);
    
    switch(check)
    {
      case UNLOCK:
      Serial.println("Going into Unlock");
      unlock();
      break;
      case GPS_LOC:
      break;
      case BAT_STAT:
      break;
      case RESPONSE:
      Serial.println("Server Response has been recorded");
      break;
    }
    
  }

  String Lock :: package_creator()
  {
    String str="C";
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


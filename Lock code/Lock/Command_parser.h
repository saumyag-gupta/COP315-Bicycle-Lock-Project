#ifndef _PARSERRR_
#define _PARSERRR_

#define UNLOCK 1
#define GPS_LOC 2
#define BAT_STAT 3
#define RESPONSE 9

class Command_parser{  
  
  // Error code: function returning 0:ERROR, function returning anything else:successful
   
  public:
  /*void S8();   // Ringing for finding a bike Command
  //void G0();   //  Query Firmware Version Command
  //void W0();   // Alarmimg Command mlo 
  //void I0();   // Obtain SIM card ICCID Code Command*/

int parser(char command[])
{
  char *IMEI,*Dev_code,*Time,*CMD,*valu1,*valu2,*valu3;
  int i=0;
  char *header="";
  while(command[i]!=',')
  {
    header+=command[i];
    i++;
  }
  if(header!="CMDS")
   return 1;

  i++;
  while(command[i]!=',')
  {
    Dev_code+=command[i];
    i++;
  }
  
  i++;
  while(command[i]!=',')
  {
    IMEI+=command[i];
    i++;
  }

  i++;
  while(command[i]!=',')
  {
    Time+=command[i];
    i++;
  }

  i++;
  while(command[i]!=',')
  {
    CMD+=command[i];
    i++;
  }
  
  i++;
  if(command[i]=='#')
   goto END;
  while(command[i]!=',')
  {
    valu1+=command[i];
    i++;
  }

  i++;
  if(command[i]=='#')
   goto END;
  while(command[i]!=',')
  {
    valu2+=command[i];
    i++;
  }

  i++;
  if(command[i]=='#')
   goto END;
  while(command[i]!=',')
  {
    valu3+=command[i];
    i++;
  }
  
  END:

    if ( CMD == "L0" )
     return L0_in();
    if ( CMD == "Re")
     return Re_in();
    if ( CMD == "D0")
     return D0_in();
    if ( CMD == "S5")
     return S5_in();
  
}

int L0_in()
{
  return UNLOCK;
  //if(lock.unlock());
}

int D0_in()
{
  return GPS_LOC;
}

int S5_in()
{
  return BAT_STAT;
}

int Re_in()
{
  return RESPONSE;
}


};

#endif

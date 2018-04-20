#include "Board_Comms.h"
#include <stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LGPS.h>

LGPRSClient client;
gpsSentenceInfoStruct info;

int port = 80; // HTTP

int Board_Comms::setup_(char server[],char path[])
{
  while (!LGPRS.attachGPRS("wholesale", NULL, NULL))
  {
    delay(500);
  }
  if (client.connect(server, port))
  {
    return 1;
  }
  else
  {
    // if you didn't get a connection to the server:
    return 0;
  }
}

char* Board_Comms::read_()
{
  int flag=0;
  String com = "";
  while (client.available())
  {
    char c = client.read();
    if( c == 'C')
     flag=1;
    else if( c == 'M' && flag == 1)
     flag=2;
    else if( c == 'D' && flag == 2)
     flag=3;
    else if( c == 'S' && flag == 3)
     flag=4;
    else if( c == '#')
     {
      flag=0;
      com+=c;
      break;
     }
    else if( flag != 4 )
     flag=0;
     
    if(flag >0)
     com+=c;
    else
     com = "";
    
  }

  //client.stop();
  char* command = (char*)com.c_str();
  return command;
}

int Board_Comms::write_(char command[])
{
  
  if (client.connect(server, port))
  {
    // Make a HTTP request:
    String str="GET /server.php?";
    str += "command=";
    str += command;
    client.print(str);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    return 1;
  }
  else
  {
    // if you didn't get a connection to the server:
    return 0;
  }
}

const char *Board_Comms::nextToken(const char* src, char* buf)
{
   int i = 0;
   while(src[i] != 0 && src[i] != ',')
   i++;
   if(buf)
   {
   strncpy(buf, src, i);
   buf[i] = 0;
   }
   if(src[i])
     i++;
   return src+i;
}

void Board_Comms::update (const char* str, char* lati, char* longi)
{
  char latitude[20];
  char longitude[20];
  char buf[20];
  const char* p = str;
  p = nextToken(p, 0); // GGA
  p = nextToken(p, 0); // Time
  p = nextToken(p, latitude); // Latitude
  p = nextToken(p, 0); // N
  p = nextToken(p, longitude); // Longitude
  lati=latitude;
  longi=longitude;

  if(buf[0] == '1') {
    Serial.print("GPS is fixed:");
    Serial.print(atoi(buf));
    Serial.println(" satellite(s) found!");
    Serial.print("Latitude:");
    Serial.println(latitude);
    Serial.print("Longitude:");
    Serial.println(longitude);
  }
  else {
    Serial.println("GPS is not fixed yet.");
  }
}

void Board_Comms::read_gps (char* lati, char* longi)
{
  LGPS.powerOn();
  delay(5000);
  LGPS.getData(&info);
  Board_Comms::update((char*)info.GPGGA);
  delay(1000);
  LGPS.powerOff();
  delay(100);
}


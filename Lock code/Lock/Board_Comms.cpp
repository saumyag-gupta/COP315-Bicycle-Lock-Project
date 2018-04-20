#include "Board_Comms.h"
#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

LGPRSClient client;

int port = 80; // HTTP

String Board_Comms :: communicate(String command)
{
  Serial.println(command);

  server = "linkitonetest.000webhostapp.com";
  while (!LGPRS.attachGPRS("wholesale", NULL, NULL))
  {
    delay(500);
  }
  // if you get a connection, report back via serial:
  Serial.print("Connect to ");
  Serial.println(server);
  if (client.connect(server, port))
  {
    Serial.println("connected");
    // Make a HTTP request:
    //client.print("GET ");
    String str = "GET /server.php?";
    str+="command=";
    //str+="CMDR,01,Lock1,000,D0,0,255.32,2545.2";
    str+=command;

    client.print(str);
    //client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    
    Serial.println(str);
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  String com="";command="";
  int flag=0;
  while(1)
  {
      if (client.available())
  {
    char c = client.read();
    //Serial.print(c);
           
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
      command=com;
     }
    else if( flag != 4 )
     flag=0;
     
    if(flag >0)
     com+=c;
    else
     com = "";
     //com+=c;
  }

  // if the server's disconnected, stop the client:
  if (!client.available() && !client.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    break;

  }
  }
  Serial.println(command);
  return command;
 
}


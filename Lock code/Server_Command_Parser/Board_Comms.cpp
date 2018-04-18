#include "Board_Comms.h"
#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

LGPRSClient client;

int port = 80; // HTTP

char command[100];

int Board_Comms :: setup_(char server[],char path[])
{
  while (!LGPRS.attachGPRS("wholesale", NULL, NULL))
  {
    delay(500);
  }
  if (client.connect(server, port))
  {
    return 0;
  }
  else
  {
    // if you didn't get a connection to the server:
    return 1;
  }
}

char* Board_Comms :: read_()
{
  int i=0;
  while (client.available())
  {
    char c = client.read();
    command[i]=c;
    i++;
  }

  //client.stop();

  return command;
}

int Board_Comms :: write_(char command[])
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
    return 0;
  }
  else
  {
    // if you didn't get a connection to the server:
    return 1;
  }
}


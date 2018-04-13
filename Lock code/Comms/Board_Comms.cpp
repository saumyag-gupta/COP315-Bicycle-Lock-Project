#include "Board_Comms.h"
#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

typedef unsigned char  BYTE; // 1byte
typedef unsigned short  NUM; // 2bytes

LGPRSClient client;

int port = 80; // HTTP

char command[100];

NUM setup_(char server[],char path[])
{
  while (!LGPRS.attachGPRS("wholesale", NULL, NULL))
  {
    delay(500);
  }
  if (client.connect(server, port))
  {
    // Make a HTTP request:
    client.print("GET ");
    client.print(path);
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

char *read_()
{
  NUM i=0;
  while (client.available())
  {
    char c = client.read();
    command[i]=c;
    i++;
  }

  client.stop();

  return command;
}


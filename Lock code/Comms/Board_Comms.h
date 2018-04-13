#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

typedef unsigned char  BYTE; // 1byte
typedef unsigned short  NUM; // 2bytes

class Board_Comms{
  
   private:
   char *server;
   char *path;

   int port = 80; // HTTP

   public:

   Board_Comms(char serv[],char pat[])
   {
    server=serv;
    path=pat;
    setup_(server,path);
   }

   NUM setup_(char serv[],char pat[]);

   char *read_();

   char *write_();

};


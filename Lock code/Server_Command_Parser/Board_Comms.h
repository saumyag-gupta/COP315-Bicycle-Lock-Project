#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

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

   int setup_(char serv[],char pat[]);

   char *read_();

   int write_(char command[]);

};


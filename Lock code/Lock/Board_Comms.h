#include<stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

class Board_Comms{
  
   private:
   char *server;
   char *path;
   int CONNECTED;

   int port = 80; // HTTP

   public:

   Board_Comms()
   {
   }

   int setup_(char serv[],char pat[]);

   String read_();

   int write_(String command);

};


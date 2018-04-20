#include <stdlib.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LGPS.h>

class Board_Comms{
  
   private:
   char *server;
   char *path;

   int port = 80; // HTTP

   public:

   Board_Comms()
   {

   }

   int setup_(char serv[], char pat[]);

   char *read_();

   int write_(char command[]);

   const char *nextToken(const char* src, char* buf);

   void update(const char* str, char* lati, char* longi);

   void read_gps(char* lati, char* longi);

};


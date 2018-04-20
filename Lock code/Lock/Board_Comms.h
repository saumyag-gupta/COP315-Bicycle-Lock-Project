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

   String communicate(String command);

   const char *nextToken(const char* src, char* buf);

   void update(const char* str, char* lati, char* longi);

   void read_gps(char* lati, char* longi);

};


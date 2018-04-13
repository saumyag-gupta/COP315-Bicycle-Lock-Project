#include <stdlib.h>

typedef unsigned char  BYTE; // 1byte
typedef unsigned short  NUM; // 2bytes

public class Server_Command_Parser{

  private:
  BYTE cmd[100];

  public:

  Server_Command_Parser()
  {
    cmd=NULL;
  }

  BYTE *Convert(string command);   // Convert from PlainText to Byte Array

  void L0();   // Unlock Command

  void L1();    // Lock Command

  void D0()   // Positioning Command

  void S5();  // Obtain Lock Status Command

  void S8();   // Ringing for finding a bike Command

  void G0();   //  Query Firmware Version Command

  void W0();   // Alarmimg Command mlo 

  void I0();   // Obtain SIM card ICCID Code Command
  
}


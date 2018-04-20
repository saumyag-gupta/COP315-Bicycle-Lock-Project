#include "Lock.h"

Lock test;
int i=0;
void setup() {  
  
  Serial.begin(9600);
  test.INIT();
  test.RFID_setup();
  //digitalWrite(MOTOR,HIGH);
}

void loop() {
   
   test.RFID_read();
   test.read_server();
   /*if(command!="")
   {
    test.com_par(command);
   }*/
   //test.unlock();
   // test.buzzer();
   
   //test.get_lock_status();

}

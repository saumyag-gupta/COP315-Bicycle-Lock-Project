#include "Lock.h"

Lock test;
int i=0;
void setup() {  
  test.INIT();
  Serial.begin(9600);
  //test.RFID_setup();
  digitalWrite(MOTOR,HIGH);
}

void loop() {
   
   //test.RFID_read();
   //test.unlock();
   // test.buzzer();
   
   test.get_lock_status();

}

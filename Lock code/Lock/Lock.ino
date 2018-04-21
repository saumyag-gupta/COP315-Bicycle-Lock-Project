#include "Lock.h"

Lock test;

void setup() {  
  
  Serial.begin(9600);
  test.INIT();
  //test.RFID_setup();
}

void loop() {
   
   //test.GPS_periodic();
   //test.RFID_read();
   //test.lock();
   //test.LED();
}

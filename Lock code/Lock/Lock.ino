#include "Lock.h"

Lock test;

void setup() {  
  
  Serial.begin(9600);
  test.INIT();
  test.RFID_setup();
  //digitalWrite(MOTOR,HIGH);
}

void loop() {
   
   test.RFID_read();

}

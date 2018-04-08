#include <LGSM.h>


void setup() {
Serial.begin(9600);

while(!LSMS.ready())
delay(1000);

Serial.println("SIM ready for work!");

LSMS.beginSMS("9717684830");
LSMS.print("Bhai Makker Bhai");
if(LSMS.endSMS())
{
Serial.println("SMS is sent");
}
else
{
Serial.println("SMS is not sent");
}
}

void loop() {
  // put your main code here, to run repeatedly:

}

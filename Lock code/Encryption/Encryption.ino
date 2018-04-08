#include "Encryption.h"

typedef unsigned char  BYTE; 
typedef unsigned short  NUM;

void setup() {
Serial.begin(9600);
  
  BYTE data[]={0xFE,0x88,0x66,0x21,0x04,0x00,0x00,0x00,0x01};
  NUM len=9;
  
  BYTE *enc = Encrypt(data,len);
  
  NUM lene=11;
  for( NUM i=0 ; i < lene ; i++)
      Serial.println(enc[i],HEX);
            
  BYTE *dec = Decrypt(enc,lene);
  NUM lend=9;
  for( NUM i=0 ; i < lend ; i++)
     Serial.println(dec[i],HEX);
}

void loop() {
  // put your main code here, to run repeatedly:

}

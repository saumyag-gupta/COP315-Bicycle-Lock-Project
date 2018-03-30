// LinkIt One Bluetooth GATT Demo

#include "GATTService1.h"
#include "GATTService2.h"
#include <LGATTUUID.h>

GATTService1 serv1;
GATTService2 serv2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );

  // splash
  pinMode( 13, OUTPUT );
  for( int i = 0; i < 20; i++ ) {
    digitalWrite( 13, HIGH ); delay( 500 );
    digitalWrite( 13,  LOW ); delay( 500 );
  }
  // end of splash
  
  // Start GATT Server
  Serial.printf( "Starting GATT Server ......\n" );
  if ( LGATTServer.begin(2, &serv1, &serv2) ) {
    Serial.println( "GATT Server Started" );
  } else {
    Serial.println( "Error Starting GATT Server" );
  }
}

void loop() {
  
  LGATTServer.handleEvents();
  
}


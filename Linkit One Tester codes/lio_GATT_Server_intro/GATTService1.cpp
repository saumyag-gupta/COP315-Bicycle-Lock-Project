// GATT Service 1
#include "vmbtgatt.h"
#include "GATTService1.h"

// service 1 declaration
// Has four characteristics
static LGATTServiceInfo g_serv1_decl[] =
{
  { TYPE_SERVICE, "E30A39F4-73F5-4BC4-A12F-17D1AD07A961", TRUE, 0, 0, 0 },
    { TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDE0", FALSE, VM_GATT_CHAR_PROP_READ, VM_GATT_PERM_READ, 0 },
    { TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDE1", FALSE, VM_GATT_CHAR_PROP_NOTIFY|VM_GATT_CHAR_PROP_READ, VM_GATT_PERM_READ, 0 },
    { TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDE2", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0 },
    { TYPE_CHARACTERISTIC, "01234567-89AB-CDEF-0123-456789ABCDE3", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0 },
  { TYPE_END, 0, 0, 0, 0, 0 }
};

// prepare the data for profile
LGATTServiceInfo *GATTService1::onLoadService(int32_t index) {
  Serial.printf( "[GATTService1]  onLoadService()\n" );
  Serial.printf( "    index : %08X\n", index );
  
  return g_serv1_decl;
}

// characteristic added
boolean GATTService1::onCharacteristicAdded(LGATTAttributeData &data) {
    Serial.printf( "[GATTService1]  onCharacteristicAdded()\n" );
    Serial.printf( "    handle : %04X\n", data.handle );
    Serial.printf( "    UUID   : %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
                        data.uuid[0xF], data.uuid[0xE], data.uuid[0xD], data.uuid[0xC],
                        data.uuid[0xB], data.uuid[0xA], data.uuid[0x9], data.uuid[0x8],
                        data.uuid[0x7], data.uuid[0x6], data.uuid[0x5], data.uuid[0x4],
                        data.uuid[0x3], data.uuid[0x2], data.uuid[0x1], data.uuid[0x0] );
    Serial.printf( "    flag   : %d\n", data.failed );
    if (!data.failed) {
        // set handles here
    }
    return true;
}

// connected or disconnected
boolean GATTService1::onConnection( const LGATTAddress &addr, boolean connected ) {
  Serial.printf( "[GATTService1] Client %X:%X:%X:%X:%X:%x ",
                 addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0] );
  if( connected ) {
    Serial.println( "[   connected]" );
  } else {
    Serial.println( "[disconnected]" );
  }

  // set connection flag
  _connected = connected;

  return true;
}
// read action comming from master
boolean GATTService1::onRead( LGATTReadRequest &data ) {
    Serial.println( "[GATTService1] onRead()" );
    if( _connected ) {
      Serial.println( "    Status         : Connected" );
      Serial.printf(  "    Transaction ID : 0x%04X\n", data.trans_id );
      Serial.printf(  "    BT Address     : %X:%X:%X:%X:%X:%X\n",
                                data.bd.addr[5], data.bd.addr[4], data.bd.addr[3], data.bd.addr[2], data.bd.addr[1], data.bd.addr[0] );
      Serial.printf(  "    Attrib Handle  : 0x%04X\n", data.attr_handle );
      Serial.printf(  "    Offset         : 0x%04X\n", data.offset );
      
      // Set Data
      LGATTAttributeValue value = { 0 };
      const char *str = "onRead response";
      memcpy( value.value, str, strlen(str) );
      value.len = strlen( str );
      
      // Send Response
      data.ackOK( value );
    } else {
      // no connection
      Serial.println( "    Status         : Disconnected" );
    }
    return true;
}

// write action comming from master
boolean GATTService1::onWrite( LGATTWriteRequest &data ) {
  Serial.println( "[GATTService1]  onWrite()" );
  
  if( _connected ) {
    Serial.printf( "    Status         : Connected\n" );
    Serial.printf( "    Transaction ID : 0x%04X\n", data.trans_id );
    Serial.printf( "    BT Address     : %02X:%02X:%02X:02X:%02X:%02X\n",
                        data.bd.addr[5], data.bd.addr[4], data.bd.addr[3], data.bd.addr[2], data.bd.addr[1], data.bd.addr[5] );
    Serial.printf( "    Data Length    : %2d\n", data.value.len );
    Serial.printf( "    Data (Hex)     : " );
    for( uint16_t i = 0; i < data.value.len; i++ )
      Serial.printf( "%02X ", data.value.value[i] );
    Serial.println();
    Serial.printf( "    Data(ASCII)    : " );
    for( uint16_t i = 0; i < data.value.len; i++ )
      Serial.printf( "%c", data.value.value[i] );
    Serial.println();
    Serial.printf( "    Offset         : 0x%02X\n", data.offset );
    Serial.printf( "    Need Response  : %s\n", (data.need_rsp)?" True":"False" );
    if( data.need_rsp ) {
      data.ackOK();
    }
  }
  return true;
}





// The headers for all the modules
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LBT.h>
#include <LBTServer.h>
#include <LGPS.h>

#define SITE_URL "www.iitd.ac.in"
#define WIFI_AP "********"           //Replace afterward
#define WIFI_PWD "*********"         //Replace afterward

LGPRSClient client;   //GPRS client
LWiFiClient c;        //Wifi Client


void setup() {
  Serial.begin(9600);
  
 // GPRS Testing
 GPRS_test();

 // WiFi testing
 WiFi_test();

 // Bluetooth testing
 Blue_test();

 // GPS testing
 GPS_test();

}

void GPS_test()
{
  LGPS.powerOn();     // Make code to get location data and test
}

void Blue_test()
{
  if(!LBTServer.begin((uint8_t*)"COP315_Server"))
 {
 Serial.println("Fail to start Bluetooth.");
 return;
 }
 else
 {
 Serial.println("BT server is started.");
 }
}

void WiFi_test()
{
  LWiFi.begin();

 Serial.println();
 Serial.print("Connecting to Wifi...");
 if(LWiFi.connectWEP(WIFI_AP, WIFI_PWD) < 0)
 {
 Serial.println("FAILED TO CONNECT!");
 return;
 }
 Serial.println("Connected successfully to wifi");
 
 Serial.print("Connecting to : " SITE_URL "...");
 if(!c.connect(SITE_URL, 80))
 {
 Serial.println("FAIL to connect to URL!");
 return;
 }
 Serial.println("Successfully connected to URL!");
  
}

void GPRS_test()
{
 Serial.println("Attempting GPRS connection");
 while(!LGPRS.attachGPRS())
 {
 Serial.println("wait for SIM card ready");
 delay(1000);
 }
 Serial.println("GPRS module initialized");
 
 Serial.print("Connecting to : " SITE_URL "...");
 if(!client.connect(SITE_URL, 80))
 {
 Serial.println("FAIL to connect to URL!");
 return;
 }
 else
 {
  Serial.println("Successfully connected to URL!");
 }
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 * WiFi file containing functions for managing WiFi in NAPaC project
 * SmartConfig setup from Wifi SmartConfig example
 * 
 */

#include "WiFi.h"
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>


//char * server_host;
//WiFiMulti wifiMulti;

void setup_wifi_smartconfig(){
  WiFi.beginSmartConfig();
  
  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("SmartConfig received.");

  //Wait for WiFi to connect to AP
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
      Serial.println("WiFi Connected.");
    //* server_host = WiFi.localIP(); // constant defined by Yann
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
 
void setup_wifi() {
//  //Init WiFi as Station, start SmartConfig
//  WiFi.mode(WIFI_AP_STA);
//
//  wifiMulti.addAP("NAPaC_WiFi", "NAPaC2018");
//  //From WiFiMulti example
//  Serial.println("Connecting Wifi...");
//  while(wifiMulti.run() != WL_CONNECTED) {
//        Serial.print(".");
//        delay(500);
//    }
//  Serial.println("");
//  Serial.println("WiFi connected from WiFiMulti");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  delay(500);
}



 

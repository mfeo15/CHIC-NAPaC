/*
 * WiFi file containing functions for managing WiFi in NAPaC project
 * SmartConfig setup from Wifi SmartConfig example
 * 
 */

#include "WiFi.h"

void setup_wifi_smartconfig(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    blink_LED(0,green);
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
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    set_LED(0,green);
    delay(1000);
    set_LED(0,off);
}
 
void setup_wifi() {
  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);

  WiFiMulti.addAP("NAPaC_WiFi", "NAPaC2018");
  Serial.println("Connecting Wifi...");
  while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
  Serial.println("");
  Serial.println("WiFi connected from WiFiMulti");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}



 

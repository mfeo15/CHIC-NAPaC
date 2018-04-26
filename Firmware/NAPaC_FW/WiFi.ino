/*
 * WiFi file containing functions for managing WiFi in NAPaC project
 * 
 */

#include "WiFi.h"

/*
 * SmartConfig setup from Wifi SmartConfig example
 */

char * server_host;
 
void setup_wifi() {
  Serial.begin(115200);

  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
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
    * server_host = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
 }



 

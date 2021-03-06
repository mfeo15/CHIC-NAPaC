/*
   WiFi file containing functions for managing WiFi in NAPaC project
   SmartConfig setup from Wifi SmartConfig example

*/

#include "WiFi.h"

void setup_wifi_smartconfig() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    //delay(500);
    blink_presence_LEDs(green);
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
  set_presence_LEDs(green);
  delay(1000);
  set_presence_LEDs(off);
}

void setup_wifi() {
  WiFi.begin("NAPAC", "1234abcd");   //WiFi connection

  Serial.print("Connecting Wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    blink_presence_LEDs(green);
  }

  Serial.println("\n");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  set_presence_LEDs(green);
  delay(1000);
  set_presence_LEDs(off);
}




/*
 * WiFi file containing functions for managing WiFi in NAPaC project
 * SmartConfig setup from Wifi SmartConfig example
 * 
 */

#include "WiFi.h"
#include <EEPROM.h>

//char * server_host;

#define EEPROM_SIZE 64 // I DON'T KNOW WHY

uint8_t num_smartconfig = 0;
int adress = 0;
int address_SSID = 0; 
int address_pwd = 0; 

void setup_EEPROM() {
  uint8_t EEPROM_size = EEPROM.length(); // DOESN'T WORK
  //Serial.println("EEPROM_size =");
  //Serial.println(EEPROM_size);
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
}
 
void setup_wifi() { //NOT TESTED
  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);

  num_smartconfig = EEPROM.readString(address);
  
  if (num_smartconfig = 0){
    Serial.println("No saved Smartconfig - initialising Smartconfig");
    smartconfig(); //saves smartconfig in EEPROM
  }

  for (uint8_t i=0; i<num_smartconfig;i++){
    address_SSID  = address + sizeof(num_smartconfig);
    String SSID_s = EEPROM.readString(address_SSID);
    address_pwd   = address_SSID + sizeof(SSID_s);
    String PWD    = EEPROM.readString(address_pwd);
    Serial.println("WiFi config found:");
    Serial.println(SSID_s);
    Serial.println(PWD);
    wifiMulti.addAP(SSID_s, PWD);
  }
  //From WiFiMulti example
  Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}


void smartconfig(){
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

    Serial.println("\nTesting EEPROM Library\n");

    //save SSID and PWD in strings
    String SSID_s = WiFi.SSID();
    //SSID_s.concat('\0');
    Serial.println("SSID:");
    Serial.println(SSID_s);

    String PWD = WiFi.psk();
    Serial.println("PWD:");
    Serial.println(PWD);


    //save wifi config in eeprom
    Serial.println("read&write from eeprom");
    EEPROM.writeString(address_SSID, SSID_s);
    Serial.println("SSID written in EEPROM");
    Serial.println(EEPROM.readString(address_SSID));
    address_pwd = address_SSID + sizeof(SSID_s);
    EEPROM.writeString(address_pwd, PWD);
    Serial.println(EEPROM.readString(address_pwd));
    // WORKS BUT HAS AN EXTRA CHARACTER - CHECK END OF LINE?
  
}

void setup(){
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor
    setup_EEPROM();
    setup_wifi();
    //smartconfig();
    
}

void loop()
{    
    
}



 

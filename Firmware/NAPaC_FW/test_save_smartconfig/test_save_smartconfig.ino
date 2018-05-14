/*
 * WiFi file containing functions for managing WiFi in NAPaC project
 * SmartConfig setup from Wifi SmartConfig example
 * 
 */

#include "WiFi.h"
#include <EEPROM.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

//char * server_host;

#define EEPROM_SIZE 64 // I DON'T KNOW WHY

uint8_t num_smartconfig = -1;
int address = 0;
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
 
void setup_wifi() {
  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);

  //To reinitialise smartconfig memory, run setup_eeprom.ino
  num_smartconfig =  EEPROM.readByte(address); 
  Serial.println("Smartconfigs found:");
  Serial.println(num_smartconfig);
  
  if (num_smartconfig == 0){
    Serial.println("No saved Smartconfig - initialising Smartconfig");
    smartconfig(); //saves smartconfig in EEPROM
  }

  for (uint8_t i=0; i<num_smartconfig;i++){
    address_SSID  = address + sizeof(num_smartconfig);
    const char *SSID_s = EEPROM.readString(address_SSID).c_str();
    address_pwd   = address_SSID + sizeof(SSID_s);
    const char* PWD    = EEPROM.readString(address_pwd).c_str();
    Serial.println("WiFi config found:");
    Serial.println(SSID_s);
    Serial.println(PWD);
    wifiMulti.addAP(SSID_s, PWD);
  }
  //From WiFiMulti example
  Serial.println("Connecting Wifi...");
  while(wifiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
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
      Serial.println("\n WiFi Connected.");
    //* server_host = WiFi.localIP(); // constant defined by Yann
//    Serial.print("IP Address: ");
//    Serial.println(WiFi.localIP());

    //save SSID and PWD in strings
    String SSID_s = WiFi.SSID();
    //SSID_s.concat('\0');
    Serial.println("SSID:");
    Serial.println(SSID_s);

    String PWD = WiFi.psk();
//    Serial.println("PWD:");
//    Serial.println(PWD);


    //save wifi config in eeprom
    Serial.println("\nRead&write from eeprom");
    address_SSID = address + sizeof(num_smartconfig);
    EEPROM.writeString(address_SSID, SSID_s);
    address_pwd = address_SSID + sizeof(SSID_s);
    EEPROM.writeString(address_pwd, PWD);
    // WORKS BUT HAS AN EXTRA CHARACTER - CHECK END OF LINE?

    Serial.println("SSID & PWD written in EEPROM:");
    Serial.println(EEPROM.readString(address_SSID));
    Serial.println(EEPROM.readString(address_pwd));

    num_smartconfig++;
    EEPROM.writeByte(address, num_smartconfig);
    EEPROM.commit();
  
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



 

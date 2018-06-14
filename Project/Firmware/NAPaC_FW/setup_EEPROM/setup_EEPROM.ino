/*
 * Code to run to setup memory
 */


#include <EEPROM.h>

uint8_t num_smartconfig = 0;
int address = 0;
#define EEPROM_SIZE 64 // I DON'T KNOW WHY


void setup() {  
  Serial.begin(115200);
  delay(1000);
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  EEPROM.writeByte(address, num_smartconfig);
  for (uint8_t i=0; i<EEPROM_SIZE; i++) //IS THIS A GOOD IDEA?!
  {
    EEPROM.writeByte(address+i, 0);
  }
  // Erase/set all memory???
  EEPROM.commit();
  Serial.println("EEPROM memory ready for NAPaC_FW install");  
}

void loop() {
  // put your main code here, to run repeatedly:

}

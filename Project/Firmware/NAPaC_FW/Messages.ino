/*
   Messages file containing messages sent and received by server for NAPaC project
*/

/*
   setup_messages(); sets up message headers - not yet in use
   first_message(); The toy presents itself to the server in initiate pairing
   hello(); Prints NAPaC FW in serial

   accept_game_message(); Sends start of game session to parent
   LED_on_message(LEDid); For play session with parent, tells the parent the child has turned a LED on
   LED_off_message(LEDid); For play session with parent, tells the parent the child has turned a LED off

*/

#include <string.h>

void accept_game_message() {
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& encoder = JSONbuffer.createObject();

  encoder["id"] = "2002";
  encoder["source"] = "T314";
  encoder["destination"] = "P123";

  char JSONmessage[300];
  encoder.prettyPrintTo(JSONmessage, sizeof(JSONmessage));

  pushMessage(JSONmessage);
  
  Serial.println("Message sent: Child accepted game session!");
  Serial.println(JSONmessage);
}

//Message to tell parent a kid turned on a LED - no error checking
void LED_on_message(uint8_t LEDid) {

  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& encoder = JSONbuffer.createObject();

  char led_str[3];
  get_led_string(led_str, LEDid);

  encoder["id"] = "2003";
  encoder["source"] = "T314";
  encoder["destination"] = "P123";
  encoder["zone"] = led_str;
  encoder["status"] = "ON";

  char JSONmessage[300];
  encoder.prettyPrintTo(JSONmessage, sizeof(JSONmessage));

  pushMessage(JSONmessage);

  Serial.println(JSONmessage);
}

//Message to tell parent a kid turned off a LED - no error checking
void LED_off_message(uint8_t LEDid) {

  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& encoder = JSONbuffer.createObject();

  char led_str[3];
  get_led_string(led_str, LEDid);

  encoder["id"] = "2003";
  encoder["source"] = "T314";
  encoder["destination"] = "P123";
  encoder["zone"] = led_str;
  encoder["status"] = "OFF";

  char JSONmessage[300];
  encoder.prettyPrintTo(JSONmessage, sizeof(JSONmessage));

  pushMessage(JSONmessage);

  Serial.println(JSONmessage);
}

void get_led_string(char* buffer_str, uint8_t LEDid) {

  char led_str = (char)LEDid + 49;
  sprintf(buffer_str, "%c", led_str);
}





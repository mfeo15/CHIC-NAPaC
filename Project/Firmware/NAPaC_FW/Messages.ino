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
  /*
  char message1[31] = {0};
  char led_id = (char)LEDid + offset;
  //header+2003+RS+PC+US+(n)+EOT
  sprintf(message1, "%c0020%cU123%cP314%c2003%c1%c%c%c", STX[0], RS[0], RS[0], RS[0], RS[0], US[0], led_id, EOT[0]);
  send_message(message1);
  Serial.print("Message sent: Child turned on LED");
  Serial.println(LEDid);
  */
  
}

//Message to tell parent a kid turned off a LED - no error checking
void LED_off_message(uint8_t LEDid) {
  /*
  char message1[31] = {0};
  char led_id = (char)LEDid + offset;
  //header+2004+RS+PC+US+(n)+EOT
  sprintf(message1, "%c0020%cU123%cP314%c2004%c1%c%c%c", STX[0], RS[0], RS[0], RS[0], RS[0], US[0], led_id, EOT[0]);
  send_message(message1);
  Serial.print("Message sent: Child turned off LED");
  Serial.println(LEDid);
  */
  
}





/*
 * Game file containing functions for managing game sessions on Toygether plush
 */

 /*
  * accept_game_request(); Blinks heart light to signal game session request from parent.
  *   Waits until the child presses the toy, sends an accept message to server.
  * parent_game(); loops on parent/child game session until parent breaks off connection
  *   reads & sends message to/from server for interactions
  */


//bool game_session_on = 0;
enum LED_mode { LED_off, on_kid, on_parent};
uint8_t zone_status[9] = {0};
uint8_t LEDid;


bool accept_game_request(){
  blink_LED(0,purple);
  Serial.println("Parent requested game session");
  int c = 0;

  while (1){
    blink_LED(0,purple);
    if (presence()){
      accept_game_message();
      blink_LED(0,yellow);
      return 1;
    }
  }
}

//void start_game_session(){ //not in use MS5
//  Serial.println("Beginning of game session!");
//  set_LED(0,red);
//  game_session_on =1;
//}
//
void end_game_session(){
  Serial.println("End of game session!");
  blink_LED(0, parent);
  set_LED(0,off);
  game_session_on = 0;
}

uint8_t read_LEDid(String message){
  int offset = 48; // = "1"
  int LEDid = (int) message.charAt(23) - offset; // CHAR AT 23 TO BE TESTED
  Serial.println(LEDid);
  return LEDid;
}

// not in use for MS5
bool LED_sequence_request(String message){
  uint8_t game_led = 10;  //MS4
  int offset = 48; // = "1"
  int nb_LED = (int) message.charAt(21) - offset;
  Serial.println(nb_LED);
  
  if (nb_LED > 1){
    Serial.println("Stupid you, we only have one LED working!");
    return 0;
  }

  set_LED(game_led, yellow);
  Serial.println("game LED on");
  
  while (1){
    if (presence()){
      for (uint8_t i = 1; i <= nb_LED; i++){
      //set_LED(i, off);
      Serial.println("LED off");
      }
      set_LED(game_led,off);//MS4
      set_LED(0,red);
      return 1;
    }
  }
}

void solo_game(){
  set_LED(0, purple);
  Serial.println("Solo Game session initiated");
  while(1){
    for (uint8_t i=1; i < nb_capa; i++){ //i < nb_capa
      if (capa_touched(i)){ 
        if (zone_status[i] == 0){
          set_LED(i, blue);          
          zone_status[i] = 1;
          play_tone((int)i);
        }
        else{
          set_LED(i, off);
          zone_status[i] = 0;
          play_tone_short((int)i);
        }
        delay(100);
      }
    }
  }
}

void parent_game(){
  accept_game_request(); //waits until child presses the toy to accept request
  Serial.println("Parent game session on");
  sound_game_on();
  
  while (game_session_on){
    message = read_message();
    //blink_LED(0,yellow);
    messageID = message.substring(16, 20).toInt();

   
    switch(messageID){
      
      // Area activated by parent
      case 2003:                                  
        Serial.println("Message 2003 received from server");
        LEDid = read_LEDid(message);
         Serial.print("LEDid:");
         Serial.println(LEDid);
        if(game_session_on){
          game_set_LED(LEDid, on_parent);
          play_tone(LEDid);
          };break;

      case 2004:                                  
        Serial.println("Message 2004 received from server");
        LEDid = read_LEDid(message);
        if(game_session_on){
          game_set_LED(LEDid, off);
          play_tone_short(LEDid);
          };break;
      
      case 2005:
        end_game_session();
        // blink Heart LED to signal end of interaction
        sound_game_off();
        break; //end game session
    } 
  }
}


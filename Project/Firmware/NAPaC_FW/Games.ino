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
const uint8_t nb_zones = 7; // number of touch zones + 1
uint8_t zone_status[nb_zones] = {0};
uint8_t LEDid;
int c = 0;

bool accept_game_request(){
  mario();
  blink_LED(0,parent);
  Serial.println("Parent requested game session");
  Serial.println("Waiting for kid to accept game request");

  while (!game_session_on){
    // blinks until the child accepts the game session
    if ( c++ == 10 ){
      set_LED(0,parent);
    }
    else if ( c == 20){
      set_LED(0, off);
      c = 0;
      Serial.print(".");
    }
    if (presence()){
      accept_game_message();
      game_session_on = 1;
      set_LED(0,parent);
      parent_game();
      return 1;
    }
    delay(100);
  }
}


void end_game_session(){
  Serial.println("End of game session!");
  blink_LED(0, parent);
  blink_LED(0, parent);
  blink_LED(0, parent);
  sound_game_off();
  set_LED(0,off);
  all_LED_off();
  reset_zone_status();
  display_zone_status();
  game_session_on = 0;
}

uint8_t read_LEDid(String message){
  int offset = 48; // = "1"
  int LEDid = (int) message.charAt(23) - offset; // CHAR AT 23 TO BE TESTED
  Serial.println(LEDid);
  return LEDid;
}

void display_zone_status(){
  for (uint8_t i=1; i < nb_zones; i++){
    Serial.print(i);
    Serial.print("\t");
  }
  Serial.print("\n");
  for (uint8_t i=1; i < nb_zones; i++){
    Serial.print(zone_status[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}

void reset_zone_status(){
  for (uint8_t i=1; i < nb_zones; i++){
    zone_status[i] = 0;
  }
}

void solo_game(){
  //set_LED(0, kid);
  Serial.println("Solo Game session initiated");
  while(1){
    for (uint8_t i=1; i < nb_zones; i++){ //i < nb_zones
      if (capa_touched(i)){ 
        
//        if (i == 3){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          i = 2;
//        }
//
//        if (i == 4){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          i = 0;
//        }
        
        if (zone_status[i] == LED_off){
          game_set_LED(i, on_kid);
          if (sound_on){
            play_tone((int)i);}
          display_zone_status();
          delay(500);
        }
        else{
          game_set_LED(i, off);
          if (sound_on){
            play_tone_short((int)i);}
          display_zone_status();
          delay(500);

        }
        delay(100);
      }
    }
  }
}

void parent_game(){
  //accept_game_request(); //waits until child presses the toy to accept request
  Serial.println("Parent game session on");
  sound_game_on();

  display_zone_status();
  
  while (game_session_on){
    messageID = 0;
    message = read_message();
    Serial.print(message);
    if (!message.equals("")){
      messageID = message.substring(16, 20).toInt();
      display_zone_status();
      //Serial.print("Message ID:");
      //Serial.println(messageID);
    }
    
    switch(messageID){
      
      // Area activated by parent
      case 2003:                                  
        //Serial.println("Message 2003 received from server");
        LEDid = read_LEDid(message);

        Serial.print("LED activated by parent! LEDid:");
        Serial.println(LEDid);
        
//        if (LEDid == 3){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          LEDid = 2;
//          Serial.print("LED transformed by China Magic LEDid:");
//          Serial.println(LEDid);
//        }
//
//        if (LEDid == 4){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          LEDid = 0;
//          Serial.print("LED transformed by China Magic LEDid:");
//          Serial.println(LEDid);
//        }
                
        game_set_LED(LEDid, on_parent);
        if (sound_on){
          play_tone((int)LEDid);}
        display_zone_status();
        break;
          
      // Area turned off by parent
      case 2004:                                  
        //Serial.println("Message 2004 received from server");
        LEDid = read_LEDid(message);
        Serial.print("LED deactivated by parent! LEDid:");
        Serial.println(LEDid);
        game_set_LED(LEDid, off);
        if (sound_on){
          play_tone_short((int)LEDid);}
        display_zone_status();
        break;
          
      // Parent signals end of game session
      case 2005:
        end_game_session();
        return;  break;
    }
    
    for (uint8_t i=1; i < nb_zones; i++){ //i < nb_zones
      LEDid=i;
      
      if (capa_touched(i)){
        
//        if (i == 3){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          i = 2;
//        }
//
//        if (i == 4){ //CODE ADAPTED FOR CHINA PROTO ZONES
//          i = 0;
//        }
        
        display_zone_status();
        if (zone_status[i] == on_parent){
          Serial.print("LED deactivated by kid! LEDid:");
          Serial.println(LEDid);
          game_set_LED(LEDid, off);
          if (sound_on){
            play_tone_short((int)LEDid);}
          LED_off_message(LEDid);
          display_zone_status();
        }
        else{
          Serial.print("LED activated by kid! LEDid:");
          Serial.println(LEDid);
          set_LED(i, kid);     
          if (sound_on){   
            play_tone((int)LEDid);}
          LED_on_message(LEDid);
          display_zone_status();
        }
        delay(100);
      }
    } 
  }
}


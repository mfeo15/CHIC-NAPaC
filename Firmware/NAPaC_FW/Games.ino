/*
 * Game file containing functions for managing game sessions on Toygether plush
 */

//bool game_session_on = 0;

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

void start_game_session(){
  Serial.println("Beginning of game session!");
  blink_LED(0,red);
  game_session_on =1;
}

void end_game_session(){
  Serial.println("End of game session!");
  game_session_on = 0;
}

bool LED_sequence_request(String message){
  uint8_t game_led = 0;
  int offset = 48; // = "1"
  int nb_LED = (int) message.charAt(21) - offset;
  Serial.println(nb_LED);
  
  if (nb_LED > 1){
    Serial.println("Stupid you, we only have one LED working!");
    return 0;
  }

  set_LED(game_led , yellow); //MS4
  Serial.println("LED on");
  
  while (1){
    if (presence()){
      for (uint8_t i = 1; i <= nb_LED; i++){
      set_LED(i, off);
      set_LED(game_led,off);//MS4
      Serial.println("LED off");
      }
      return 1;
    }
  }
}


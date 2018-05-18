/*
 * Game file containing functions for managing game sessions on Toygether plush
 */

//bool game_session_on = 0;
uint8_t LED_status_game[9] = {0};

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
  set_LED(0,red);
  game_session_on =1;
}

void end_game_session(){
  Serial.println("End of game session!");
  set_LED(0,off);
  game_session_on = 0;
}

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
  while(1){
    for (uint8_t i=1; i < 6; i++){ //i < nb_capa
      if (capa_touched(i)){
        if (LED_status_game[i] == 0){
          set_LED(i, blue);
          LED_status_game[i] = 1;
        }
        else
        {
          set_LED(i, off);
          LED_status_game[i] = 0;
        }
        delay(100);
      }
    }
  }
}


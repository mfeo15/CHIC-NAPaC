/*
   Game file containing functions for managing game sessions on Toygether plush
*/

/*
   accept_game_request(); Blinks heart light to signal game session request from parent.
     Waits until the child presses the toy, sends an accept message to server.
   parent_game(); loops on parent/child game session until parent breaks off connection
     reads & sends message to/from server for interactions
*/



uint8_t LEDid;

/*
  bool accept_game_request(){
  mario();
  //blink_LED(0,parent);
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
*/

void display_zone_status() {
  Serial.println("----------------------------------------------");
  for (uint8_t i = 0; i < ZONES_NUMBER; i++) {
    Serial.print(i + 1);
    Serial.print("\t");
  }
  Serial.print("\n");
  for (uint8_t i = 0; i < ZONES_NUMBER; i++) {
    Serial.print(zone_status[i]);
    Serial.print("\t");
  }
  Serial.println("\n");
  Serial.println("----------------------------------------------");
  Serial.print("\n\n");
}

void reset_zone_status() {
  for (uint8_t i = 0; i < ZONES_NUMBER; i++) {
    zone_status[i] = LED_off;
  }
}


void update_game_status() {

  for (uint8_t LEDid = 0; LEDid < ZONES_NUMBER; LEDid++) {

    if (button_pressed(LEDid)) {

      uint8_t currentZoneLED = zone_status[LEDid];

      switch (currentZoneLED) {
        case LED_off:
          zone_status[LEDid] = LED_kid;

          
          if (sound_on) play_tone((int)LEDid);
          LED_on_message(LEDid);
          break;

        case LED_kid:
          if (sound_on) play_tone((int)LEDid);
          break;

        case LED_parent:
          zone_status[LEDid] = LED_off;

          if (sound_on) play_tone_short((int)LEDid);
          LED_off_message(LEDid);
          delay(500);
          break;
      }
      //delay(100);
    }
  }
}



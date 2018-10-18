/*
 * NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
 */

int incomingByte = 0;
//const char* server_host = "192.168.1.10";
enum colours{off,white,red,green,blue,purple,yellow,parent,kid};

String message;
int messageID;
bool game_session_on = 0;

bool sound_on = 0;  // set to 1 to have sound, set to zero to keep silent
bool test_mode_on = 0; // does test loops in main loop
bool test_solo = 1; // set to 1 for offline tests (solo mode), 
                    // set to 0 for regular operation


void setup(){
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor

    setup_LEDs();
    setup_touch();
    setup_sound();

    //sound_test();
    if (sound_on){
      mario();}

    if ( !test_solo){
      setup_wifi_smartconfig();
      setup_wifi();
      connect_to_server();
    }

    hello();
    
    if ( !test_solo){
      first_message();}
}

void test_loop(void){
  
  // LED test: turns on heart LED in all colours one after another then blinks all LEDs
  test_LEDs(); 

  // Touch test: prints touched sensors in serial
  test_if_touched();
}

void loop()
{    

  if (test_mode_on){
    test_loop();
  }
  
  if ( test_solo){
    // if solo mode is on, loops in solo game
    solo_game();
  }

  if ( !test_solo){
    message = read_message();
    if (!message.equals("")){
      messageID = message.substring(16, 20).toInt();
    }
    
    switch(messageID){
      case 2001:
        Serial.println("Message 2001 received from server");
        accept_game_request();
        break;
    }
  }

//    check_to_close_ServerConnection();

}

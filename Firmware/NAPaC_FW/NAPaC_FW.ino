/*
 * NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
 */

int incomingByte = 0;
//const char* server_host = "192.168.1.10";
enum colours{off,white,red,green,blue,purple,yellow,parent,kid};

String message;
int messageID;
bool game_session_on = 0;


void setup(){
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor

    setup_LEDs();
    setup_capa();
    setup_sound();

    //sound_test();
    //mario();

    //setup_wifi_smartconfig();
    //setup_wifi();
    //connect_to_server();

    blink_LED(0,yellow);
    hello();
    //first_message();
}

void loop()
{    
  test_LEDs();
  //test_touch_values();
  //test_if_touched();
  //solo_game();

  
  message = read_message();
  if (!message.equals("")){
    messageID = message.substring(16, 20).toInt();
  }

  //accept_game_request();
  //parent_game();
  
  switch(messageID){
    case 2001:
      Serial.println("Message 2001 received from server");
      accept_game_request();
      break;
  }

//    check_to_close_ServerConnection();

}

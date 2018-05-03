/*
 *  Edited code looking horrible to demonstrate neopixels on esp32
 *  Capa pads on soft paw turn on neopixels
 *  Random colours may turn on for unknown reasons
 */

int incomingByte = 0;
//const char* server_host = "192.168.1.10";
enum colours{off,red,green,blue,purple,yellow};

String message;
int messageID;
bool game_session_on = 0;


void setup(){
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor

    setup_LEDs();
    setup_capa();

    blink_LED(0,red);
    set_LED(0,red);   
    setup_wifi();

    blink_LED(0,purple);
    set_LED(0,purple);
    connect_to_server();
    
    setup_alphabet();

    blink_LED(0,yellow);
    hello();
    first_message();
}

void loop()
{    
    message = read_message();
    //blink_LED(0,yellow);
    messageID = message.substring(16, 20).toInt();
    
    switch(messageID){
      case 2001:
        Serial.println("Message 2001 received from server");
        if(accept_game_request()){
          start_game_session();
          game_session_on = 1;
          };break; //Turn on LED to signal game session invitation
      //when touched send 2002
      case 2003:
        Serial.println("Message 2003 received from server");
        if(game_session_on){
          LED_sequence_request(message);
          };break; //LED interactive sequence
      case 2005:
        end_game_session();
        game_session_on = 0;
        break; //end game session
    }

    check_to_close_ServerConnection();

}

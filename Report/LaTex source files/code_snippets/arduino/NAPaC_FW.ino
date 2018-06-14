/*
 * NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
 */

int incomingByte = 0;
enum colours{off,white,red,green,blue,purple,yellow,parent,kid};

String message;
int messageID;
bool game_session_on = 0;


void setup(){
    Serial.begin(115200);
    delay(1000); 
    
    setup_LEDs();
    setup_capa();
    setup_sound();

    setup_wifi_smartconfig();
    connect_to_server();

    hello();
    first_message();
}

void loop(){   
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

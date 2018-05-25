/*
 * Messages file containing messages sent and received by server
 */
 
#include <string.h>

char STX[1] = {char(2)};
char EOT[1] = {char(4)};
char RS[1]  = {char(30)};
char US[1]  = {char(31)};

//void setup_messages_alphabet(){
//  STX[0] = char(2);
//  EOT[0] = char(4);
//  RS[0]  = char(30);
//  US[0]  = char(31);
//}

//First packet : the microcontroller presents itself to the server, so that
//the server can link its IP address with its microcontroller name
void first_message(){
  char message1[22]={0};
  sprintf(message1,"%c0020%cS001%cP314%c0001%c", STX[0],RS[0],RS[0],RS[0],EOT[0]);
  send_message(message1);
  Serial.println("message sent!");
}

void accept_game_message(){
  Serial.println("Child accepted game session!");
  char message1[22]={0};
  sprintf(message1,"%c0020%cU123%cP314%c2002%c", STX[0],RS[0],RS[0],RS[0],EOT[0]);
  send_message(message1);
  Serial.println("message sent!");
}



void hello(){
    Serial.println();
    Serial.println("                                                                                ");
    Serial.println("  _   _    _    ____        ____   _____ _                                      ");
    Serial.println(" | \\ | |  / \\  |  _ \\ __ _ / ___| |  ___(_)_ __ _ __ _____      ____ _ _ __ ___ ");
    Serial.println(" |  \\| | / _ \\ | |_) / _` | |     | |_  | | '__| '_ ` _ \\ \\ /\\ / / _` | '__/ _ \\");
    Serial.println(" | |\\  |/ ___ \\|  __/ (_| | |___  |  _| | | |  | | | | | \\ V  V / (_| | | |  __/");
    Serial.println(" |_| \\_/_/   \\_\\_|   \\__,_|\\____| |_|   |_|_|  |_| |_| |_|\\_/\\_/ \\__,_|_|  \\___|");
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    
    Serial.println("Toygether Welcomes You To MS4!");
    Serial.println();
    Serial.println();

    //set_pixels_colour(black);
}
 





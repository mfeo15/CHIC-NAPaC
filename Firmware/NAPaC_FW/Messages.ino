/*
 * Messages file containing messages sent and received by server
 */
 
#include <string.h>

char STX[1];
char EOT[1];
char RS[1];
char US[1];

void setup_alphabet(){
  STX[0] = char(2);
  EOT[0] = char(4);
  RS[0]  = char(30);
  US[0]  = char(31);
}

void first_message(){
  char message1[22]={0};
  sprintf(message1,"%c0020%cS001%cP314%c0001%c", STX[0],RS[0],RS[0],RS[0],EOT[0]);
  send_message(message1);
  Serial.println("message sent!");
}





#include <string.h>

char STX[1];
char EOT[1];
char RS[1];
char US[1];

void setup() {

  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  
  STX[0] = char(2);
  EOT[0] = char(4);
  RS[0]  = char(30);
  US[0]  = char(31);
  
  Serial.println("STX=");Serial.println(STX[0]);
  Serial.println("EOT=");Serial.println(EOT[0]);
  Serial.println("RS=");Serial.println(RS[0]);
  Serial.println("US=");Serial.println(US[0]);

  char message1[21]={0};
  //char message1[21] = {0};
 //String message1;
// strcat(message1,(char*)STX);
// strcpy(message1,"1");
// strcat(message1,RS);
// strcat(message1,"2");

 sprintf(message1,"%c0020%cS001%cP314%c001%c", STX[0],RS[0],RS[0],RS[0],EOT[0]);
 //sprintf(message1,"0020 S001 P314");
 //message1[20]='\0';
 Serial.println("message=");
 Serial.println(message1);
 
  
  while(1){
  //Serial.println("hello\n");
  delay(500);
  }

}

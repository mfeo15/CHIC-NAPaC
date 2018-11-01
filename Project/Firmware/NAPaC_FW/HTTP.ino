/*
   HTTP Client file containing functions for acting as an HTTP Client in NAPaC project
   Send and receive messages (JSON) between clients and server

*/

#include <HTTPClient.h>
#include <ArduinoJson.h>

const int POOLING_DELAY = 100;

const char* pushURL = "http://toygether.altervista.org/receive_stream.php";
const char* pullURL = "http://toygether.altervista.org/pooling_stream.php";

void pushMessage(char* message) {
  
}

String pullMessage()
{
  delay(POOLING_DELAY);
  
  char JSONMessage[] = " {\"source\": \"T123\"} ";

  // Prepare HTTP environment
  HTTPClient http;
  http.begin(pullURL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONMessage);   //Send the request
  String payload = http.getString();             //Get the response payload

  //Serial.println();
  //Serial.print("Received response with code ");
  //Serial.print(httpCode);   //Print HTTP return code
  //Serial.print("\n");
  //Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  return payload;
}


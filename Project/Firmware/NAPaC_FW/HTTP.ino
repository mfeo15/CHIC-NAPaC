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

  String p = sendMessage(message, pushURL);
}

String pullMessage()
{
  //delay(POOLING_DELAY);

  char JSONMessage[] = " {\"source\": \"T314\"} ";

  return sendMessage(JSONMessage, pullURL);
}

String sendMessage(char* message, const char* url) {
  // Prepare HTTP environment
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(message);   //Send the request
  String payload = http.getString();       //Get the response payload

  http.end();  //Close connection

  return payload;
}


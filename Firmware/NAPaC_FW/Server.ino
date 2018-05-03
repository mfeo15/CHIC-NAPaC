/*
 * Server file containing functions for server connectivity in NAPaC project
 * Connects to server, listens to messages and sends messages back
 * 
 */

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

// Use WiFiClient class to create TCP connections
WiFiClient client;
const uint16_t server_port = 6789;  
const char* server_host = "192.168.1.10";

/*
 * Waits until connects to the TCP server, at the given host ip and port
 */
void connect_to_server()//char * server_host
{   
    Serial.print("connecting to Server ");
    Serial.println(server_host);

    while (!client.connect(server_host, server_port)) 
    {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
    }
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
}

void send_message(const char *message){ //send the string reference to avoid heap Swiss cheese
 client.print(message); 
}

/*
 * Sends data packet to server
 * First packet : the microcontroller presents itself to the server, so that
 *  the server can link its IP address with its microcontroller name
 * Following packets : when an action on the plush toy needs to be notified to the
 *  parent on the app (to be implemented)
 */
void send_message()
{
  //dunno
}

//Reads the message stored on the server, sent by the parent from the app
String read_message() 
{
    String stringa = "";
    char c;

    c = client.read();
    if (c == char(2)){      //STX[0] = char(2);
    do{
        stringa += c;
        c = client.read();  // lettura di un byte  
        //Serial.println(c);
    }while(c != char(4));//EOT[0] = char(4);
    Serial.println(stringa);
    }
    return stringa;
}

/*
 * Checks if the user tapped any command from keyboard on the serial monitor
 *  If True: turns the connection with the server off and the connection cannot
 *  be done anymore (dead end)
 *  Currently, the user is forced to manually reset the board to restart the program 
 *  from scratch and reconnect to the server
 */
void check_to_close_ServerConnection()
{
    if (Serial.available() > 0)
    {
        static bool connection_closed = 0;
        
        while( Serial.available() )
        {
            //Empties the buffer in the monitor
            int incomingByte = Serial.read();
        }

        if (connection_closed == 0)
        {
            Serial.println("closing connection");
            client.stop();
            connection_closed = 1;
        }
        else 
        {
            Serial.println("connection already closed");
            Serial.println("Please reset the board to start again the program");
        }
    }
}

/*
 * Reads from Server if any request has been sent from the app to activate a LED
 */
void check_to_activateLED()
{
    if (client.available() )
    {
          String line = read_message(); 
          Serial.println();
          Serial.println();
          Serial.println("_______________________________________________________");
          Serial.println("> Message from server:");
          Serial.print("  "); Serial.println(line);
          Serial.println();
          //Serial.println(line.charAt(18));          

          if (line.charAt(18) == '1')     //If the LED needs to be turned ON
          {
               //read color of the LED to light ON 
               String color = line.substring(15, 18);  //char from 15 included to 18 not included
               Serial.print("Request from server received: Activate LED of color "); Serial.println(color);
               Serial.println();
               //toggleLED(color);
          }
    }
}

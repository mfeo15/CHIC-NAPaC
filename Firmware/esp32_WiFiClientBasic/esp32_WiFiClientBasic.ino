/*
 *  Author: Simone Aron Sanso and Matteo Yann Feo
 *  Last revision : March 22nd 2018
 *  
 *  Reads message from a set up TCP Server to light a LED on
 *  Listens to touch sensors on the plush toy to turn the LED off 
 *  
 *  (Does not notify the parent yet, sending a message back to the TCP server)
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

// Use WiFiClient class to create TCP connections
WiFiClient client;

// Define which digital pins correspond to colored LEDs
const int RED_LED = 21;   //IO21
const int YEL_LED = 22;   //IO22
const int GRN_LED = 23;   //IO23

// Define which capacitive touch sensors/pins correspond to each colored LED
const int RED_TOUCH = T3; //IO15
const int YEL_TOUCH = T6; //IO14
const int GRN_TOUCH = T4; //IO13

// To compare first and current sensor input (touch sensors) (far in time)
const int THRESHOLD_RED = 25;
const int THRESHOLD_YEL = 30;
const int THRESHOLD_GRN = 25;

// To compare previous and current sensor input (touch sensors) (close in time)
const int MAX_DIFF = 3;

//The smaller SAMPLING_FREQ is, the faster is the response to light off a LED but 
// the larger is the risk of turning the LED off involontarily
const int SAMPLING_FREQ = 10000;

//WiFi settings
//Yann's hotspot    : "MiPhone", "1234abcd"     
//Simone's hotspot  : "iPhoneSimoneSanso", "a1b2c3Sim"
const char * wifi_ssid = "iPhoneSimoneSanso";
const char * wifi_password = "a1b2c3Sim";

//Server settings 
//IP of Yann's hotspot    : "192.168.43.213"
//IP of Simone's hotspot  : "172.20.10.9"
const char * server_host = "172.20.10.9";
const uint16_t server_port = 6789;          // port of the server (stays unchanged)


/*
 * Resetting the board makes the program start from here, before callingthe 
 * loop() function
 */
void setup()
{    
    initial_setup();

    start_wifi();
    delay(500);

    connect_to_server();
    
    send_Message_to_Server();
}

/*
 * Sets the serial monitor at the correct baud rate and initializes the output pins
 */
void initial_setup()
{
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor
    delay(10);
    
    // initialize digital pins for the LEDs as an output.
    pinMode(RED_LED, OUTPUT);
    pinMode(YEL_LED, OUTPUT);
    pinMode(GRN_LED, OUTPUT);

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
    
    Serial.println("ESP32 Welcomes You To MS3");
    Serial.println();
    Serial.println();
    delay(1000);
}

/*
 * Configures SSID and password of the WiFi and waits until the microcontroller connects
 * to it
 */
void start_wifi()
{
    // We start by connecting to a WiFi network : WiFiMulti.addAP("SSID", "passpasspass");
    WiFiMulti.addAP(wifi_ssid, wifi_password);
  
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

/*
 * Waits until connects to the TCP server, at the given host ip and port
 */
void connect_to_server()
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

/*
 * Sends data packet to server
 * First packet : the microcontroller presents itself to the server, so that
 *  the server can link its IP address with its microcontroller name
 * Following packets : when an action on the plush toy needs to be notified to the
 *  parent on the app (to be implemented)
 */
void send_Message_to_Server()
{
    static unsigned int counter;
    static bool first_message = 1; 

    if (first_message == 1)
    {
        // First message to send to server : "RECEIVER:SENDER:MSG_ID:PARAM$" with
        // RECEIVER "S001" (SERVER_NAME)
        // SENDER   "P314" (MICROCONTROLLER_NAME)
        // MSG_ID   "0001" (Identification)
        // PARAM    "0000"
        // and finish with caracter '$'
        client.print("S001:P314:0001:0000$");

        first_message = 0;
        counter = 0;
        return;
    }

    else 
    {
        //To be implemented here : sending back messages to the TCP server
        // Write data to server "RECEIVER:SENDER:MSG_ID:PARAM$"
        //client.print("U123:P314:4242:RED1$");
    }   
}

/*
 * Reads the message stored on the server, sent by the parent from the app
 */
String read_Message_from_Server() 
{
    String stringa = "";
  
    for (int i=0; i<20; i++)
    {
        char c = client.read();  // lettura di un byte
        stringa += c;
    }
    
    return stringa;
}

/*
 * Activates the LED of color "color"
 */
void activate_led(String color)
{
    //Serial.print("Activating "); Serial.print(color); Serial.println("_LED");
    
    if (color == "RED") 
    {
        digitalWrite (RED_LED, HIGH);  // turn on the LED
        return;
    }
  
    if (color == "GRN") 
    {
        digitalWrite (GRN_LED, HIGH);  // turn on the LED
        return;
    }
  
    if (color == "YEL") 
    {
        digitalWrite (YEL_LED, HIGH);  // turn on the LED
        return;
    }
}

/*
 * Deactivates the LED of color "color"
 */
void deactivate_led(String color)
{
    //Serial.print("Deactivating "); Serial.print(color); Serial.println("_LED");
    
    if (color == "RED") 
    {
        digitalWrite (RED_LED, LOW);  // turn off the LED
        return;
    }
  
    if (color == "GRN") 
    {
        digitalWrite (GRN_LED, LOW);  // turn off the LED
        return;
    }
  
    if (color == "YEL") 
    {
        digitalWrite (YEL_LED, LOW);  // turn off the LED
        return;
    }
}

/*
 * CAUTIOUS : The "first_read_[color]" values are assigned as constant but need to be 
 *  better defined in future, depending on which value each touch sensor stabilizes around
 *  Currently, the values have been manually hard coded and are specific to this board, 
 *  with these particular touch sensors.
 */
void readTouchSensor()
{
    static bool first_measure = 1; 
    static unsigned int counter, debug_measurement;
    static int first_read_RED, first_read_YEL, first_read_GRN;
    static int prev_read_RED, prev_read_YEL, prev_read_GRN;
    int current_read_RED, current_read_YEL, current_read_GRN;

    if (first_measure == 1)   //Initialization
    {
        //first_read_RED = touchRead(RED_TOUCH);
        //first_read_YEL = touchRead(YEL_TOUCH);
        //first_read_GRN = touchRead(GRN_TOUCH);
        first_read_RED = 40;
        first_read_YEL = 46;
        first_read_GRN = 37;
        first_measure  = 0;
        debug_measurement = 0;
        counter        = 0;
        return;
    }

    else if (counter > SAMPLING_FREQ)   //To reduce the frequency at which the sensors are checked
    {   
        //Serial.println(debug_measurement);
        //displayMonitorTouchSensors(); 
        //Serial.print("first_read_RED : "); Serial.println(first_read_RED);
        //Serial.print("current_read_RED : "); Serial.println(current_read_RED);
        //Serial.print("prev_read_RED : "); Serial.println(prev_read_RED);
        
        current_read_RED = touchRead(RED_TOUCH);
        current_read_YEL = touchRead(YEL_TOUCH);
        current_read_GRN = touchRead(GRN_TOUCH);
        
        if ( (abs(first_read_RED - current_read_RED) >= THRESHOLD_RED) 
            and (first_read_RED > current_read_RED) 
            and (abs(prev_read_RED - current_read_RED) <= MAX_DIFF) )
        {
            deactivate_led("RED");
        }                
        
        else if ( (abs(first_read_YEL - current_read_YEL) >= THRESHOLD_YEL) 
            and (first_read_YEL > current_read_YEL)
            and (abs(prev_read_YEL - current_read_YEL) <= MAX_DIFF) )
        {
            deactivate_led("YEL");
        }
       
        else if ( (abs(first_read_GRN - current_read_GRN) >= THRESHOLD_GRN) 
            and (first_read_GRN > current_read_GRN)
            and (abs(prev_read_GRN - current_read_GRN) <= MAX_DIFF) )
        {
            deactivate_led("GRN");  
        }

         //Update
         prev_read_RED = current_read_RED;
         prev_read_YEL = current_read_YEL;
         prev_read_GRN = current_read_GRN;
         counter       = 0;
         debug_measurement++;
    } 

    counter++;
}

/*
 * For debug purposes : prints out the read values from the capacitive touch sensors
 */
void displayMonitorTouchSensors()
{
    Serial.print("RED : "); Serial.println(touchRead(RED_TOUCH));
    Serial.print("YEL : "); Serial.println(touchRead(YEL_TOUCH));
    Serial.print("GRN : "); Serial.println(touchRead(GRN_TOUCH));
    Serial.println("");
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
          String line = read_Message_from_Server(); 
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
               activate_led(color);
          }
    }
}

void loop()
{       
    check_to_activateLED();

    readTouchSensor();

    check_to_close_ServerConnection();
}


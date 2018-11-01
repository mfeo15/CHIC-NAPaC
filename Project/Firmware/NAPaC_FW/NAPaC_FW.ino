/*
   NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
*/

#include <Message.h>
#include <ArduinoJson.h>

int incomingByte = 0;
//const char* server_host = "192.168.1.10";
enum colours {off, white, red, green, blue, purple, yellow, parent, kid};

enum state {boot, offline, online, game_request, game, game_update};

state currentState = boot;

TaskHandle_t LoopTaskOnCore0;

int c = 0;

String message;
int messageID;
bool game_session_on = 0;

bool sound_on = 0;  // set to 1 to have sound, set to zero to keep silent
bool test_mode_on = 0; // does test loops in main loop
bool test_solo = 0; // set to 1 for offline tests (solo mode),
// set to 0 for regular operation


void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor

  setup_LEDs();
  setup_touch();
  setup_sound();

  //sound_test();
  if (sound_on) {
    mario();
  }

  xTaskCreatePinnedToCore(
    loopOnCore0,
    "loopTaskCore0",
    10000,
    NULL,
    1,
    &LoopTaskOnCore0,
    0);
}

void hello() {
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

  Serial.println("Toygether Welcomes You To its Firmware warm insides!");
  Serial.println();
  Serial.println();
}

void loopOnCore0( void* parameter)
{
  while (1)
  {
    String m = pullMessage();

    StaticJsonBuffer<300> JSONBuffer;                         //Memory pool
    JsonObject& parsed = JSONBuffer.parseObject(m);           //Parse message

    if (parsed.success()) {   //Check for errors in parsing
      int id = atoi(parsed["id"]);
      Serial.print("New message received: ");
      Serial.println(id);

      switch (id) {
        case 2001:
          currentState = game_request;
          break;
        case 2003:
        
        case 2004:
        case 2005:
        break;
      }
    }
  }
}

void loop()
{
  int unused = uxTaskGetStackHighWaterMark(LoopTaskOnCore0);
  //Serial.println(unused);

  switch (currentState) {
    case boot:
      hello();
      currentState = offline;
      break;
    case offline:
      Serial.println("State: OFFLINE");

      if ( !test_solo) {
        //setup_wifi_smartconfig();
        setup_wifi();
        currentState = online;
      }

      break;
    case online:
      Serial.println("State: ONLINE");
      break;
    case game_request:
      Serial.println("State: GAME REQUEST");

      mario();
      blink_LED(0, parent);
      Serial.println("Parent requested game session");
      Serial.println("Waiting for kid to accept game request");

      while (true) {
        // blinks until the child accepts the game session
        if ( c++ == 10 ) {
          set_LED(0, parent);
        }
        else if ( c == 20) {
          set_LED(0, off);
          c = 0;
          //Serial.print(".");
        }
        if (presence()) {
          //accept_game_message();
          set_LED(0, parent);
          //parent_game();
          currentState = game;
        }
      }

      break;
    case game:
      Serial.println("State: GAME");
      break;
    case game_update:
      Serial.println("State: GAME UPDATE");
      break;

  }
}

void test_loop(void) {

  // LED test: turns on heart LED in all colours one after another then blinks all LEDs
  test_LEDs();

  // Touch test: prints touched sensors in serial
  test_if_touched();
}



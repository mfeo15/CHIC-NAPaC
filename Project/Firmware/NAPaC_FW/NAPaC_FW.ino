/*
   NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
*/

#include <ArduinoJson.h>

TaskHandle_t LoopTaskOnCore0;
SemaphoreHandle_t baton;

enum colours {off, white, red, green, blue, purple, yellow, parent, kid};

enum state {boot, offline, online, game_request_received, game_request_waiting, start_game, game, game_update, end_game};

state currentState = boot;

bool sound_on = 0;  // set to 1 to have sound, set to zero to keep silent
bool test_mode_on = 0; // does test loops in main loop
bool test_solo = 0; // set to 1 for offline tests (solo mode),
// set to 0 for regular operation

enum LEDmode { LED_off, LED_kid, LED_parent };

const uint8_t ZONES_NUMBER = 6;

uint8_t zone_status[ZONES_NUMBER] = {LED_off, LED_off, LED_off, LED_off, LED_off, LED_off };

//int zoneLEDS[] = {0, 0, 0, 0, 0, 0};

int c = 0;

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor

  setup_game_LEDs();
  setup_presence_LEDs();
  setup_touch();
  setup_sound();

  //sound_test();
  if (sound_on) {
    mario();
  }

  baton = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    loopOnCore0,
    "loopTaskCore0",
    10000,
    NULL,
    1,
    &LoopTaskOnCore0,
    0);
}


void loopOnCore0( void* parameter)
{
  while (1)
  {
    String m = pullMessage();

    StaticJsonBuffer<300> JSONBuffer;                         //Memory pool
    JsonObject& parsed = JSONBuffer.parseObject(m);           //Parse message

    if (! parsed.success()) {   //Check for errors in parsing
      continue;
    }

    int id = atoi(parsed["id"]);
    if (id == 0) {
      continue;
    }

    Serial.print("New message received: ");
    Serial.println(id);

    if (id == 2001) {
      currentState = game_request_received;
      continue;
    }

    if (id == 2003)
    {
      int modifiedZone = atoi(parsed["zone"]);

      xSemaphoreTake( baton, portMAX_DELAY );

      if (parsed["status"] == "ON") {
        zone_status[modifiedZone - 1] = LED_parent;
        if (sound_on) play_tone(modifiedZone);
      } else {
        zone_status[modifiedZone - 1] = LED_off;
        if (sound_on) play_tone_short(modifiedZone);
      }

      xSemaphoreGive(baton);
      continue;
    }

    if (id == 2005) {
      currentState = end_game;
      continue;
    }

  }
}

void loop()
{
  switch (currentState) {
    case boot:                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: BOOTING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      hello();
      currentState = offline;
      break;

    case offline:                 // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: OFFLINE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      if ( !test_solo) {
        //setup_wifi_smartconfig();
        setup_wifi();
        currentState = online;
      }

      break;

    case online:                  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: ONLINE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%;
      break;

    case game_request_received:   // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME REQUEST RECEIVED %%%%%%%%%%%%%%%%%

      mario();
      blink_presence_LEDs(green);
      Serial.println("Parent requested game session");
      Serial.println("Waiting for kid to accept game request");

      currentState = game_request_waiting;

      break;

    case game_request_waiting:    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME REQUEST WAITING %%%%%%%%%%%%%%%%%%
      // blinks until the child accepts the game session
      blink_presence_LEDs(green);

      /*
        if (presence()) {
        //accept_game_message();
        set_LED(0, parent);
        //parent_game();
        currentState = game;
        }
      */

      if (Serial.available() > 0) {

        accept_game_message();
        set_presence_LEDs(green);
        currentState = game;
      }

      break;

    case start_game:            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: START GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("Parent game session on");
      sound_game_on();

      display_zone_status();
      break;

    case game:                   // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      xSemaphoreTake( baton, portMAX_DELAY );
      update_game_status();
      xSemaphoreGive(baton);
      delay(50);

      display_zone_status();
      update_LEDs(zone_status);
      break;

    case game_update:
      break;

    case end_game:               // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: END GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      end_game_session();
      currentState = online;
      break;
  }
}

void test_loop(void) {

  // LED test: turns on heart LED in all colours one after another then blinks all LEDs
  test_presence_LEDs();

  // Touch test: prints touched sensors in serial
  test_if_touched();
}



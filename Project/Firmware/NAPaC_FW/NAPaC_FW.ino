/*
   NAPaC main Firmware file by Chloe Dickson for Toygether project, CHIC 2018
*/

#include <ArduinoJson.h>

TaskHandle_t PollingHandle;
TaskHandle_t UxHandle;
SemaphoreHandle_t baton;

enum colours {off, white, red, green, blue, purple, yellow, parent, kid};

enum state {boot, offline, online, game_request_received, game_request_waiting, start_game, game, end_game};

state currentState = boot;

bool sound_on = 0;  // set to 1 to have sound, set to zero to keep silent

enum LEDmode { LED_off, LED_kid, LED_parent };

const uint8_t ZONES_NUMBER = 6;

uint8_t zone_status[ZONES_NUMBER] = {LED_off, LED_off, LED_off, LED_off, LED_off, LED_off };

//uint8_t zone_status[ZONES_NUMBER] = {LED_off};

void setup() {
  Serial.begin(115200);

  //Setup of the different components
  setup_game_LEDs();
  setup_presence_LEDs();
  setup_touch();
  setup_sound();

  baton = xSemaphoreCreateMutex();
}

void update_game_status_by_parent(JsonObject& parsed) {
  int modifiedZone = atoi(parsed["zone"]);

  //xSemaphoreTake( baton, portMAX_DELAY );

  if (parsed["status"] == "ON") {
    zone_status[modifiedZone - 1] = LED_parent;
    if (sound_on) play_tone(modifiedZone);
  } else {
    zone_status[modifiedZone - 1] = LED_off;
    if (sound_on) play_tone_short(modifiedZone);
  }

  //xSemaphoreGive(baton);
}

/**
   Polling loop to handle the incoming messages from the parent in parallel to the other local tasks.

*/
void polling_loop( void* parameter)
{
  StaticJsonBuffer<300> JSONBuffer;

  while (1)
  {
    String m = pullMessage();

    //StaticJsonBuffer<300> JSONBuffer;                         //Memory pool
    JsonObject& parsed = JSONBuffer.parseObject(m);           //Parse message

    if (! parsed.success()) {   //Check for errors in parsing
      continue;
    }

    int id = atoi(parsed["id"]);

    switch (id) {
      case 0 :
        break;
      case 2001:
        Serial.println(m);
        currentState = game_request_received;
        break;
      case 2003:
        Serial.println(m);
        update_game_status_by_parent(parsed);
        break;
      case 2005:
        Serial.println(m);
        currentState = end_game;
        break;
    }

    JSONBuffer.clear();
  }
}

/**
   UX loop code for the task created during game mode in order to parallize the user inputs (main loop)
   with any output to the kid (sounds and lights)

*/
void ux_loop( void* parameter) {
  while (1) {

    switch (currentState) {
      case game_request_waiting:
        blink_all_game_LEDs();
        blink_presence_LEDs(green);
        break;

      case start_game:
        turn_all_game_LEDs_off();
        set_presence_LEDs(green);
        sound_game_on();
        break;

      case game:
        update_LEDs(zone_status);
        break;
    }
  }
}

/**
   Main loop of the firmware, taking care of handling the state-machine, the creation of supplementary tasks,
   general operations (wifi connection, prints, sounds) and during game mode of the button input from the kid

*/
void loop()
{
  switch (currentState) {
    case boot:                    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: BOOTING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      hello();
      if (sound_on) mario();
      currentState = offline;
      break;

    case offline:                 // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: OFFLINE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      //setup_wifi_smartconfig();
      setup_wifi();
      blink_game_LED(4);
      xTaskCreatePinnedToCore(polling_loop, "polling_loop", 10000, NULL, 1, &PollingHandle, 0);
      currentState = online;
      break;

    case online:                  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: ONLINE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%;
      break;

    case game_request_received:   // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME REQUEST RECEIVED %%%%%%%%%%%%%%%%%

      mario();
      xTaskCreatePinnedToCore(ux_loop, "ux_loop", 10000, NULL, 1, &UxHandle, 1);
      currentState = game_request_waiting;
      break;

    case game_request_waiting:    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME REQUEST WAITING %%%%%%%%%%%%%%%%%%

      if (presence()) currentState = start_game;
      break;

    case start_game:            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: START GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      accept_game_message();

      delay(1000);
      currentState = game;
      break;

    case game:                   // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      //xSemaphoreTake( baton, portMAX_DELAY );
      update_game_status();
      //xSemaphoreGive(baton);
      //delay(50);

      break;

    case end_game:               // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% STATE: END GAME %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

      blink_presence_LEDs(green);
      blink_presence_LEDs(green);
      blink_presence_LEDs(green);
      sound_game_off();
      turn_all_game_LEDs_off();

      reset_zone_status();

      vTaskDelete(UxHandle);
      currentState = online;
      break;
  }
}


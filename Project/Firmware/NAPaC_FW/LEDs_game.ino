
const uint8_t LED_1 = 23;
const uint8_t LED_2 = 22;
const uint8_t LED_3 = 19;
const uint8_t LED_4 = 18;
const uint8_t LED_5 = 5;
const uint8_t LED_6 = 0;

void setup_game_LEDs() {
  // initialize digital pin as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
}

int get_pin_GPIO(uint8_t led) {
  if (led == 1) return LED_1;
  if (led == 2) return LED_2;
  if (led == 3) return LED_3;
  if (led == 4) return LED_4;
  if (led == 5) return LED_5;
  if (led == 6) return LED_6;
}

void update_LED(uint8_t led, uint8_t led_mode) {

  switch (led_mode) {
    case LED_off:
      digitalWrite( get_pin_GPIO(led), LOW);
      break;

    case LED_parent:
      //blink_game_LED(led);
      digitalWrite( get_pin_GPIO(led), !digitalRead(get_pin_GPIO(led)) );
      break;

    case LED_kid:
      digitalWrite( get_pin_GPIO(led), HIGH);
      break;
  }
}

void update_LEDs(uint8_t leds[]) {
  for (int j = 0; j < 4; j++) {
    
    for (int i = 0; i < ZONES_NUMBER; i++) {
      //update_LED( get_pin_GPIO(i + 1), leds[i]);

      uint8_t led = i+1;
      uint8_t led_mode = leds[i];

      switch (led_mode) {
        case LED_off:
          digitalWrite( get_pin_GPIO(led), LOW);
          break;

        case LED_parent:
          if ( (j % 2) == 0)  {
            digitalWrite( get_pin_GPIO(led), HIGH );
          } else {
            digitalWrite( get_pin_GPIO(led), LOW );
          }
          
          break;

        case LED_kid:
          digitalWrite( get_pin_GPIO(led), HIGH);
          break;
      }
    }
    delay(250);
  }
}

void blink_game_LED(uint8_t led) {
  digitalWrite( get_pin_GPIO(led), HIGH);
  delay(250);
  digitalWrite( get_pin_GPIO(led), LOW);
  delay(250);
  digitalWrite( get_pin_GPIO(led), HIGH);
  delay(250);
  digitalWrite( get_pin_GPIO(led), LOW);
}



void turn_all_game_LEDs_off() {
  for (int i = 0; i < ZONES_NUMBER; i++) {
    update_LED( get_pin_GPIO(i + 1), LED_off);
  }
}




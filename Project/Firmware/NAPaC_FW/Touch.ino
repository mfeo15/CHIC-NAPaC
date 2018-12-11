/*
   Touch file containing functions for managing touch sensors in NAPaC project
*/

/*
   setup_touch(); sets up touch sensors with pull-up as inputs
   touch_read_value(touch_id); touch_id = 1,...,8 returns capa value
   capa_touched(touch_id); returns if capa is being touched (value < 5)
   presence(); returns 1 if at least one sensor is being touched
   test_touch_values(); prints the values of touch sensors in serial
   test_if_touched(); prints touched sensors in serial
*/

int CAP_PIN[] = {15, 13, 12, 14, 27, 33};

bool touch_state[ZONES_NUMBER];

const bool PRESSED = 0;
const bool RELEASED = 1;

#define TOUCH1 GPIO_NUM_15
#define TOUCH2 GPIO_NUM_13
#define TOUCH3 GPIO_NUM_12
#define TOUCH4 GPIO_NUM_14
#define TOUCH5 GPIO_NUM_27
#define TOUCH6 GPIO_NUM_33


void setup_touch() {

  for (uint8_t pin = 0; pin < ZONES_NUMBER; pin++) {
    pinMode(CAP_PIN[pin], INPUT);
  }

  gpio_set_pull_mode(TOUCH1, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH2, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH3, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH4, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH5, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH6, GPIO_PULLUP_ONLY);

  Serial.println("Touch sensors all set up");
}

bool button_pressed(uint8_t btn_id) {

  return digitalRead(CAP_PIN[btn_id]) == PRESSED ? 1 : 0;
}

bool presence() {
  for (uint8_t i = 0; i < ZONES_NUMBER; i++) {
    if (button_pressed(i)) return 1;
  }
  
  return 0;
}


/*
 * Touch file containing functions for managing touch sensors in NAPaC project
 */

 /*
  * setup_touch(); sets up touch sensors with pull-up as inputs
  * touch_read_value(touch_id); touch_id = 1,...,8 returns capa value
  * capa_touched(touch_id); returns if capa is being touched (value < 5)
  * presence(); returns 1 if at least one sensor is being touched
  * test_touch_values(); prints the values of touch sensors in serial
  * test_if_touched(); prints touched sensors in serial
  */
  
//IO4, IO2, IO15, IO14, IO12, IO13 -- T0,T2,T3,T6,T5,T4
int CAP_PIN[] = {0,4, 2, 15, 14, 12, 13}; 

bool touch_state[nb_zones];

const bool PRESSED = 0;
const bool RELEASED = 1;

#define TOUCH1 GPIO_NUM_4
#define TOUCH2 GPIO_NUM_2
#define TOUCH3 GPIO_NUM_15
#define TOUCH4 GPIO_NUM_14
#define TOUCH5 GPIO_NUM_12
#define TOUCH6 GPIO_NUM_13


void setup_touch(){
  
  for (uint8_t pin=1; pin<nb_zones; pin++){
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

void print_state(){
  for (uint8_t i=1; i<nb_zones; i++){
    Serial.print(touch_state[i]);    
    Serial.print("\t");
  }
  Serial.print("\n");  
}


// Reads&returns the capacitive value read on corresponding pin
int touch_read_value(uint8_t touch_id){
  int read = digitalRead(CAP_PIN[touch_id]);
  touch_state[touch_id] = read;
  
  return read;
}

bool capa_touched(uint8_t touch_id){
  if (touch_id==2){
    return 0;
  }
  
  if (touch_read_value(touch_id) == PRESSED){
    Serial.print("Touch sensor touched! On sensor:");
    Serial.println(touch_id);
    return 1;
  }
  else{
    return 0;}
}

bool presence(){
  for (uint8_t i=1; i < nb_zones; i++){
    if (capa_touched(i)){ 
      return 1;
    }
  }
  return 0;
}

void test_touch_values(){
  for (uint8_t i=1; i < nb_zones; i++){
    touch_read_value(i);
  }
  print_state();
  delay(500);
}

void test_if_touched(){
  for (uint8_t i=1; i < nb_zones; i++){
    capa_touched(i);
    delay(100);
  }
}


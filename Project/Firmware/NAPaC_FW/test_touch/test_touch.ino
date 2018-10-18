// ESP32 Touch Test
//push button pinout for MS7 mini proto

//const uint8_t CAP_PIN[] = {0,4, 2, 15, 13}; //IO4, IO2, IO15, IO13 -- T0,T2,T3,T4
const int CAP_PIN[] = {0,4, 2, 15, 14, 12, 13}; //IO4, IO2, IO15, IO14, IO12, IO13 -- T0,T2,T3,T6,T5,T4

const uint8_t nb_capa = 7; //nb capa +1

const bool PRESSED = 0;
const bool RELEASED = 1;
bool touch_state[nb_capa];

#define TOUCH1 GPIO_NUM_4
#define TOUCH2 GPIO_NUM_2
#define TOUCH3 GPIO_NUM_15
#define TOUCH4 GPIO_NUM_14
#define TOUCH5 GPIO_NUM_12
#define TOUCH6 GPIO_NUM_13


/* Set the GPIO as a input */
//     gpio_set_direction(BUTTON1, GPIO_MODE_INPUT);


void print_state(){
  for (uint8_t i=1; i<nb_capa; i++){
    Serial.print(touch_state[i]);    
    Serial.print("\t");
  }
  Serial.print("\n");  
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("NAPaC Touch Test: implementation of buttons");

  for (uint8_t pin=1; pin<nb_capa; pin++){
    pinMode(CAP_PIN[pin], INPUT);
  }
  
  
  //gpio_pullup_en(TOUCH1);
  gpio_set_pull_mode(TOUCH1, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH2, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH3, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH4, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH5, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(TOUCH6, GPIO_PULLUP_ONLY);

  
//  for (int i=1; i < nb_capa; i++){
//    //gpio_pullup_en(i);
//  }
}

void loop()
{
  
  for (uint8_t i=1; i < nb_capa; i++){
    touch_state[i] = digitalRead(CAP_PIN[i]);
  }
  
  print_state();
  
  delay(100);
}

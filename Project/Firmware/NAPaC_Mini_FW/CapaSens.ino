/*
 * CapaSens file containing functions for managing textile capacitive 
 * touch sensors in NAPaC project
 */

 /*
  * setup_capa(); sets up capacitive touch sensors: reads initial value
  * touch_read_value(touch_id); touch_id = 1,...,8 returns capa value
  * capa_touched(touch_id); returns if capa is being touched (value < 5)
  * presence(); returns 1 if at least one sensor is being touched
  * test_touch_values(); prints the values of touch sensors in serial
  * test_if_touched(); prints touched sensors in serial
  */

const uint8_t CAP_PIN[] = {0,T0,T2,T3,T4}; //IO4, IO2, IO15, IO13
const uint8_t nb_capa = 5; //nb capa +1
bool touch_state[nb_capa];
int capa_init[nb_capa];

const bool PRESSED = 1;
const bool RELEASED = 0;

void setup_capa(){
  pinMode(32, INPUT);
  Serial.println("Initial capa values:");
  for (uint8_t i=1; i < nb_capa; i++){
    Serial.print(i);
    Serial.print("\t");
  }
 Serial.print("\n"); 
  for (uint8_t i=1; i < nb_capa; i++){
    pinMode(CAP_PIN[i], INPUT);
    capa_init[i] = touchRead(CAP_PIN[i]);
    Serial.print(capa_init[i]);
    Serial.print("\t");
  }
 Serial.print("\n"); 
}

// Reads&returns the capacitive value read on corresponding pin
int touch_read_value(uint8_t touch_id){
  int read = touchRead(CAP_PIN[touch_id]);
  return read;
}

bool capa_state(uint8_t touch_id){
  if (touch_read_value(touch_id) < 30){//capa_init[touch_id] - 20
    delay(50);
    if (touch_read_value(touch_id) < 30){ 
      touch_state[touch_id] = PRESSED;     
      return PRESSED;
    }
  }
  touch_state[touch_id] = RELEASED;
  return RELEASED;
}

bool capa_touched(uint8_t touch_id){
  if (capa_state(touch_id) == PRESSED){
    Serial.print("Touch sensor touched! On sensor:");
    Serial.print(touch_id);
    Serial.print("\t Read value:");
    Serial.println(touch_read_value(touch_id));
    return 1;
  }
  else{
    return 0;}
}

bool presence(){
  for (uint8_t i=1; i < nb_capa; i++){
    if (capa_touched(i)){ 
      return 1;
    }
  }
  return 0;
}

void test_touch_values(){
  
  Serial.println("Touch sensor values:");
  for (uint8_t i=1; i < nb_capa; i++){
    Serial.print("T");
    Serial.print(i);
    Serial.print("\t");
  }
 Serial.print("\n"); 
  for (uint8_t i=1; i < nb_capa; i++){
    pinMode(CAP_PIN[i], INPUT);
    capa_init[i] = touchRead(CAP_PIN[i]);
    Serial.print(capa_init[i]);
    Serial.print("\t");
  }
 Serial.print("\n"); 
  delay(500);
}

void test_if_touched(){
  //Serial.println("Test if touched");
  for (uint8_t i=1; i < nb_capa; i++){
    capa_touched(i);
    delay(100);
  }
}


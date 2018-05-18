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

const uint8_t CAP_PIN[] = {0,T0,T2,T3,T4,T5,T6,T7,T8};
const uint8_t nb_capa = 9; //nb capa +1
int capa_init[nb_capa];

void setup_capa(){
  for (uint8_t i=1; i <= nb_capa; i++){
    capa_init[i] = touchRead(CAP_PIN[i]);
  }
}

// Reads&returns the capacitive value read on corresponding pin
int touch_read_value(uint8_t touch_id){
  int read = touchRead(CAP_PIN[touch_id]);
  return read;
}

bool capa_touched(uint8_t touch_id){
  if (touch_read_value(touch_id) < 10){//capa_init[touch_id] - 20
    Serial.println("Touch sensor touched! On sensor:");
    Serial.println(touch_id);
    Serial.println(touch_read_value(touch_id));
    return 1;}
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
  for (uint8_t i=1; i < nb_capa; i++){
    Serial.println("Touch sensor read:");
    Serial.println(i);
    Serial.println(touch_read_value(i));
  }
  delay(500);
}

void test_if_touched(){
  for (uint8_t i=1; i < nb_capa; i++){
    capa_touched(i);
    delay(100);
  }
}


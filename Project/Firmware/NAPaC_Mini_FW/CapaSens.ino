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
uint16_t capa_off_avg[nb_capa];
int capa_init[nb_capa];
uint16_t THRESH = 100;

const bool PRESSED = 1;
const bool RELEASED = 0;

void setup_capa(){
  pinMode(32, INPUT);
  Serial.println("Initial capa values:");
  touchSetCycles(50000,0);
  for (uint8_t i=1; i < nb_capa; i++){
    Serial.print("T");
    Serial.print(i);
    Serial.print("\t");
  }
 Serial.print("\n "); 
  for (uint8_t i=1; i < nb_capa; i++){
    pinMode(CAP_PIN[i], INPUT);
    //capa_init[i] = touchRead(CAP_PIN[i]);
  
    uint8_t read_avg = touch_read_value(i);
    for (uint8_t c = 1 ; c < 10 ; c++){
      read_avg = (read_avg + touch_read_value(i));
    }
    //capa_init[i] = read_avg/10;
    
    Serial.print(capa_init[i]);
    Serial.print("\t ");
  }
 Serial.print("\n"); 
}

// Reads&returns the capacitive value read on corresponding pin
int touch_read_value(uint8_t touch_id){
  int read = touchRead(CAP_PIN[touch_id]);
  return read;
}

bool capa_state(uint8_t touch_id){
  //if (uint8_t read_avg = touch_read_value(touch_id) < THRESH){//capa_init[touch_id] - 20
    uint8_t read_avg = touch_read_value(touch_id);
    //Serial.print("Capa value read on T");
    //Serial.print(touch_id);
    //Serial.print(", initial value: ");
    Serial.print("i:");
    Serial.print(read_avg);
    Serial.print("/");
   //Serial.print(", avg value: ");
    for (uint8_t c = 1 ; c < 10 ; c++){
      read_avg = (read_avg + touch_read_value(touch_id));
    }
    //read_avg = read_avg/10;
    Serial.print("avg:");
    Serial.print(read_avg);
    if (read_avg < THRESH ){  //&& read_avg > 100
      touch_state[touch_id] = PRESSED;
      Serial.print("P");
      Serial.print("\t");
      //Serial.print("Touch sensor touched! On sensor:");
      //Serial.println(touch_id);     
      return PRESSED;
    }
    Serial.print("\t");
  
   
//    delay(50);
//    if (touch_read_value(touch_id) < THRESH){ 
//      touch_state[touch_id] = PRESSED;     
//      return PRESSED;
//    }
  
  touch_state[touch_id] = RELEASED;
  return RELEASED;
}

bool capa_touched(uint8_t touch_id){
  if (capa_state(touch_id) == PRESSED){
    Serial.print("Touch sensor touched! On sensor:");
    Serial.print(touch_id);
    //Serial.print("\t Read value:");
    //Serial.println(touch_read_value(touch_id));
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
    Serial.print("\t\t");
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
  Serial.println("Capa value read:");
  Serial.print("\t");
  
  for (uint8_t i=1; i < nb_capa; i++){
    Serial.print("T");
    Serial.print(i);
    Serial.print("\t\t");
  }
  Serial.print("\n\t");
  
  for (uint8_t i=1; i < nb_capa; i++){
    //capa_touched(i);
    capa_state(i);
    //delay(100);
  }
  Serial.print("\n");
}


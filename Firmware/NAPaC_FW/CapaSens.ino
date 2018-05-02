/*
 * CapaSens file containing functions for managing textile capacitive 
 * touch sensors in NAPaC project
 */

//enum capa_pads{0,T6,T2,T3};

//const uint8_t CAP1 = T6; //IO14
//const uint8_t CAP2 = T2; //IO02
//const uint8_t CAP3 = T3; //IO15

const uint8_t CAP_PIN[] = {0,T6,T2,T3};
uint8_t nb_capa = 4; //nb capa +1
int capa_init[4];

void setup_capa(){
  for (uint8_t i=1; i <= nb_capa; i++){
    capa_init[i] = touchRead(CAP_PIN[i]);
  }
}


// Reads&returns the capacitive value read on corresponding pin
int touch_read_value(uint8_t touch_id){
  uint8_t touch_pin;
  
  switch(touch_id){
    case 1: touch_pin = CAP_PIN[1]; break;
    case 2: touch_pin = CAP_PIN[2]; break;
    case 3: touch_pin = CAP_PIN[3]; break;
  }
  
  int read = touchRead(touch_pin);

  return read;
}

bool touched(uint8_t touch_id){
  int read = touch_read_value(touch_id);

  if (read < capa_init[touch_id] - 200){
    return 1;}
  else{
    return 0;}
}

bool presence(){
  for (uint8_t i=1; i <= nb_capa; i++){
    if (touched[i]) return 1;
  }
  return 0;
}

//void displayMonitorTouchSensors()
//{
//    Serial.print("RED : "); Serial.println(touchRead(RED_TOUCH));
//    Serial.print("YEL : "); Serial.println(touchRead(YEL_TOUCH));
//    Serial.print("GRN : "); Serial.println(touchRead(GRN_TOUCH));
//    Serial.println("");
//}


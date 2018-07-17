// ESP32 Touch Test
//capa pinout for MS7 mini proto

const uint8_t CAP_PIN[] = {0,T0,T2,T3,T4}; //IO4, IO2, IO15, IO13
const uint8_t nb_capa = 5; //nb capa +1
bool touch_state[nb_capa];
uint16_t capa_off_avg[nb_capa];
int capa_init[nb_capa];
uint16_t THRESH = 100;
 

const uint8_t buffer_size = 20; // 10 == 50ms
uint16_t Touch_Buffer[nb_capa][buffer_size];
uint16_t capa_buffer[nb_capa] = {0};

const bool PRESSED = 1;
const bool RELEASED = 0;
int capa_read[nb_capa];

void touch_measure_buffer(){
  for (uint8_t i=1; i<nb_capa; i++){ // boulce sur les T
    uint16_t avg_value = 0;
    uint8_t c = 1;
    for (uint8_t j = buffer_size -1; j>0; j--){ // boucle sur le buffer
      if (j != 0){
        Touch_Buffer[i][j] = Touch_Buffer[i][j-1];
        avg_value += Touch_Buffer[i][j];
        c++;
      }
//      else if (Touch_Buffer[i][j] = touchRead(CAP_PIN[i]) ){
//        avg_value += Touch_Buffer[i][j];
//        c++;
//      }
      //avg_value += Touch_Buffer[i][j];
    }
   Touch_Buffer[i][0] = touchRead(CAP_PIN[i]);
   avg_value += Touch_Buffer[i][0];
   c++;
    
   capa_buffer[i] = avg_value/c;
  }
}

//for (i=0; i<nb_capa; i++){
//    for (j=0; j<buffer_size; j++){
//    }
//}

void print_buffer(){
    for (uint8_t i=1; i<nb_capa; i++){
    Serial.print("T");
    Serial.print(i);
    Serial.print("\t");
      for (uint8_t j=0; j<buffer_size; j++){
        Serial.print(touchRead(CAP_PIN[i]));
        //Serial.print(Touch_Buffer[i][j]);
        Serial.print("\t");
      }
    Serial.print("\n");
  } 
  Serial.print("\n");
}

void print_plot(){
  for (uint8_t i=1; i<nb_capa; i++){
    Serial.print(capa_buffer[i]);

//    if (uint16_t value = Touch_Buffer[i][0]){
//      Serial.print(value);
//    }
//    else{
//      Serial.print("\t");
//    }
    
    //Serial.print(Touch_Buffer[i][0]);
    Serial.print("\t");
  }
  Serial.print("\n");  
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("NAPaC Touch Test");

  touchSetCycles(50000,0);

//  for (uint8_t i=1; i < nb_capa; i++){
//    pinMode(CAP_PIN[i], INPUT);
//  }

}

void loop()
{
//    for (uint8_t i=1; i < nb_capa; i++){
//    Serial.print("T");  
//    Serial.print(i);
//    Serial.print("\t");
//  }
//  Serial.print("\n");
//  
//  for (uint8_t i=1; i < nb_capa; i++){
//    //Serial.print(touchRead(CAP_PIN[i]));
//    Serial.print("\t");
//  }
//  Serial.print("\n");
//  

  touch_measure_buffer();
  print_plot();
  print_buffer(); 
  
  delay(100);
}



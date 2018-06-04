// ESP32 Touch Test
//capa pinout for MS4 prototype

const uint8_t CAP_PIN[] = {0,T0,T2,T3,T4,T5,T6,T7,T8};
const uint8_t nb_capa = 9; //nb capa +1
int capa_read[nb_capa];

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("NAPaC Touch Test");

  
  for (uint8_t i=1; i < nb_capa; i++){
    pinMode(CAP_PIN[i], INPUT);
  }
}

void loop()
{
    for (uint8_t i=1; i < nb_capa; i++){
    Serial.print(i);
    Serial.print("\t");
  }
  Serial.print("\n");
  
  for (uint8_t i=1; i < nb_capa; i++){
    
    Serial.print(touchRead(CAP_PIN[i]));
    Serial.print("\t");
  }
  Serial.print("\n");
  
  delay(500);
}

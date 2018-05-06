#include <driver/adc.h>

int sensor = 0;
int i=0;

int readSensor(){
  adc1_config_width(ADC_WIDTH_BIT_10);   //Range 0-1023 
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_6);  //ADC_ATTEN_DB_11 = 0-3,6V
  return adc1_get_raw( ADC1_CHANNEL_6 ); //Read analog
}

void setup() {
  Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor
   
   //analogSetAttenuation(ADC_6db);
   //analogReadResolution(11);  
  
  // put your setup code here, to run once:
  Serial.print("running on ADC channel 0 \n");
}

void bend_test(){
  Serial.println("bend sensor testing\n");
  delay(2000);
  
  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<20; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor gently pressed\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor strongly pressed\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor lightly bent\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }
  
  Serial.println("sensor strongly bent\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }
  
  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<10; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("end of test\n");

}

void loop() {
  //bend_test();
  stretch_test();
}

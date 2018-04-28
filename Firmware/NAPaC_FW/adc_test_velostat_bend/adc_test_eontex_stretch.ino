void stretch_test(){
  Serial.println("stretch sensor testing\n");
  delay(2000);
  
  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<15; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("medium stretch\n");
  delay(1000);
  for ( i=0; i<15; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<15; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("max stretch\n");
  delay(1000);
  for ( i=0; i<15; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

  Serial.println("sensor untouched\n");
  delay(1000);
  for ( i=0; i<15; i++){
    sensor = readSensor();
    Serial.println(sensor);
    delay(500);
  }

 Serial.println("end of test\n");
}


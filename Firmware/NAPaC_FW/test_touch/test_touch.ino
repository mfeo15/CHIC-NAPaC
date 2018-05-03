// ESP32 Touch Test
//capa pinout for MS4 prototype

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop()
{
  Serial.println("Touch pad 1:");
  Serial.println(touchRead(T6));  // get value using T0
  Serial.println("Touch pad 2:");
  Serial.println(touchRead(T2));  // get value using T0
  Serial.println("Touch pad 3:");
  Serial.println(touchRead(T3));  // get value using T0
  delay(1000);
}

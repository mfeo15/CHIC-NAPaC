// ESP32 Touch Test
// Just test touch pin to activate corresponding LED

/*
 *  Edited code looking horrible to demonstrate neopixels on esp32
 *  Capa pads on soft paw turn on neopixels
 *  Random colours may turn on for unknown reasons
 */

void setup()
{
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor

    setup_pixels();

    Serial.println();
    Serial.println();
    Serial.println("ESP32 Sensors Touch Test");
    Serial.println();
    Serial.println();
}

void loop()
{
    readTouchSensor();
   
    //delay(1000);
}

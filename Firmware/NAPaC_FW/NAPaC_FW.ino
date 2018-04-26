// ESP32 Touch Test
// Just test touch pin to activate corresponding LED

/*
 *  Edited code looking horrible to demonstrate neopixels on esp32
 *  Capa pads on soft paw turn on neopixels
 *  Random colours may turn on for unknown reasons
 */

int incomingByte = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor

    setup_pixels();
    //setup_wifi();
    hello();
}

void loop()
{
//    if (Serial.available() > 0){ //not working 
//      incomingByte = Serial.read();
//      Serial.println("received:");
//      Serial.println(incomingByte, DEC);
//    }
    
    readTouchSensor();
    //displayMonitorTouchSensors();

    //server loop
//    check_to_activateLED();
//    readTouchSensor();
//    check_to_close_ServerConnection();
   
    //delay(1000);
}

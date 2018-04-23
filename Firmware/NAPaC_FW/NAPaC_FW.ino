// ESP32 Touch Test
// Just test touch pin to activate corresponding LED

/*
 *  Edited code looking horrible to demonstrate neopixels on esp32
 *  Capa pads on soft paw turn on neopixels
 *  Random colours may turn on for unknown reasons
 */

#include <NeoPixelBus.h> 


const int RED_LED = 0;
const int YEL_LED = 2;
const int GRN_LED = 1;
const uint16_t PixelCount = 3;  
const uint8_t PixelPin = 23;  

#define colorSaturation 50 // saturation of color constants
RgbColor red(colorSaturation, 0, 0);
RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor black(0, 0, 0);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

uint8_t red_state=0;
uint8_t green_state=0;
uint8_t yellow_state=0;

const int RED_TOUCH = T3; //IO15
const int YEL_TOUCH = T6; //IO14
const int GRN_TOUCH = T4; //IO13

const int THRESHOLD_RED = 10; //to compare first and current sensor input
const int THRESHOLD_YEL = 30; //to compare first and current sensor input
const int THRESHOLD_GRN = 25; //to compare first and current sensor input

const int MAX_DIFF = 3; //to compare previous and current sensor input

void setup()
{
    Serial.begin(115200);
    delay(1000); // give me time to bring up serial monitor
    
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(PixelPin, OUTPUT);
    //pinMode(YEL_LED, OUTPUT);
    //pinMode(GRN_LED, OUTPUT);

    strip.Begin();
    strip.SetPixelColor(RED_LED, black);
    strip.Show();

    Serial.println();
    Serial.println();
    Serial.println("ESP32 Sensors Touch Test");
    Serial.println();
    Serial.println();
}

void toggleLED(String color)
{
    //Serial.print("Color of LED to light on: "); Serial.println(color);
    
    if (color == "RED") 
    {
        Serial.println("Toggling RED_LED");
        if (red_state == 0){
            strip.SetPixelColor(RED_LED, red);  // turn on the LED
            Serial.print("Red On\n");
            red_state = 1;}
        else{
            strip.SetPixelColor(RED_LED, black);  // turn on the LED
            Serial.print("Red Off\n");
            red_state =0;}
        strip.Show();
        return;
    }
  
    if (color == "GRN") 
    {
        Serial.println("Toggling GRN_LED");
        if (green_state == 0){
            strip.SetPixelColor(GRN_LED, green);  // turn on the LED
            Serial.print("Green On\n");
            green_state = 1;}
        else{
            strip.SetPixelColor(GRN_LED, black);  // turn on the LED
            Serial.print("Green Off\n");
            green_state =0;}
        strip.Show();
        return;
    }
  
    if (color == "YEL") 
    {
        Serial.println("Toggling YEL_LED");
        if (yellow_state == 0){
            strip.SetPixelColor(YEL_LED, yellow);  // turn on the LED
            Serial.print("Yellow On\n");
            yellow_state = 1;}
        else{
            strip.SetPixelColor(YEL_LED, black);  // turn on the LED
            Serial.print("Yellow Off\n");
            yellow_state = 0;}
        strip.Show();
        return;
    }
}

void readTouchSensor()
{
    static bool first_measure = 1; 
    static unsigned int counter, debug_measurement;
    static int first_read_RED, first_read_YEL, first_read_GRN;
    static int prev_read_RED, prev_read_YEL, prev_read_GRN;
    
    int current_read_RED, current_read_YEL, current_read_GRN;

    if (first_measure == 1)
    {
        //LED initialisation
        strip.SetPixelColor(0, red);
        strip.Show();
        
        //Initialization
        first_read_RED = touchRead(RED_TOUCH);
        first_read_YEL = touchRead(YEL_TOUCH);
        first_read_GRN = touchRead(GRN_TOUCH);
            
        first_measure = 0;
        counter = 0;
        debug_measurement = 0;

      
        return;
    }

    else if (counter > 1000000/4)
    {
        //Serial.print("Comparing previous_read_RED and current_read_RED with THRESHOLD "); Serial.println(THRESHOLD);
//        Serial.println(debug_measurement);
//        displayMonitorTouchSensors();
        
        current_read_RED = touchRead(RED_TOUCH);
        current_read_YEL = touchRead(YEL_TOUCH);
        current_read_GRN = touchRead(GRN_TOUCH);
        
        if ( current_read_RED < THRESHOLD_RED ){
                toggleLED("RED");
        }
          

        else if ( current_read_YEL < THRESHOLD_RED )
        {
                toggleLED("YEL");
        }
       

        else if (current_read_GRN < THRESHOLD_RED)
        {
                toggleLED("GRN");  
        }

       prev_read_RED = current_read_RED;
       prev_read_YEL = current_read_YEL;
       prev_read_GRN = current_read_GRN;
       
       counter = 0;
       debug_measurement++;
    } 

    counter++;
}

void displayMonitorTouchSensors()
{
    Serial.print("RED : "); Serial.println(touchRead(RED_TOUCH));
    Serial.print("YEL : "); Serial.println(touchRead(YEL_TOUCH));
    Serial.print("GRN : "); Serial.println(touchRead(GRN_TOUCH));
    Serial.println("");
}

void loop()
{
    readTouchSensor();
   
    //delay(1000);
}

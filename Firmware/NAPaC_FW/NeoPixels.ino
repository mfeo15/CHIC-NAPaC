/*
 * NeoPixels file containing functions for managing NeoPixels in NAPaC project
 */

#include <NeoPixelBus.h> 

const int RED_LED = 0;
const int YEL_LED = 2;
const int GRN_LED = 1;
const uint16_t PixelCount = 3;  
const uint8_t PixelPin = 23;  

uint8_t red_state=0;
uint8_t green_state=0;
uint8_t yellow_state=0;

#define colorSaturation 50 // saturation of color constants
RgbColor red(colorSaturation, 0, 0);
RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor black(0, 0, 0);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void setup_pixels(void){
    pinMode(PixelPin, OUTPUT);
    strip.Begin();
    strip.Show();
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




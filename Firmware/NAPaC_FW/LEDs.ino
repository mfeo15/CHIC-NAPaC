/*
 * CapaSens file containing functions for managing SK9822
 * touch sensors in NAPaC project
 */


#include <APA102.h>
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

// Define which pins to use.
const uint8_t dataPin = 0;
const uint8_t clockPin = 4;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Define LEDs on the plush toy
const uint16_t ledCount = 1;


// Create a buffer for holding the colors (3 bytes per color).
rgb_color colours[ledCount];

//Colour alphabet
//enum colours{off,red,green,blue,purple,yellow};
uint8_t max_bright = 255;
const uint8_t brightness = 1;
rgb_color rgb_black = {0, 0, 0};
rgb_color rgb_red = {max_bright, 0, 0};
rgb_color rgb_green = {0, max_bright, 0};
rgb_color rgb_blue = {0, 0, max_bright};
rgb_color rgb_purple = {max_bright, 0, max_bright};
rgb_color rgb_yellow = {max_bright, max_bright, 0};

// Set the brightness to use (the maximum is 31).


void setup_LEDs(void){
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (uint8_t i = 0; i < ledCount; i++)
  {
    colours[i] = rgb_color(0,0,255);
  }
  ledStrip.write(colours, ledCount, brightness);
}

void set_LED(uint8_t LEDid, uint8_t colour){
  switch(colour){
    case off: colours[LEDid] = rgb_black; break;
    case red: colours[LEDid] = rgb_red; break;
    case green: colours[LEDid] = rgb_green; break;
    case blue: colours[LEDid] = rgb_blue; break;
    case purple: colours[LEDid] = rgb_purple; break;
    case yellow: colours[LEDid] = rgb_yellow; break;
  }
  ledStrip.write(colours, ledCount, brightness);
}

void blink_LED(uint8_t LEDid, uint8_t colour){
  set_LED(LEDid, colour);
  delay(200);
  set_LED(LEDid, off);
  delay(200);
  set_LED(LEDid, colour);
  delay(200);
  set_LED(LEDid, off);
  delay(200);
}



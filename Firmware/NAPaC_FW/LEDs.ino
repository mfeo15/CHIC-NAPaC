/*
 * LEDs file containing functions for managing SK9822
 */


#include <APA102.h>
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

// Define which pins to use.
const uint8_t dataPin = 0;
const uint8_t clockPin = 4;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

//  second LED strip for MS4
  const uint8_t dataPin2 = 13;
  const uint8_t clockPin2 = 12;
  APA102<dataPin2, clockPin2> ledStrip2;

// Define LEDs on the plush toy
const uint16_t ledCount = 1;
const uint16_t ledCount2 = 1;


// Create a buffer for holding the colors (3 bytes per color).
rgb_color colours[ledCount];
rgb_color colours2[ledCount2];

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

  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);

  for (uint8_t i = 0; i < ledCount; i++)
  {
    colours[i] = rgb_color(0,0,0);
    colours2[i] = rgb_color(0,0,0);
  }
  ledStrip.write(colours, ledCount, brightness);
  ledStrip2.write(colours2, ledCount2, brightness);
}

void set_LED(uint8_t LEDid, uint8_t colour){
  if (LEDid == 10){
    switch(colour){
      case off: colours[0] = rgb_black; break;
      case red: colours[0] = rgb_red; break;
      case green: colours[0] = rgb_green; break;
      case blue: colours[0] = rgb_blue; break;
      case purple: colours[0] = rgb_purple; break;
      case yellow: colours[0] = rgb_yellow; break;
    } 
    ledStrip2.write(colours2, ledCount2, 20);
  }
   else{
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



/*
   LEDs file containing functions for managing SK9822
*/

/*
   setup_LEDs(); sets up LED strips and turns all LEDs off
   set_LED(LEDid, rgb_colour); colour = rgb_off/_red/_blue... turns on one individual LED
   blink_LED(LEDid, rgb_colour); blinks twice an individual LED (1 second)
   test_LEDs(); turns on heart LED in all colours one after another then blinks all LEDs
                one after another from 0 to 9
   all_LED_off(); turns off all game LEDs

   game_set_LED(LEDid, LED_mode); Sets LED during game according to mode on_parent/_kid
                                   turn on/off or blink
*/

#include <APA102.h>
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

// Define which pins to use for presence LED strip and create LED strip object
const uint8_t dataPin = 4;
const uint8_t clockPin = 2;
APA102<dataPin, clockPin> presenceLedStrip;

// Define counter of presence LEDs on the plush toy (2, one for each side of the toy)
const uint16_t presenceLedCount = 2;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colours[presenceLedCount];

//Colour alphabet
uint8_t max_bright = 255;
const uint8_t brightness = 10; // Set the brightness to use (the maximum is 31).
rgb_color rgb_off = {0, 0, 0};
rgb_color rgb_white = {max_bright, max_bright, max_bright};
rgb_color rgb_red = {max_bright, 0, 0};
rgb_color rgb_green = {0, max_bright, 0};
rgb_color rgb_blue = {0, 0, max_bright};
rgb_color rgb_purple = {max_bright, 0, max_bright};
rgb_color rgb_yellow = {max_bright, max_bright, 0};


void setup_presence_LEDs() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (uint8_t i = 1; i < presenceLedCount; i++) {
    colours[i] = rgb_off;
    zone_status[i] = 0;
  }

  presenceLedStrip.write(colours, presenceLedCount, brightness);
}

void turnOffPresenceLEDs() {
  for (uint8_t i = 1; i < presenceLedCount; i++) {
    colours[i] = rgb_off;
    zone_status[i] = 0;
  }

  presenceLedStrip.write(colours, presenceLedCount, brightness);
}

/*
void game_set_LED(uint8_t LEDid, uint8_t LED_mode) {
  switch (LED_mode) {

    case LED_off:
      set_LED(LEDid, off);
      zone_status[LEDid] = LED_off;
      break;

    case on_parent:
      if (zone_status[LEDid] == on_parent) {
        blink_LED(LEDid, white);
      }
      set_LED(LEDid, parent);
      zone_status[LEDid] = on_parent;
      break;

    case on_kid:
      if (zone_status[LEDid] == on_kid) {
        blink_LED(LEDid, white);
      }
      set_LED(LEDid, kid);
      zone_status[LEDid] = on_kid;
      break;
  }
}
*/

void set_presence_LEDs(uint8_t colour) {

  switch (colour) {
    case off:
      colours[0] = rgb_off;
      colours[1] = rgb_off;
      break;
    case white:
      colours[0] = rgb_white;
      colours[1] = rgb_white;
      break;
    case red:
      colours[0] = rgb_red;
      colours[1] = rgb_red;
      break;
    case green:
      colours[0] = rgb_green;
      colours[1] = rgb_green;
      break;
    case blue:
      colours[0] = rgb_blue;
      colours[1] = rgb_blue;
      break;
    case purple:
      colours[0] = rgb_purple;
      colours[1] = rgb_purple;
      break;
    case yellow:
      colours[0] = rgb_yellow;
      colours[1] = rgb_yellow;
      break;
  }

  presenceLedStrip.write(colours, presenceLedCount, brightness);
}

void blink_presence_LEDs(uint8_t colour) {
  set_presence_LEDs(colour);
  delay(250);
  set_presence_LEDs(off);
  delay(250);
  set_presence_LEDs(colour);
  delay(250);
  set_presence_LEDs(off);
}

void test_presence_LEDs() {
  set_presence_LEDs(red);
  delay(1000);
  set_presence_LEDs(green);
  delay(1000);
  set_presence_LEDs(blue);
  delay(1000);
  set_presence_LEDs(purple);
  delay(1000);
  set_presence_LEDs(yellow);
  delay(1000);
  set_presence_LEDs(off);

  blink_presence_LEDs(red);
}


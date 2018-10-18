/*
 * LEDs file containing functions for managing SK9822
 */

/*
 * setup_LEDs(); sets up LED strips and turns all LEDs off
 * set_LED(LEDid, rgb_colour); colour = rgb_off/_red/_blue... turns on one individual LED
 * blink_LED(LEDid, rgb_colour); blinks twice an individual LED (1 second)
 * test_LEDs(); turns on heart LED in all colours one after another then blinks all LEDs
 *              one after another from 0 to 9
 * all_LED_off(); turns off all game LEDs
 * 
 * game_set_LED(LEDid, LED_mode); Sets LED during game according to mode on_parent/_kid
 *                                 turn on/off or blink
 */

#include <APA102.h>
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

// Define which pins to use for LED strips and create LED strip object
const uint8_t dataPin1 = 22;
const uint8_t clockPin1 = 23;
APA102<dataPin1, clockPin1> ledStrip1; 

const uint8_t dataPin2 = 25;
const uint8_t clockPin2 = 26;
APA102<dataPin2, clockPin2> ledStrip2;

// Define LEDs on the plush toy
const uint16_t ledCount1 = 5;
const uint16_t ledCount2 = 2;
const uint16_t ledCount = ledCount1 + ledCount2;

//uint8_t LED_status[ledCount];


// Create a buffer for holding the colors (3 bytes per color).
rgb_color colours1[ledCount1];
rgb_color colours2[ledCount2];

//Colour alphabet
//enum colours{off,red,green,blue,purple,yellow};
uint8_t max_bright = 255;
const uint8_t brightness = 31; // Set the brightness to use (the maximum is 31).
rgb_color rgb_off = {0, 0, 0};
rgb_color rgb_white = {max_bright, max_bright, max_bright};
rgb_color rgb_red = {max_bright, 0, 0};
rgb_color rgb_green = {0, max_bright, 0};
rgb_color rgb_blue = {0, 0, max_bright};
rgb_color rgb_purple = {max_bright, 0, max_bright};
rgb_color rgb_yellow = {max_bright, max_bright, 0};

rgb_color parent_colour = rgb_green;
rgb_color kid_colour    = rgb_white;


void setup_LEDs(void){
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);

  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  
  uint8_t j = 0;
  for (uint8_t i = 1; i < ledCount; i++)
  {
    if (i<ledCount1){
      colours1[i] = rgb_off;}
    else{
      j = i - ledCount1;
      colours2[j] = rgb_off;
    }
    //LED_status[i]=0;
    zone_status[i]=0;
  }
  ledStrip1.write(colours1, ledCount1, brightness);
  ledStrip2.write(colours2, ledCount2, brightness);
}

void all_LED_off(){
  uint8_t j = 0;
  for (uint8_t i = 0; i < ledCount; i++)
  {
    if (i<ledCount1){
      colours1[i] = rgb_off;}
    else{
      j = i - ledCount1;
      colours2[j] = rgb_off;
    }
    //LED_status[i]=0;
    zone_status[i]=0;
  }
  ledStrip1.write(colours1, ledCount1, brightness);
  ledStrip2.write(colours2, ledCount2, brightness);
}

void game_set_LED(uint8_t LEDid, uint8_t LED_mode){
  switch(LED_mode){
    
      case LED_off: 
        set_LED(LEDid, off); 
        zone_status[LEDid] = LED_off;
        break;
        
      case on_parent: 
        if(zone_status[LEDid] == on_parent){
          blink_LED(LEDid, white);
        }
        set_LED(LEDid, parent);
        zone_status[LEDid]=on_parent;
        break;
        
      case on_kid: 
        if(zone_status[LEDid] == on_kid){
            blink_LED(LEDid, white);
          }
        set_LED(LEDid, kid);
        zone_status[LEDid]=on_kid;  
        break;
  }
}

void set_LED(uint8_t LEDid, uint8_t colour){
  zone_status[LEDid]=1;
  if (LEDid < ledCount1){
    switch(colour){
      case off: colours1[LEDid] = rgb_off; zone_status[LEDid] = LED_off; break;
      case white: colours1[LEDid] = rgb_white; break;
      case red: colours1[LEDid] = rgb_red; break;
      case green: colours1[LEDid] = rgb_green; break;
      case blue: colours1[LEDid] = rgb_blue; break;
      case purple: colours1[LEDid] = rgb_purple; break;
      case yellow: colours1[LEDid] = rgb_yellow; break;
      case parent: colours1[LEDid] = parent_colour; break;
      case kid: colours1[LEDid] = kid_colour; break;
    } 
    ledStrip1.write(colours1, ledCount1, brightness);
    if (LEDid == 0 ){
      ledStrip1.write(colours1, ledCount1, 31);//stronger brightness for heart LED
    }
  }
   else{
    LEDid = LEDid - ledCount1;
    switch(colour){
      case off: colours2[LEDid] = rgb_off; zone_status[LEDid] = LED_off; break;
      case white: colours2[LEDid] = rgb_white; break;
      case red: colours2[LEDid] = rgb_red; break;
      case green: colours2[LEDid] = rgb_green; break;
      case blue: colours2[LEDid] = rgb_blue; break;
      case purple: colours2[LEDid] = rgb_purple; break;
      case yellow: colours2[LEDid] = rgb_yellow; break;
      case parent: colours2[LEDid] = parent_colour; break;
      case kid: colours2[LEDid] = kid_colour; break;
    } 
    ledStrip2.write(colours2, ledCount2, brightness);
  }
}

void blink_LED(uint8_t LEDid, uint8_t colour){
  set_LED(LEDid, colour);
  delay(250);
  set_LED(LEDid, off);
  delay(250);
  set_LED(LEDid, colour);
  delay(250);
  set_LED(LEDid, off);
  delay(250);
}

void test_LEDs(){
  set_LED(0, red);
  delay(1000);
  set_LED(0, green);
  delay(1000);
  set_LED(0, blue);
  delay(1000);
  set_LED(0, purple);
  delay(1000);
  set_LED(0, yellow);
  delay(1000);
  set_LED(0, off);  
  
  for (uint8_t i = 0; i < ledCount; i++)
  {
    blink_LED(i, red);
  }
}


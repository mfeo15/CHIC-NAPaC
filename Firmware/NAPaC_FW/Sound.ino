/*
 * Sound file containing functions for managing piezo in NAPaC project
 * Written by Chloe Rosanna Dickson, spring 2018
 * Arduino tone function not yet implemented on ESP32 -> workaround using LED PWM functions 
 * Example: https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/ 
 */

 /*
  * setup_sound(); sets pin output for piezo on pin IO21
  * void sound_test(); Sound test: plays do-re-mi-fa-sol-la-si-Do
  */

#define Do 261
#define Do_Di 277
#define Re 294
#define Re_Di 311
#define Mi 329
#define Fa 349
#define Fa_Di 370
#define Sol 392
#define Sol_Di 415
#define La 440
#define La_Di 466
#define Si 493
#define DO 523

const uint8_t soundPin = 21;
const int gamme[]={Do,Re,Mi,Fa,Sol,La,Si,DO};

int freq = 2000;
int channel = 0;
int resolution = 8;


void setup_sound(){
  pinMode(soundPin, OUTPUT);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(21, channel);
}

// Sound test: plays do-re-mi-fa-sol-la-si-Do
void sound_test(){ 
  for (uint8_t i=0; i<8; i++){
    ledcWriteTone(channel, gamme[i]);
    delay(500);
    ledcWriteTone(channel, 0);
    delay(500);
  }
  ledcWriteTone(channel, 0);
}


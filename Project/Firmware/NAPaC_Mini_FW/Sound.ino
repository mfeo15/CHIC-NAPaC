/*
 * Sound file containing functions for managing piezo in NAPaC project
 * Written by Chloe Rosanna Dickson, spring 2018
 * Arduino tone function not yet implemented on ESP32 -> workaround using LED PWM functions 
 * Example: https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/ 
 */

 /*
  * setup_sound(); sets pin output for piezo on pin IO21
  * play_tone(tone); Plays tone for 200ms
  * play_tone_short(tone); Plays tone for 70ms
  * 
  * sound_test(); Sound test: plays do-re-mi-fa-sol-la-si-Do
  * mario(); plays mario tune
  */

#define Do 523
#define Re 587
#define Mi 659
#define Fa 698
#define Sol 784
#define La 880
#define Si 988
#define DO 1047

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


void play_tone(int tone){
  ledcWriteTone(channel, gamme[tone-1]);
  delay(200);
  ledcWriteTone(channel, 0);
}

void play_tone_short(int tone){
  ledcWriteTone(channel, gamme[tone-1]);
  delay(70);
  ledcWriteTone(channel, 0);
}

// Sound test: plays do-re-mi-fa-sol-la-si-Do
void sound_test(){ 
  for (uint8_t i=1; i <= 8; i++){
    play_tone(i);
    delay(100);
  }
  ledcWriteTone(channel, 0);
}



void mario(){
  ledcWriteTone(channel,660);
  delay(150);
  ledcWriteTone(channel, 0);
  delay(100);
  ledcWriteTone(channel,660);
  delay(150);
  ledcWriteTone(channel, 0);
  delay(100);
  ledcWriteTone(channel,660);
  delay(150);
  ledcWriteTone(channel, 0);
  delay(100);
  ledcWriteTone(channel,510);
  delay(100);
  ledcWriteTone(channel, 0);
  delay(100);
  ledcWriteTone(channel,660);
  delay(150);
  ledcWriteTone(channel, 0);
  delay(100);
  ledcWriteTone(channel,770);
  delay(300);
  ledcWriteTone(channel, 0);
}

void sound_game_on(){
  ledcWriteTone(channel, Do);
  delay(100);
  ledcWriteTone(channel, Mi);
  delay(100);
  ledcWriteTone(channel, Sol);
  delay(100);
  ledcWriteTone(channel, 0);
}


void sound_game_off(){
  ledcWriteTone(channel, Sol);
  delay(100);
  ledcWriteTone(channel, Mi);
  delay(100);
  ledcWriteTone(channel, Do);
  delay(100);
  ledcWriteTone(channel, 0);
}


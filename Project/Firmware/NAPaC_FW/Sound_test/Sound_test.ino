/*
 *  Arduino tone function not yt implemented on ESP32 -> workaround using LED PWM functions 
 *  Example: https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/ 
 */

//#define Do 261
//#define Do_Di 277
//#define Re 294
//#define Re_Di 311
//#define Mi 329
//#define Fa 349
//#define Fa_Di 370
//#define Sol 392
//#define Sol_Di 415
//#define La 440
//#define La_Di 466
//#define Si 493
//#define DO 523

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

double frequency_calculator (float note) {
  //determines the frequency of do (-10), re (-8), mi (-6), fa (-5), sol(-3), la (-1), si (1) and do (1.5)
  //see reference here: https://www.deleze.name/marcel/physique/musique/Frequences.pdf
  const double r = 1.05946;
  double frequency = 440.0 * pow(r, note);
  
  return frequency;
}

void sound_test_simone(){
  for (int8_t i = -10; i <= 4; i += 2) {
    float note = i;
    if (i >= -4 && i <= 2) note = i -1;
    if (i == 4) note = 1.6;
    ledcWriteTone(channel, frequency_calculator(note));    //double ledcWriteTone(uint8_t channel, double freq);
    delay(500);
  }

  ledcWriteTone(channel, 0);
}

void sound_test_techtuto(){
  ledcWriteTone(channel, 2000);
 
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle=dutyCycle+10){
 
    Serial.println(dutyCycle);
 
    ledcWrite(channel, dutyCycle);
    delay(1000);
  }
 
    ledcWrite(channel, 125);
   
    for (int freq = 255; freq < 10000; freq = freq + 250){
   
       Serial.println(freq);
   
       ledcWriteTone(channel, freq);
       delay(1000);
    }
}

void sound_test_chloe(){
  for (uint8_t i=0; i<8; i++){
    ledcWriteTone(channel, gamme[i]);
    delay(500);
    ledcWriteTone(channel, 0);
    delay(500);
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


void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  pinMode(soundPin, OUTPUT);

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(21, channel);

  //sound_test_techtuto();
  sound_test_chloe();
  mario();

}

void loop() {
  // put your main code here, to run repeatedly:

}





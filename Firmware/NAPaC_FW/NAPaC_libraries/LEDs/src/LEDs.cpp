/*
	LEDs.h - Library for NAPaC Toygether project, CHIC 2018
	Created by Chloe Dickson, April 2018
*/

#include "Arduino.h"
#include <WS2812.h>
#include "LEDs.h"

LEDs::Neopixel(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void LEDs::on(int mode)
{
	//blablabla turn LED on
}
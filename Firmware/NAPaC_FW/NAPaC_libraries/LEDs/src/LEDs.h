/*
	LEDs.h - Library for NAPaC Toygether project, CHIC 2018
	Created by Chloe Dickson, April 2018
*/

#ifndef	LEDs_h
#define	LEDs_h

class Neopixel
{
	public:
		Neopixel(int pin); //"gpio_num_t gpioPin" instead of "int pin"
		void on(int mode);
	private:
		int _pin;
};


#endif

#ifndef ARDUINO_BUZZER_H
#define ARDUINO_BUZZER_H
#include <Arduino.h>

class Buzzer  
{
	private:
  		byte pin;
	public:


		Buzzer( byte pin);
		~Buzzer();
		void buzz();
		void multipleBuzz(int count);
		void delay(int count);
		void init();
		void off();

};
#endif

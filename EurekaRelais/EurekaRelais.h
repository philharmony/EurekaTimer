// EurekaRelais.h

#ifndef _EUREKARELAIS_h
#define _EUREKARELAIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EurekaRelaisClass
{
 private:
	 int _pin;
	 void _set(int state);
	 int _get();
 public:
	EurekaRelaisClass(int pin);
	void set(int state);
	void seton();
	void setoff();
	int state();
	bool isOn();
	bool isOff();
};

#endif


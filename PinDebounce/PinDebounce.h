// PinDebounce.h

#ifndef _PINDEBOUNCE_h
#define _PINDEBOUNCE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PinDebounceClass
{
 private:
	 int _pin;
	 int _stateOld;
	 int _state;
	 unsigned long _timeDebounce;
	 unsigned long _lastChecked;
	 void _debounce();
 public:
	 PinDebounceClass(int pin, unsigned long timeDebounce = 50);
	 void debounce();
	 int state();
};

#endif


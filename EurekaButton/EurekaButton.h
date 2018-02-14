// EurekaButton.h

#ifndef _EUREKABUTTON_h
#define _EUREKABUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PinDebounce.h"

class EurekaButtonClass : private PinDebounceClass
{
 private:
	 int _event;	//clicked, long, none
	 int _stateOld;
	 bool _holdset;
	 unsigned long _lastChange;
	 unsigned long _timeHold;
	 unsigned long _timeDown;
	 unsigned long _timeDebounce;
	 void _reset();

 public:
	 EurekaButtonClass(int pin, unsigned long timeDebounce = 50, unsigned long timeHold = 1000);
	 void update();
	 int state();
	 int event();
	 bool clicked();
	 bool held();
	 bool released();
	 void reset();
};

#endif


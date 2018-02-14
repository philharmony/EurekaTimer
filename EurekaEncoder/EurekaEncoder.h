// EurekaEncoder.h

#ifndef _EUREKAENCODER_h
#define _EUREKAENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PinDebounce.h"
#include "EurekaButton.h"

class _Button : public EurekaButtonClass{
public:
	_Button(int pin, unsigned long timeDebounce = 50, unsigned long timeHold = 1000) : EurekaButtonClass(pin, timeDebounce, timeHold) {};
};
class _portA : public PinDebounceClass{
public:
	_portA(int pin, unsigned long timeDebounce = 0) : PinDebounceClass(pin, timeDebounce) {};
};
class _portB : public PinDebounceClass {
public:
	_portB(int pin, unsigned long timeDebounce = 0) : PinDebounceClass(pin, timeDebounce) {};
};


class EurekaEncoderClass : private _Button, _portB, _portA
{
 private:
	 int _stateAOld;
	 int _stateBOld;
	 unsigned long _timeLastTick;
	 signed int _rotaryValue;
	 void _update();

 public:
	EurekaEncoderClass(int pinPortA, int pinPortB, int pinButton, unsigned long timeDebouncePorts = 0, unsigned long timeDebounceButton = 50, unsigned long timeHold = 1000);
	signed int rotaryValue();
	bool hasRotaryValue();
	int buttonState();
	int buttonEvent();
	bool buttonClicked();
	bool buttonHeld();
	bool buttonReleased();
	void buttonReset();
	void update();
};

#endif
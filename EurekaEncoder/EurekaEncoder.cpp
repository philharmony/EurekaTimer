// 
// 
// 

#include "EurekaEncoder.h"

const signed int graytab[16] = { 0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//{ 0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0 };

void EurekaEncoderClass::_update()
{
	_portA::debounce();
	_portB::debounce();
	_Button::update();
	unsigned long _now = millis();
	int tick = graytab[_portA::state() << 3 | _portB::state() << 2 | _stateAOld << 1 | _stateBOld];
	if (tick != 0)
	{
		if ((unsigned long)(_now - _timeLastTick) < 30) tick = tick * 2;
		if ((unsigned long)(_now - _timeLastTick) < 15) tick = tick * 5;
		_timeLastTick = _now;
	}
	_rotaryValue = _rotaryValue + tick;
	_stateAOld = _portA::state();
	_stateBOld = _portB::state();
}

signed int EurekaEncoderClass::rotaryValue()
{
	signed int result = _rotaryValue;
	_rotaryValue = 0;
	return result;
}

bool EurekaEncoderClass::hasRotaryValue()
{
	return (_rotaryValue != 0);
}

int EurekaEncoderClass::buttonState()
{
	return _Button::state();
}

int EurekaEncoderClass::buttonEvent()
{
	return _Button::event();
}

bool EurekaEncoderClass::buttonClicked()
{
	return _Button::clicked();
}
bool EurekaEncoderClass::buttonHeld()
{
	return  _Button::held();
}
bool EurekaEncoderClass::buttonReleased()
{
	return _Button::released();
}

void EurekaEncoderClass::buttonReset()
{
	_Button::reset();
}

void EurekaEncoderClass::update()
{
	this->_update();
}

EurekaEncoderClass::EurekaEncoderClass(int pinPortA, int pinPortB, int pinButton, unsigned long timeDebouncePorts, unsigned long timeDebounceButton, unsigned long timeHold) :
	_portA(pinPortA, timeDebouncePorts),
	_portB(pinPortB, timeDebouncePorts),
	_Button(pinButton, timeDebounceButton, timeHold),
	_stateAOld(HIGH),
	_stateBOld(HIGH),
	_rotaryValue(0),
	_timeLastTick(0)
{
}


// 
// 
// 

#include "PinDebounce.h"


void PinDebounceClass::_debounce()
{
	unsigned long _now = millis();
	int _statenow = digitalRead(_pin);

	if (_stateOld != _statenow) _lastChecked = _now;	//If changed restart timing

	if (((unsigned long)(_now - _lastChecked) > _timeDebounce) && (_state != _stateOld)) _state = _statenow; //if new state stable long enough, update

	_stateOld = _statenow; //save for next run
}

//Constructor
PinDebounceClass::PinDebounceClass( int pin, unsigned long timeDebounce ) : _pin(pin), _timeDebounce(timeDebounce), _state(HIGH), _stateOld(HIGH), _lastChecked(0)
{
	pinMode(_pin, INPUT_PULLUP);
}


void PinDebounceClass::debounce()
{
	this->_debounce();
}

int PinDebounceClass::state()
{
	return _state;
}

//PinDebounceClass PinDebounce;


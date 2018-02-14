// 
// 
// 

#include "EurekaButton.h"

typedef enum {
	EUREKABUTTONNONE,
	EUREKABUTTONCLICKED,
	EUREKABUTTONHELD,
	EUREKABUTTONRELEASED
};


void EurekaButtonClass::_reset()
{
	_event = EUREKABUTTONNONE;
}

//Constructor
EurekaButtonClass::EurekaButtonClass(int pin, unsigned long timeDebounce, unsigned long timeHold) :
	PinDebounceClass(pin),
	_timeHold(timeHold),
	_stateOld(HIGH),
	_holdset(false),
	_event(EUREKABUTTONNONE),
	_timeDown(0)
{
}

void EurekaButtonClass::update()
{
	PinDebounceClass::debounce();
	int _statenow = PinDebounceClass::state();
	unsigned long _now = millis();
	if (_statenow != _stateOld)	//if changed
	{
		if (_statenow == LOW)	//and new state is pressed
		{
			_lastChange = _now;
		}
		else if (_statenow == HIGH) //if changed to released
		{
			_holdset = false;	//reset the hold recognition function
			if ((unsigned long)(_now - _lastChange) <= _timeHold) _event = EUREKABUTTONCLICKED;//and time shorter than _timeHold
			else _event = EUREKABUTTONRELEASED;
		}
	_stateOld = _statenow;	//save for next run
	}
	else //if unchanged
	{
		if ((_statenow == LOW) && ((unsigned long)(_now - _lastChange) > _timeHold) && (!_holdset))
		{
			_event = EUREKABUTTONHELD;//and State low (pressed) and time longer than _timeHold
			_holdset = true; //set the hold recognition function to trigger the event only once
		}
	}
}

int EurekaButtonClass::state()
{
	return PinDebounceClass::state();
}

int EurekaButtonClass::event()
{
	return _event;
}

bool EurekaButtonClass::clicked()
{
	if (_event != EUREKABUTTONCLICKED) return false;
	this->_reset();
	return true;

}

bool EurekaButtonClass::held()
{
	if (_event != EUREKABUTTONHELD) return false;
	this->_reset();
	return true;
}

bool EurekaButtonClass::released()
{
	if (_event != EUREKABUTTONRELEASED) return false;
	this->_reset();
	return true;
}

void EurekaButtonClass::reset()
{
	this->_reset();
}



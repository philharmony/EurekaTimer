// 
// 
// 

#include "EurekaRelais.h"

#define EUREKARELAISON LOW
#define EUREKARELAISOFF HIGH

void EurekaRelaisClass::_set(int state)
{
	digitalWrite(_pin, state);
}

int EurekaRelaisClass::_get()
{
	return digitalRead(_pin);
}

EurekaRelaisClass::EurekaRelaisClass(int pin) : _pin(pin)
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, EUREKARELAISOFF);
}

void EurekaRelaisClass::set(int state)
{
	this->_set(state);
}

void EurekaRelaisClass::seton()
{
	this->set(EUREKARELAISON);
}

void EurekaRelaisClass::setoff()
{
	this->_set(EUREKARELAISOFF);
}

int EurekaRelaisClass::state()
{
	return this->_get();
}

bool EurekaRelaisClass::isOn()
{
	return (this->_get() == EUREKARELAISON);
}

bool EurekaRelaisClass::isOff()
{
	return (this->_get() == EUREKARELAISOFF);
}

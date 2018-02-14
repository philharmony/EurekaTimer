// 
// 
// 

#include "EurekaCountdown.h"

EurekaCountdownClass::EurekaCountdownClass() : _isRunning(false), _startTime(0), _targetTime(0), _timeIsUp(false)
{
}

unsigned long EurekaCountdownClass::timeRemaining()
{
	return this->_timeRemaining();
}

int EurekaCountdownClass::secondsLeft()
{
	return _timeRemaining() / 1000;
}

int EurekaCountdownClass::tenthsLeft()
{
	return (_timeRemaining() % 1000) / 100;
}

void EurekaCountdownClass::start()
{
	this->_start();
}

void EurekaCountdownClass::stop()
{
	this->_stop();
}

void EurekaCountdownClass::reset()
{
	this->_reset();
}

void EurekaCountdownClass::set(int tgtSeconds, int tgtTenths)
{
	this->_set(tgtSeconds * 1000 + tgtTenths * 100);
}

void EurekaCountdownClass::set(unsigned long tgtmillis)
{
	this->_set(tgtmillis);
}

bool EurekaCountdownClass::isRunning()
{
	return _isRunning;
}

bool EurekaCountdownClass::timeIsUp()
{
	this->timeRemaining();
	bool result = _timeIsUp;
	_timeIsUp = false;
	return result;
}


unsigned long EurekaCountdownClass::_timeRemaining()
{
	if (_isRunning)
	{
		unsigned long _now = millis();
		if ((unsigned long)(_now - _startTime) > _targetTime)
		{
			_isRunning = false;
			_timeIsUp = true;
			return 0;
		}
		else
		{
			return (unsigned long)(_targetTime - (_now - _startTime));
		}
	}
	else return 0;
}

void EurekaCountdownClass::_start()
{
	_startTime = millis();
	_isRunning = true;
	_timeIsUp = false;
}
void EurekaCountdownClass::_stop()
{

}
void EurekaCountdownClass::_reset()
{
	_isRunning = false;
	_timeIsUp = false;
}


void EurekaCountdownClass::_set(unsigned long tgtmillis)
{
	_targetTime = tgtmillis;
}

// 
// 
// 

#include "EurekaStopwatch.h"

EurekaStopwatchClass::EurekaStopwatchClass() : _isPaused(false), _isRunning(false), _elapsedTime(0), _startTime(0), _lastTimeChecked(0)
{
}

unsigned long EurekaStopwatchClass::timeElapsed()
{
	return this->_timeElapsed();
}

int EurekaStopwatchClass::secondsElapsed()
{
	return _timeElapsed() / 1000;
}

int EurekaStopwatchClass::tenthsElapsed()
{
	return (_timeElapsed() % 1000) / 100;
}

void EurekaStopwatchClass::start()
{
	this->_start();
}

void EurekaStopwatchClass::pause()
{
	this->_pause();
}

void EurekaStopwatchClass::resume()
{
	this->_resume();
}

void EurekaStopwatchClass::reset()
{
	this->_reset();
}

bool EurekaStopwatchClass::isRunning()
{
	return _isRunning;
}

bool EurekaStopwatchClass::isPaused()
{;
	return _isPaused;
}


unsigned long EurekaStopwatchClass::_timeElapsed()
{
	if (_isRunning)
	{
		if (!isPaused())
		{ 
			unsigned long _now = millis();
			_elapsedTime = _elapsedTime + ((unsigned long)(_now - _lastTimeChecked));
			_lastTimeChecked = _now;	
		}
	}
	return _elapsedTime;
}

void EurekaStopwatchClass::_start()
{
	_elapsedTime = 0;
	_lastTimeChecked = millis();
	_isRunning = true;
	_isPaused = false;
}
void EurekaStopwatchClass::_pause()
{
	_isPaused = true;
}
void EurekaStopwatchClass::_resume()
{
	_isPaused = false;
	_lastTimeChecked = millis();
}

void EurekaStopwatchClass::_reset()
{
	_isRunning = false;
	_isPaused = false;
	_elapsedTime = 0;
}

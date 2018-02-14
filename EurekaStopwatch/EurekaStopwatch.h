// EurekaStopwatch.h

#ifndef _EUREKASTOPWATCH_h
#define _EUREKASTOPWATCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EurekaStopwatchClass
{
 private:
	 bool _isRunning;
	 bool _isPaused;
	 unsigned long _startTime;
	 unsigned long _elapsedTime;
	 unsigned long _lastTimeChecked;
	 unsigned long _timeElapsed();
	 void _start();
	 void _pause();
	 void _resume();
	 void _reset();
	 void _set(unsigned long tgtmillis);
 public:
	 EurekaStopwatchClass();
	 unsigned long timeElapsed();
	 int secondsElapsed();
	 int tenthsElapsed();
	 void start();
	 void pause();
	 void resume();
	 void reset();
	 bool isRunning();
	 bool isPaused();
};

#endif


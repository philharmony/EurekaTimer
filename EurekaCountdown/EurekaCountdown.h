// EurekaCountdown.h

#ifndef _EUREKACOUNTDOWN_h
#define _EUREKACOUNTDOWN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EurekaCountdownClass
{
 private:
	 bool _isRunning;
	 bool _timeIsUp;
	 unsigned long _startTime;
	 unsigned long _targetTime;
	 unsigned long _timeRemaining();
	 void _start();
	 void _stop();
	 void _reset();
	 void _set(unsigned long tgtmillis);
 public:
	 EurekaCountdownClass();
	 unsigned long timeRemaining();
	 int secondsLeft();
	 int tenthsLeft();
	 void start();
	 void reset();
	 void stop();
	 void set(int tgtSeconds, int tgtTenths);
	 void set(unsigned long tgtmillis);
	 bool isRunning();
	 bool timeIsUp();
};

#endif


// EurekaDisplayOLED.h
/*
	Functions to draw the various pages and the cup symbol. Uses Adafruit_GFX for draw functions, and
	Adafruit_SSD1306 to controll the oled display. Adapt functions to any other display you would like to use
*/

#ifndef _EUREKADISPLAYOLED_h
#define _EUREKADISPLAYOLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>
class EurekaDisplayOLEDClass
{
 private:
	Adafruit_SSD1306 _display;
	void _drawSingleCup(int left, int top, int level);
	void _drawDoubleCup(int left, int top, int level);
	void _drawScreenSaver(unsigned long screenSaverTime);
 public:
	EurekaDisplayOLEDClass();
	void begin();
	void showWelcomeScreen();
	void showReadyScreen(unsigned long targetTimeSingle, unsigned long targetTimeDouble, bool select);
	void showMillingScreen(unsigned long runningTime, unsigned long targetTimeSingle, unsigned long targetTimeDouble, bool select);
	void showEndlessScreen(unsigned long timeElapsed);
	void showMillingTimeMenu(unsigned long targetTimerSingle, unsigned long targetTimeDouble, bool select);
	void showSaveEndlessYesNoMenu(bool selYes);
	void showSaveEndlessSingleDoubleMenu(unsigned long time, bool select);
	void showScreenSaver(unsigned long screenSaverTime);
};

#endif


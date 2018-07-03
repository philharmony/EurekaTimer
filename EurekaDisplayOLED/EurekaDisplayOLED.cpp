// 
// 
// 

#include "EurekaDisplayOLED.h"


EurekaDisplayOLEDClass::EurekaDisplayOLEDClass() :
	_display(false)
{
}

void EurekaDisplayOLEDClass::begin()
{
	_display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	_display.clearDisplay();
	_display.display();
	_display.setTextSize(2);
	_display.setTextColor(WHITE);
}

void EurekaDisplayOLEDClass::_drawSingleCup(int left, int top, int level)
{
	const int width = 30;
	const int height = 30;
	const int rHandle = 7;
	const int fillHeight = (height * level) / 100;
	const int fillTop = height - fillHeight;
	left = left + rHandle;
	_display.fillRect(left + 1, top -1, width +2, height + 2, BLACK);
	_display.drawLine(left + 2 + 2, top + height + 1, left + 2 + width - 1 , top + height + 1, BLACK);
	_display.drawLine(left + 2 + 2, top + height + 2, left + 2 + width + 3, top + height + 2, BLACK);
	//_display.drawLine(left + 2 - 2, top + height + 3, left + 2 + width + 2, top + height + 3, BLACK);
	_display.fillCircle(left  , top + (height / 2), rHandle, WHITE);
	_display.fillCircle(left  , top + (height / 2), rHandle - 2, BLACK);
	_display.drawRect(left  + 2, top + 0, width, height, WHITE);
	_display.drawRect(left  + 2 + 1, top + 1, width - 2, height - 2, WHITE);
	_display.fillRect(left  + 2 + 2, top + 2, width -4, height - 4, BLACK);
	_display.fillRect(left + 2 + 2, top + fillTop, width - 4, fillHeight, WHITE);
	_display.drawLine(left + 2 + 1, top + height, left  + 2 + width - 2, top + height, WHITE);
	_display.drawLine(left  + 2 + 2, top + height + 1, left + 2 + width - 3, top + height + 1, WHITE);
	_display.drawLine(left + 2 - 2, top + height + 3, left  + 2 + width + 2, top + height + 3, WHITE);
	_display.drawLine(left + 2 - 1, top + height + 4, left + 2 + width + 1, top + height + 4, WHITE);
	_display.drawLine(left + 2 - 0, top + height + 5, left + 2 + width, top + height + 5, WHITE);
}

void EurekaDisplayOLEDClass::_drawDoubleCup(int left, int top, int level)
{
	this->_drawSingleCup(left + 20, top, level);
	this->_drawSingleCup(left, top + 3, level);
}

void EurekaDisplayOLEDClass::_drawScreenSaver(unsigned long screenSaverTime)
{
	//Uneven numbers to prevent patterns on the screen!
	int left = (screenSaverTime / 241) % 178;
	if (left > 89) left = 89 - (left - 89);
	int top = (screenSaverTime / 189) % 64;
	if (top > 32) top = 32 - (top - 32);
	if ((screenSaverTime / 60000) %  2) this->_drawSingleCup(left, top, (screenSaverTime / 200) % 90);
	else this->_drawDoubleCup(left, top, (screenSaverTime / 200) % 90);
}

void EurekaDisplayOLEDClass::showWelcomeScreen()
{
	_display.clearDisplay();
	_display.setTextSize(2);
	_display.setCursor(30,10);
	_display.print(F("Eureka"));
	_display.setCursor(36, 32);
	_display.print(F("Timer"));
	_display.setTextSize(1);
	_display.setCursor(52, 56);
	_display.print(F("V1.0"));
	_display.display();
}

void EurekaDisplayOLEDClass::showReadyScreen(unsigned long targetTimeSingle, unsigned long targetTimeDouble, bool select)
{
	unsigned long targetTime;
	if (select) targetTime = targetTimeSingle;
	else targetTime = targetTimeDouble;
	_display.clearDisplay();
	if (select)	this->_drawSingleCup(38,10,0);
	else this->_drawDoubleCup(30, 8, 0);
	if (targetTime > 10000)_display.setCursor(40, 50);
	else _display.setCursor(45, 50);
	_display.setTextSize(2);
	_display.print(targetTime / 1000);
	_display.print(",");
	_display.print((targetTime % 1000) / 100);
	_display.display();
}

void EurekaDisplayOLEDClass::showMillingScreen(unsigned long runningTime, unsigned long targetTimeSingle, unsigned long targetTimeDouble, bool select)
{
	unsigned long targetTime;
	if (select) targetTime = targetTimeSingle;
	else targetTime = targetTimeDouble;
	int level = ((targetTime - runningTime) * 100) / targetTime;
	_display.clearDisplay();
	if (select)	this->_drawSingleCup(38, 10, level);
	else this->_drawDoubleCup(30, 8, level);
	if(runningTime > 10000)_display.setCursor(40, 50);
	else _display.setCursor(45, 50);
	_display.setTextSize(2);
	_display.print(runningTime / 1000);
	_display.print(",");
	_display.print((runningTime % 1000) / 100);
	_display.display();
}

void EurekaDisplayOLEDClass::showEndlessScreen(unsigned long timeElapsed)
{
	_display.clearDisplay();
	_display.setCursor(20, 8);
	_display.setTextSize(2);
	_display.print(F("Endless"));
	if (timeElapsed > 10000)_display.setCursor(28, 36);
	else _display.setCursor(35, 36);
	_display.setTextSize(3);
	_display.print(timeElapsed / 1000);
	_display.print(F(","));
	_display.print((timeElapsed % 1000) / 100);
	_display.display();
}


void EurekaDisplayOLEDClass::showMillingTimeMenu(unsigned long targetTimerSingle, unsigned long targetTimeDouble, bool select)
{
	unsigned long setTime;
	if (select) setTime = targetTimerSingle;
	else setTime = targetTimeDouble;
	_display.clearDisplay();
	_display.setCursor(15, 8);
	_display.setTextSize(2);
	_display.print(F("Set Time:"));
	if (setTime > 10000)_display.setCursor(28, 36);
	else _display.setCursor(35, 36);
	_display.setTextSize(3);
	_display.print(setTime / 1000);
	_display.print(F(","));
	_display.print((setTime % 1000) / 100);
	_display.display();
}


void EurekaDisplayOLEDClass::showSaveEndlessYesNoMenu(bool selYes)
{
	_display.clearDisplay();
	_display.setCursor(40, 8);
	_display.setTextSize(2);
	_display.print(F("Save?"));
	_display.setTextSize(3);
	if (selYes)
	{
		_display.setCursor(25, 36);
		_display.print(F("<Yes>"));
	}
	else
	{
		_display.setCursor(30, 36);
		_display.print(F("<No>"));
	}
	_display.display();
}


void EurekaDisplayOLEDClass::showSaveEndlessSingleDoubleMenu(unsigned long time, bool select)
{
	_display.clearDisplay();
	_display.setCursor(5, 2);
	_display.setTextSize(2);
	_display.print(F("Save "));
	_display.print(time / 1000);
	_display.print(F(","));
	_display.print((time % 1000) / 100);
	_display.print(F(":"));
	if (select)	this->_drawSingleCup(40, 26, 0);
	else this->_drawDoubleCup(32, 24, 0);
	_display.display();
}

void EurekaDisplayOLEDClass::showScreenSaver(unsigned long screenSaverTime)
{
	_display.clearDisplay();
	this->_drawScreenSaver(screenSaverTime);
	_display.display();
}


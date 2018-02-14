#include <EurekaDisplayOLED.h>
#include <EurekaCountdown.h>
#include <EEPROM.h>
#include <EurekaStopwatch.h>
#include <EurekaRelais.h>
#include <EurekaEncoder.h>
#include <EurekaButton.h>

/*
To Do:
*/


/*In/Out-Pins, configure as convenient, Pins Analog 4 and 5 are reserved for I2C on Arduino Nano*/
#define pinMillTrigger 11
#define pinEncButton 10
#define pinEncPortA 9
#define pinEncPortB 8
#define pinMillRel 12

/*EEPROM Adresses for remanent storage of times*/
int EEAdrSingleTime = 0;
int EEAdrDoubleTime =4;

/*Global Vars*/
unsigned long targetTimeSingle;
unsigned long targetTimeDouble;
int state = 0;
bool selectSingleDouble = false;
bool selectSave = false;

#define SELECTSINGLE true
#define SELECTDOUBLE false
#define SELECTSAVE	true
#define SELECTCANCLE false

/*Using only my own Libs*/
EurekaDisplayOLEDClass Display;
/*Change last Parameter to alter time when endless mode starts. Too short might misinterpret a click as a hold, too long gets boring*/
EurekaButtonClass BtnMillTrigger(pinMillTrigger, 50, 1000);
EurekaEncoderClass EncSettings(pinEncPortA, pinEncPortB, pinEncButton, 0, 50, 750);
EurekaRelaisClass RelMill(pinMillRel);
EurekaCountdownClass Countdown;
EurekaStopwatchClass Elapsed;
EurekaCountdownClass CycleTimer;



void setup() {
	// put your setup code here, to run once:

	/*Resets stored Times to 0 if Encoderbutton is being held down during PowerUp -> "Factory Reset"*/
	pinMode(pinEncButton, INPUT_PULLUP);
	if (digitalRead(pinEncButton) == LOW)
	{
		EEPROM.put(EEAdrSingleTime, (unsigned long)0);
		EEPROM.put(EEAdrDoubleTime, (unsigned long)0);
	}

	/*Read times from EEPROM, also done below, could be skipped here but doesn´t harm either*/
	EEPROM.get(EEAdrSingleTime, targetTimeSingle);
	EEPROM.get(EEAdrDoubleTime, targetTimeDouble);

	/*Serial for Debug, uncomment if needed */
//	Serial.begin(9600);
	Display.begin();
	Display.showWelcomeScreen();
	delay(5000);
//	Serial.println(F("setup done!"));
	/*Run on 10Hz, not neccessary to run and redraw more often*/
	CycleTimer.set(100);
	CycleTimer.start();
}

/*States for State-Machine*/
typedef enum {
	STATE_INIT,
	STATE_RESET,
	STATE_READY,
	STATE_RUN_TIMER,
	STATE_RUN_ENDLESS,
	STATE_PAUSE_ENDLESS,
	STATE_RESUME_ENDLESS,
	STATE_SAVE_TIME_YES_NO,
	STATE_SAVE_TIME,
	STATE_RUN_SETUP
};

void loop() {
	// put your main code here, to run repeatedly:
	/*Read Buttin and Encoder on every cycle*/
	BtnMillTrigger.update();
	EncSettings.update();

	/*All the rest runs on 10Hz*/
	/*So if timer 100 millis is up*/
	if (CycleTimer.timeIsUp())
	{
		/*Restart timer*/
		CycleTimer.start();

		/*Run state machine*/
		switch (state)
		{
		/*Init, just Zero everything and read times from eeprom*/
		case STATE_INIT:
			BtnMillTrigger.reset();
			EncSettings.buttonReset();
			Countdown.reset();
			RelMill.setoff();
			EEPROM.get(EEAdrSingleTime, targetTimeSingle);
			EEPROM.get(EEAdrDoubleTime, targetTimeDouble);
			state = STATE_RESET;
			break;

			/*same as above without reading from eeprom, good start to optimize here*/
		case STATE_RESET:
			BtnMillTrigger.reset();
			EncSettings.buttonReset();
			Countdown.reset();
			Elapsed.reset();
			RelMill.setoff();
			selectSave = false;
			/*Draw display*/
			Display.showReadyScreen(targetTimeSingle, targetTimeDouble, selectSingleDouble);
			state = STATE_READY;
			break;

		case STATE_READY:
			/*Here we are most of the time, waiting for any user imput*/
			if (BtnMillTrigger.clicked())
			{
				/*If Milltrigger clicked, load timer depending if signle or double is active, update screen and let it run*/
				if (selectSingleDouble == SELECTSINGLE) Countdown.set(targetTimeSingle);
				else Countdown.set(targetTimeDouble);
				Countdown.start();
				RelMill.seton();
				Display.showMillingScreen(Countdown.timeRemaining(), targetTimeSingle, targetTimeDouble, selectSingleDouble);
				state = STATE_RUN_TIMER;
			}

			/*If the milltrigger is held pressed for more than a second (can be changed above)*/
			/*Enter endless mode*/
			if (BtnMillTrigger.held())
			{
				Display.showEndlessScreen(Elapsed.timeElapsed());
				Elapsed.start();
				RelMill.seton();
				state = STATE_RUN_ENDLESS;
			}

			/*If encoder Button clicked or encoder turned change btw. single and duble*/
			if (EncSettings.buttonClicked() || EncSettings.rotaryValue())
			{
				selectSingleDouble = !selectSingleDouble;
				Display.showReadyScreen(targetTimeSingle, targetTimeDouble, selectSingleDouble);

			}

			/*If button held (long press, default 750millis, change above if needed) enter setup*/
			if (EncSettings.buttonHeld())
			{
				Display.showMillingTimeMenu(targetTimeSingle, targetTimeDouble, selectSingleDouble);
				state = STATE_RUN_SETUP;
			}
			break;

			/*Just update the time and cup symbol until time is up or milltrigger or button is being clicked. Then stop end reset*/
		case STATE_RUN_TIMER:
			if ((Countdown.timeIsUp()) || (BtnMillTrigger.clicked()) || EncSettings.buttonClicked()) state = STATE_RESET;
			Display.showMillingScreen(Countdown.timeRemaining(), targetTimeSingle, targetTimeDouble, selectSingleDouble);
			break;

			/*Run endless mode, count up time until milltrigger is being released again, then pause*/
		case STATE_RUN_ENDLESS:
			Display.showEndlessScreen(Elapsed.timeElapsed());
			if (BtnMillTrigger.released())
			{
				RelMill.setoff();
				Elapsed.pause();
				state = STATE_PAUSE_ENDLESS;
			}
			break;
		
			/*If trigger held again, resume endless, if Encoder clicked enter save-manu, if being held long, abort*/
		case STATE_PAUSE_ENDLESS:
			if (BtnMillTrigger.held()) state = STATE_RESUME_ENDLESS;
			//if (BtnMillTrigger.clicked()) state = STATE_RESET;
			if (EncSettings.buttonClicked())
			{
				Display.showSaveEndlessYesNoMenu(selectSave);
				state = STATE_SAVE_TIME_YES_NO;
			}
			if (EncSettings.buttonHeld()) state = STATE_RESET;

			break;

			/*Resume elapsed time and start mill again*/
		case STATE_RESUME_ENDLESS:
			Display.showEndlessScreen(Elapsed.timeElapsed());
			state = STATE_RUN_ENDLESS;
			RelMill.seton();
			Elapsed.resume();
			break;

			/*Ask if user wants to save the elapsed time <yes> or <no>. Turning changes answer, click logs it in*/
		case STATE_SAVE_TIME_YES_NO:
			if (EncSettings.buttonClicked())
			{
				if (selectSave == SELECTSAVE)
				{
					Display.showSaveEndlessSingleDoubleMenu(Elapsed.timeElapsed(), selectSingleDouble);
					state = STATE_SAVE_TIME;
				}
				else state = STATE_RESET;
			}
			if (EncSettings.rotaryValue())
			{
				selectSave = !selectSave;
				Display.showSaveEndlessYesNoMenu(selectSave);
			}
			break;

			/*If <yes> ask where to save it to, single or double. Turning changes selection, click logs in, long press aborts*/
		case STATE_SAVE_TIME:

			if (EncSettings.buttonClicked())
			{
				if (selectSingleDouble == SELECTSINGLE)	EEPROM.put(EEAdrSingleTime, Elapsed.timeElapsed());
				else EEPROM.put(EEAdrDoubleTime, Elapsed.timeElapsed());
				Elapsed.reset();				
				state = STATE_INIT;
			}
			if (EncSettings.rotaryValue())
			{
				selectSingleDouble = !selectSingleDouble;
				Display.showSaveEndlessSingleDoubleMenu(Elapsed.timeElapsed(), selectSingleDouble);
			}
			if (EncSettings.buttonHeld())
			{
				//Display.showEndlessScreen(Elapsed.timeElapsed()); //Was confusing
				state = STATE_RESET;
			}
			if (BtnMillTrigger.held())
			{
				state = STATE_RESUME_ENDLESS;
			}
			break;

			/*Long press in ready mode enters time setup of selected timer (single or double)*/
			/*Turning changes time, click saves, long press aborts*/
			case STATE_RUN_SETUP:
			if (EncSettings.buttonClicked())
			{
				if (selectSingleDouble == SELECTSINGLE) EEPROM.put(EEAdrSingleTime, targetTimeSingle);
				else EEPROM.put(EEAdrDoubleTime, targetTimeDouble);
				state = STATE_INIT;
				break;
			}
			if (EncSettings.buttonHeld())
			{
				state = STATE_INIT;
				break;
			}
			if (EncSettings.hasRotaryValue())
			{
				if (selectSingleDouble == SELECTSINGLE) targetTimeSingle = targetTimeSingle + (EncSettings.rotaryValue() * 100);
				else targetTimeDouble = targetTimeDouble + (EncSettings.rotaryValue() * 100);
				Display.showMillingTimeMenu(targetTimeSingle, targetTimeDouble, selectSingleDouble);
			}
			break;

			/*Any other state wherever it might come from resets*/
		default:
			state = STATE_RESET;
			break;
		}
	}
	
}
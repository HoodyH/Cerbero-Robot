// SequenzeLed.h

#ifndef _SEQUENZELED_h
#define _SEQUENZELED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SequenzeLedClass
{
protected:
public:
	void test(int ledPingDX, int ledPingSX, int ledRxDX, int ledRxSX, int ledFotoDX, int ledFotoSX, int ledFotoC, int ledGas, int Led_Fendinebbia, int Led_Abaglianti, int Led_FrecciaDX, int Led_FrecciaSX, int Led_Stop);
	void rotazione();
	void lampeggioLuce(int ledPingDX, int ledPingSX, int ledRxDX, int ledRxSX, int ledFotoDX, int ledFotoSX, int ledFotoC, int ledGas, int Led_Fendinebbia, int Led_Abaglianti, int Led_FrecciaDX, int Led_FrecciaSX, int Led_Stop);
	void LampeggioGas(int ledPingDX, int ledPingSX, int ledRxDX, int ledRxSX, int ledFotoDX, int ledFotoSX, int ledFotoC, int ledGas, int Led_Fendinebbia, int Led_Abaglianti, int Led_FrecciaDX, int Led_FrecciaSX, int Led_Stop);
};

extern SequenzeLedClass SequenzeLed;

#endif

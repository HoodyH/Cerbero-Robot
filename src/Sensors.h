// Sensors.h

#ifndef _SENSORS_h
#define _SENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PingClass
{
 protected:
	 int _echoDX;
	 int _triggerDX;
	 int _echoSX;
	 int _triggerSX;

 public:
	 void inizializateDX(int triggerDX, int echoDX);
	 void inizializateSX(int triggerSX, int echoSX);

	 float distanceDX(float& distanceDX);
	 float distanceSX(float& distanceSX);
};

extern PingClass Ping;

//------------------------------------------------------------------------------------

class FotoresistorClass
{
protected:
	int _fotoDX;
	int _fotoSX;
	int _fotoC;

public:
	void inizializate(int fotoDX, int fotoSX, int fotoC);

	float letturaDX(float& value);
	float letturaSX(float& value);
	float letturaC(float& value);
};

extern FotoresistorClass Fotoresistor;

//------------------------------------------------------------------------------------

class GasClass
{
protected:
	int _gasPin;

public:
	void inizializate(int gasPin);

	float lettura(float& value);
};

extern GasClass Gas;

#endif


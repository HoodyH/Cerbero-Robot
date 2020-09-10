// Motore.h

#ifndef _MOTORE_h
#define _MOTORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotoreClass
{
 protected:
	 int _pwmADX;
	 int _AIN1DX;
	 int _AIN2DX;
	 int _pwmBSX;
	 int _BIN1SX;
	 int _BIN2SX;
	 int _standby;

	 bool countstraight = 0;
	 bool countright = 0;
	 bool countleft = 0;
	 bool countback = 0;

	 unsigned long currentMillis;
	 unsigned long previousMillis = 0;

	 int i1;
	 int i2;

	 float deltaAcceleration;
	 float speedI1;
	 float speedI2;

 public:
	 void motoreDX(int pwmADX, int AIN1DX, int AIN2DX);
	 void motoreSX(int pwmBSX, int BIN1SX, int BIN2SX);
	 void standby(int standby);

	 void straight(int speed, int acceleration, float delta, int speedReduction, int StepAccelerazioneStraight, int vmin);
	 void right(int speed, int acceleration, float delta, int StepAccelerazioneRotate, int vmin);
	 void left(int speed, int acceleration, float delta, int StepAccelerazioneRotate, int vmin);
	 void back(int speed, int acceleration, float delta, int StepAccelerazioneBack, int vmin);
	 void wait(int duration);

};

extern MotoreClass Motore;

#endif


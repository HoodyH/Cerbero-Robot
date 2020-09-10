// 
// 
// 

#include "SequenzeLed.h"
#include "Motore.h"
#include "Bluetooth.h"
#include "buzzer.h"
#include "Navigation.h"

//------------------------------------------------------------------------------------
//SEQUENZELEDCLASS::TEST
//------------------------------------------------------------------------------------

void SequenzeLedClass::test(int ledPingDX, int ledPingSX, int ledRxDX, int ledRxSX, int ledFotoDX, int ledFotoSX, int ledFotoC, int ledGas, int Led_Fendinebbia, int Led_Abaglianti, int Led_FrecciaDX, int Led_FrecciaSX, int Led_Stop) {
#define speedTest 200
#define speedTestMotor 1000

  Bluetooth.stato=0; //warming up
  delay(8000);
  Bluetooth.stato=1; //test start
  
	digitalWrite(ledPingDX, HIGH);
	delay(speedTest);
	digitalWrite(ledPingDX, LOW);
	digitalWrite(ledFotoDX, HIGH);
	delay(speedTest);
	digitalWrite(ledFotoDX, LOW);
	digitalWrite(ledRxDX, HIGH);
	delay(speedTest);
	digitalWrite(ledRxDX, LOW);
	digitalWrite(ledFotoC, HIGH);
	delay(speedTest);
	digitalWrite(ledFotoC, LOW);
	digitalWrite(ledGas, HIGH);
	delay(speedTest);
	digitalWrite(ledGas, LOW);
	digitalWrite(ledRxSX, HIGH);
	delay(speedTest);
	digitalWrite(ledRxSX, LOW);
	digitalWrite(ledFotoSX, HIGH);
	delay(speedTest);
	digitalWrite(ledFotoSX, LOW);
	digitalWrite(ledPingSX, HIGH);
	delay(speedTest);
	digitalWrite(ledPingSX, LOW);
	digitalWrite(Led_Abaglianti, HIGH);
	delay(speedTest);
	digitalWrite(Led_Abaglianti, LOW);
	digitalWrite(Led_Fendinebbia, HIGH);
	delay(speedTest);
	digitalWrite(Led_Fendinebbia, LOW);
	digitalWrite(Led_FrecciaDX, HIGH);
	delay(speedTest);
	digitalWrite(Led_FrecciaDX, LOW);
	digitalWrite(Led_FrecciaSX, HIGH);
	delay(speedTest);
	digitalWrite(Led_FrecciaSX, LOW);
	digitalWrite(Led_Stop, HIGH);
	delay(speedTest);
	digitalWrite(Led_Stop, LOW);
	delay(speedTest);
	digitalWrite(ledPingDX, HIGH);
	digitalWrite(ledPingSX, HIGH);
	digitalWrite(ledRxDX, HIGH);
	digitalWrite(ledRxSX, HIGH);
	digitalWrite(ledFotoDX, HIGH);
	digitalWrite(ledFotoC, HIGH);
	digitalWrite(ledFotoSX, HIGH);
	digitalWrite(ledGas, HIGH);
	digitalWrite(Led_Abaglianti, HIGH);
	digitalWrite(Led_Fendinebbia, HIGH);
	digitalWrite(Led_FrecciaDX, HIGH);
	digitalWrite(Led_FrecciaSX, HIGH);
	digitalWrite(Led_Stop, HIGH);
	delay(speedTest);
	digitalWrite(ledPingDX, LOW);
	digitalWrite(ledPingSX, LOW);
	digitalWrite(ledRxSX, LOW);
	digitalWrite(ledRxDX, LOW);
	digitalWrite(ledFotoDX, LOW);
	digitalWrite(ledFotoC, LOW);
	digitalWrite(ledFotoSX, LOW);
	digitalWrite(ledGas, LOW);
	digitalWrite(Led_Abaglianti, LOW);
	digitalWrite(Led_Fendinebbia, LOW);
	digitalWrite(Led_FrecciaDX, LOW);
	digitalWrite(Led_FrecciaSX, LOW);
	digitalWrite(Led_Stop, LOW);

	for (int i = 0; i<800; i++) {
		Motore.straight(200, 7, 0, 0, 1, 60);
		delay(1);
	}//end for
	Motore.wait(400);

	for (int i = 0; i<800; i++) {
		Motore.back(200, 7, 0, 1, 60);
		delay(1);
	}//end for
	Motore.wait(400);

	for (int i = 0; i<10; i++) {
		digitalWrite(ledPingDX, HIGH);
		digitalWrite(ledPingSX, HIGH);
		digitalWrite(ledRxDX, HIGH);
		digitalWrite(ledRxSX, HIGH);
		digitalWrite(ledFotoDX, HIGH);
		digitalWrite(ledFotoC, HIGH);
		digitalWrite(ledFotoSX, HIGH);
		digitalWrite(ledGas, HIGH);
		digitalWrite(Led_Abaglianti, HIGH);
		digitalWrite(Led_Fendinebbia, HIGH);
		digitalWrite(Led_FrecciaDX, HIGH);
		digitalWrite(Led_FrecciaSX, HIGH);
		digitalWrite(Led_Stop, HIGH);
		delay(speedTest);
		digitalWrite(ledPingDX, LOW);
		digitalWrite(ledPingSX, LOW);
		digitalWrite(ledRxDX, LOW);
		digitalWrite(ledRxSX, LOW);
		digitalWrite(ledFotoDX, LOW);
		digitalWrite(ledFotoC, LOW);
		digitalWrite(ledFotoSX, LOW);
		digitalWrite(ledGas, LOW);
		digitalWrite(Led_Abaglianti, LOW);
		digitalWrite(Led_Fendinebbia, LOW);
		digitalWrite(Led_FrecciaDX, LOW);
		digitalWrite(Led_FrecciaSX, LOW);
		digitalWrite(Led_Stop, LOW);
		delay(speedTest);
		digitalWrite(Led_Abaglianti, HIGH);
		digitalWrite(Led_Fendinebbia, HIGH);
		digitalWrite(Led_Stop, HIGH);
	}//end for
   
   Bluetooth.stato=2; //ready
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=3; // go
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=4; //find lights
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=5; // find gas
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=6; //stop
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=7; //lights found
   Navigation.updateSensors();
   for (int i = 0; i<4; i++) {
        Buzzer.playMelody(2);  //la canzone viene scritta in base alle pause e all'intensit�, vedere buzzer.cpp
        SequenzeLed.lampeggioLuce(ledPingDX, ledPingSX, ledRxDX, ledRxSX, ledFotoDX, ledFotoSX, ledFotoC, ledGas, Led_Fendinebbia, Led_Abaglianti, Led_FrecciaDX, Led_FrecciaSX, Led_Stop);
   }//end for
   delay(2000);
   Bluetooth.stato=8; //gas found
   Navigation.updateSensors();
   Buzzer.playMelody(3);
   for (int i = 0; i<3; i++) {
        digitalWrite(ledFotoDX, HIGH);
        digitalWrite(ledFotoC, HIGH);
        digitalWrite(ledFotoSX, HIGH);
        digitalWrite(ledGas, HIGH);
        digitalWrite(Led_FrecciaDX, HIGH);
        digitalWrite(Led_FrecciaSX, HIGH);
        delay(50);
        digitalWrite(ledFotoDX, LOW);
        digitalWrite(ledFotoC, LOW);
        digitalWrite(ledFotoSX, LOW);
        digitalWrite(ledGas, LOW);
        digitalWrite(Led_FrecciaDX, LOW);
        digitalWrite(Led_FrecciaSX, LOW);
        delay(50);
      }//end for
   delay(2000);
   Bluetooth.stato=9; //both found
   Navigation.updateSensors();
   delay(2000);
   Bluetooth.stato=10; //no gas
   Navigation.updateSensors();
   Buzzer.playMelody(5);
   for (int i = 0; i<5; i++) {
      digitalWrite(ledGas, HIGH);
      digitalWrite(Led_FrecciaDX, HIGH);
      digitalWrite(Led_FrecciaSX, HIGH);
      delay(50);
      digitalWrite(ledGas, LOW);
      digitalWrite(Led_FrecciaDX, LOW);
      digitalWrite(Led_FrecciaSX, LOW);
      delay(50);
    }//end for
   delay(2000);

}//end void test

 //------------------------------------------------------------------------------------
 //SEQUENZELEDCLASS::ROTAZIONE
 //-------------------------------------------------------------------------------------

void SequenzeLedClass::rotazione() {

	for (int i = 0; i<2000; i++) {
		Motore.left(250, 5, 0, 1, 170);
		delay(1);
    Bluetooth.stato=1;//test start
	}//end for
	Motore.wait(400);
  
}// end rotazione

 //------------------------------------------------------------------------------------
 //SEQUENZELEDCLASS::LAMPEGGIOLUCE
 //-------------------------------------------------------------------------------------

void SequenzeLedClass::lampeggioLuce(int ledPingDX, int ledPingSX, int ledRxDX, int ledRxSX, int ledFotoDX, int ledFotoSX, int ledFotoC, int ledGas, int Led_Fendinebbia, int Led_Abaglianti, int Led_FrecciaDX, int Led_FrecciaSX, int Led_Stop) {

	for (int i = 0; i<3; i++) {
		digitalWrite(ledPingDX, HIGH);
		digitalWrite(ledPingSX, HIGH);
		digitalWrite(ledRxDX, HIGH);
		digitalWrite(ledRxSX, HIGH);
		digitalWrite(ledFotoDX, HIGH);
		digitalWrite(ledFotoC, HIGH);
		digitalWrite(ledFotoSX, HIGH);
		digitalWrite(Led_Abaglianti, HIGH);
		digitalWrite(Led_Fendinebbia, HIGH);
		digitalWrite(Led_FrecciaDX, HIGH);
		digitalWrite(Led_FrecciaSX, HIGH);
		digitalWrite(Led_Stop, HIGH);
		delay(50);
		digitalWrite(ledPingDX, LOW);
		digitalWrite(ledPingSX, LOW);
		digitalWrite(ledRxDX, LOW);
		digitalWrite(ledRxSX, LOW);
		digitalWrite(ledFotoDX, LOW);
		digitalWrite(ledFotoC, LOW);
		digitalWrite(ledFotoSX, LOW);
		digitalWrite(Led_Abaglianti, LOW);
		digitalWrite(Led_Fendinebbia, LOW);
		digitalWrite(Led_FrecciaDX, LOW);
		digitalWrite(Led_FrecciaSX, LOW);
		digitalWrite(Led_Stop, LOW);
		delay(50);
		digitalWrite(ledFotoC, HIGH);
		digitalWrite(ledRxDX, HIGH);
		digitalWrite(ledRxSX, HIGH);
	}//end for

}//end void lampeggio luce

SequenzeLedClass SequenzeLed;

// 
// 
// 

#include "Sensors.h"
#include "Navigation.h"
#include "Motore.h"

//------------------------------------------------------------------------------------
//PING::INIZIALIZATE
//------------------------------------------------------------------------------------

void PingClass::inizializateDX(int triggerDX, int echoDX) {
	_echoDX = echoDX;
	_triggerDX = triggerDX;
	pinMode(_triggerDX, OUTPUT);
	pinMode(_echoDX, INPUT);
	pinMode(_echoDX, INPUT_PULLUP);
	Serial.println("PingDX inizializzato ");
}

void PingClass::inizializateSX(int triggerSX, int echoSX) {
	_echoSX = echoSX;
	_triggerSX = triggerSX;
	pinMode(_triggerSX, OUTPUT);
	pinMode(_echoSX, INPUT);
	pinMode(_echoSX, INPUT_PULLUP);
	Serial.println("PingSX inizializzato ");
}

//------------------------------------------------------------------------------------
//PING::DISTANCE DX
//------------------------------------------------------------------------------------

float PingClass::distanceDX(float& distanceDX) {

	digitalWrite(_triggerDX, LOW);//porta bassa l'uscita del trigger
	digitalWrite(_triggerDX, HIGH);//invia un impulso di 10microsec su trigger
	delayMicroseconds(10);//delayMicroseconds(1);
	digitalWrite(_triggerDX, LOW);

	long durata = pulseIn(_echoDX, HIGH);
	distanceDX = 0.034 * durata / 2;
	distanceDX = constrain(distanceDX, 0, 250);
	//Serial.print("distanza DX");
	//Serial.print(distanceDX); 
	return distanceDX;
}//end int distance DX

 //------------------------------------------------------------------------------------
 //PING::DISTANCE SX
 //------------------------------------------------------------------------------------

float PingClass::distanceSX(float& distanceSX) {

	digitalWrite(_triggerSX, LOW);//porta bassa l'uscita del trigger
	digitalWrite(_triggerSX, HIGH);//invia un impulso di 10microsec su trigger
	delayMicroseconds(10);//delayMicroseconds(1);
	digitalWrite(_triggerSX, LOW);

	long durata = pulseIn(_echoSX, HIGH);
	distanceSX = 0.034 * durata / 2;
	distanceSX = constrain(distanceSX, 0, 250);
	//Serial.print("distanza SX ");
	//Serial.print(distanceSX); 
	return distanceSX;
}//end int distance DX

 //------------------------------------------------------------------------------------
 //FOTORESISTOR::INIZIALIZATE
 //------------------------------------------------------------------------------------

void FotoresistorClass::inizializate(int fotoDX, int fotoSX, int fotoC) {
	_fotoDX = fotoDX;
	_fotoSX = fotoSX;
	_fotoC = fotoC;

}//end void inizializate

 //------------------------------------------------------------------------------------
 //FOTORESISTOR::LETTURADX
 //------------------------------------------------------------------------------------

float FotoresistorClass::letturaDX(float& value) {
	value = analogRead(_fotoDX);
	return value;

}//end void letturaDX

 //------------------------------------------------------------------------------------
 //FOTORESISTOR::LETTURASX
 //------------------------------------------------------------------------------------

float FotoresistorClass::letturaSX(float& value) {
	value = analogRead(_fotoSX);
	return value;

}//end void letturaSX

 //------------------------------------------------------------------------------------
 //FOTORESISTOR::LETTURAC
 //------------------------------------------------------------------------------------

float FotoresistorClass::letturaC(float& value) {
	value = analogRead(_fotoC);
	return value;

}//end void letturaC

 //------------------------------------------------------------------------------------
 //GAS::INIZIALIZATE
 //------------------------------------------------------------------------------------

void GasClass::inizializate(int gasPin) {
	_gasPin = gasPin;
}//end void inizializate

 //------------------------------------------------------------------------------------
 //GAS::INIZIALIZATE
 //------------------------------------------------------------------------------------

float GasClass::lettura(float& value) {
	value = analogRead(_gasPin);
	return value;
}//end float lettura

PingClass Ping;
FotoresistorClass Fotoresistor;
GasClass Gas;


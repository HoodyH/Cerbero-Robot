// 
// 
// 

#include "Motore.h"

//Inversione Motori
#define A LOW
#define B HIGH
//------------------------------------------------------------------------------------
//CONFIGURAZIONE
//------------------------------------------------------------------------------------

void MotoreClass::motoreDX(int pwmADX, int AIN1DX, int AIN2DX) {
	_pwmADX = pwmADX;
	_AIN1DX = AIN1DX;
	_AIN2DX = AIN2DX;
	pinMode(_pwmADX, OUTPUT);
	pinMode(_AIN1DX, OUTPUT);
	pinMode(_AIN2DX, OUTPUT);

}//end motore dx

void MotoreClass::motoreSX(int pwmBSX, int BIN1SX, int BIN2SX) {
	_pwmBSX = pwmBSX;
	_BIN1SX = BIN1SX;
	_BIN2SX = BIN2SX;
	pinMode(_pwmBSX, OUTPUT);
	pinMode(_BIN1SX, OUTPUT);
	pinMode(_BIN2SX, OUTPUT);

}//end motore rx

void MotoreClass::standby(int standby) {
	_standby = standby;
	pinMode(_standby, OUTPUT);

}//end standby


 //------------------------------------------------------------------------------------
 //STREIGTH
 //------------------------------------------------------------------------------------

void MotoreClass::straight(int speed, int acceleration, float delta, int speedReduction, int StepAccelerazioneStraight, int vmin) {
	//funzione che implementa anche la rotazione, rallentando la velocità della ruota opposta all'ostacolo
	//tramite il delta che viene calcolato nella classe movimento, il codice riconosce tramite il sengo del delta quale ruota rallentare

	//i seguenti contatori si resettano permettendo di svolgere l'accelerazione solo la prima volta che si esegue il ciclo
	//di modo da poter riefettuare l'accelerazione dopo un cambio di direzione
	//sono definiti nel file .h
	countright = 0;
	countleft = 0;
	countback = 0;

	digitalWrite(_standby, HIGH);//attiva i motori disabilitando lo standby

								 //setta i pin alti e bassi in base alla tabella di verità dell'integrato
	digitalWrite(_AIN1DX, B);
	digitalWrite(_AIN2DX, A);
	digitalWrite(_BIN1SX, A);
	digitalWrite(_BIN2SX, B);

	//aggiorna l'istante corrente 
	currentMillis = millis();

	switch (countstraight) { //verifica se l'accelerazione è già stata inizializzata, se no costringe la velocità al valore impostato
	case 0:
		i1 = vmin;    //definita nel file .h
		i2 = vmin;    //definita nel file .h
		countstraight = 1;  //impone che l'inizializzazione dell'accelerazione è stata effettuata
		break;
		//case 0

	case 1:
		if (currentMillis - previousMillis >= acceleration) {  //conrolla se è passato il tempo minimo dell'intervallo prestabilito
			previousMillis = currentMillis;               //se si aggiorna l'istante dell'ultimo aggiornameto

			if (delta != 0) {

				if (delta<0) {
					delta = abs(delta);
					deltaAcceleration = map(delta, 10, speed, 1, 5);

					i1 = i1 + (StepAccelerazioneStraight / deltaAcceleration);
					i2 = i2 + StepAccelerazioneStraight;

					if (speedReduction == 1) {
						speedReduction = speed;
					}

					i1 = min(i1, speed - (speed / speedReduction) - delta); // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					i2 = min(i2, speed - (speed / speedReduction));       // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					break;
				}//end if delta > 0

				if (delta>0) {
					deltaAcceleration = map(delta, 10, speed, 1, 5);

					i1 = i1 + StepAccelerazioneStraight;
					i2 = i2 + (StepAccelerazioneStraight / deltaAcceleration);

					if (speedReduction == 1) {
						speedReduction = speed;
					}

					i1 = min(i1, speed - (speed / speedReduction));        // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					i2 = min(i2, speed - (speed / speedReduction) - delta);  // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					break;
				}//end if delta < 0 

			}//end if delta != 0

			else {                               //nel caso che il delta sia 0, le accelerazioni delle 2 ruote saranno identiche
				i1 = i1 + StepAccelerazioneStraight;
				i2 = i2 + StepAccelerazioneStraight;
				i1 = min(i1, speed);
				i2 = min(i2, speed);
			}//end else
		}//end else current millis
		break;

	}//and switchcase

	analogWrite(_pwmADX, i2);//assegno velocità mot 1
	analogWrite(_pwmBSX, i1);//assegno velocità mot 2 

}//end void streight

 //------------------------------------------------------------------------------------
 //RIGHT
 //------------------------------------------------------------------------------------

void MotoreClass::left(int speed, int acceleration, float delta, int StepAccelerazioneRotate, int vmin)
{
	countright = 0; //resetta il contatore che controlla il conteggio di accelerazione
	countback = 0;
	countstraight = 0;

	digitalWrite(_standby, HIGH);//attiva i motori disabilitando lo standby
	digitalWrite(_AIN1DX, A);
	digitalWrite(_AIN2DX, B);
	digitalWrite(_BIN1SX, A);
	digitalWrite(_BIN2SX, B);

	currentMillis = millis();
	switch (countleft) {

	case 0:
		i1 = vmin; //definita all inizio della libreria
		i2 = vmin;
		countleft = 1;
		break;
		//case 0

	case 1:
		if (currentMillis - previousMillis >= acceleration) {
			previousMillis = currentMillis;

			i1 = i1 + StepAccelerazioneRotate;
			i2 = i2 + StepAccelerazioneRotate;

			i1 = min(i1, speed);
			i2 = min(i2, speed);

		}//end if current millis
		break;

	}//and switchcase

	analogWrite(_pwmADX, i1);//assegno velocità mot 1
	analogWrite(_pwmBSX, i2);//assegno velocità mot 2 

}//end void left

 //------------------------------------------------------------------------------------
 //LEFT
 //------------------------------------------------------------------------------------

void MotoreClass::right(int speed, int acceleration, float delta, int StepAccelerazioneRotate, int vmin)
{
	countleft = 0; //resetta il contatore che controlla il conteggio di accelerazione
	countback = 0;
	countstraight = 0;

	digitalWrite(_standby, HIGH);//attiva i motori disabilitando lo standby
	digitalWrite(_AIN1DX, B);
	digitalWrite(_AIN2DX, A);
	digitalWrite(_BIN1SX, B);
	digitalWrite(_BIN2SX, A);

	currentMillis = millis();

	switch (countright) {

	case 0:
		i1 = vmin; //definita all inizio della libreria
		i2 = vmin;
		countright = 1;
		break;
		//case 0

	case 1:
		if (currentMillis - previousMillis >= acceleration) {
			previousMillis = currentMillis;

			i1 = i1 + StepAccelerazioneRotate;
			i2 = i2 + StepAccelerazioneRotate;

			i1 = min(i1, speed);
			i2 = min(i2, speed);

		}//end if current millis
		break;

	}//and switchcase

	analogWrite(_pwmADX, i1);//assegno velocità mot 1
	analogWrite(_pwmBSX, i2);//assegno velocità mot 2 

}//end void right

 //------------------------------------------------------------------------------------
 //BACK
 //------------------------------------------------------------------------------------

void MotoreClass::back(int speed, int acceleration, float delta, int StepAccelerazioneBack, int vmin)
{
	countleft = 0; //resetta il contatore che controlla il conteggio di accelerazione
	countright = 0;
	countstraight = 0;

	digitalWrite(_standby, HIGH);//attiva i motori disabilitando lo standby
	digitalWrite(_AIN1DX, A);
	digitalWrite(_AIN2DX, B);
	digitalWrite(_BIN1SX, B);
	digitalWrite(_BIN2SX, A);

	currentMillis = millis();

	switch (countback) { //verifica se l'accelerazione è già stata inizializzata, se no costringe la velocità al valore impostato
	case 0:
		i1 = vmin;    //definita nel file .h
		i2 = vmin;    //definita nel file .h
		countback = 1;  //impone che l'inizializzazione dell'accelerazione è stata effettuata
		break;
		//case 0

	case 1:
		if (currentMillis - previousMillis >= acceleration) {  //conrolla se è passato il tempo minimo dell'intervallo prestabilito
			previousMillis = currentMillis;               //se si aggiorna l'istante dell'ultimo aggiornameto

			if (delta != 0) {

				if (delta<0) {
					delta = abs(delta);
					deltaAcceleration = map(delta, 10, speed, 1, 10);

					i1 = i1 + (StepAccelerazioneBack / deltaAcceleration);
					i2 = i2 + StepAccelerazioneBack;

					i1 = min(i1, speed - delta); // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					i2 = min(i2, speed);       // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					break;
				}//end if delta > 0

				if (delta>0) {
					deltaAcceleration = map(delta, 10, speed, 1, 10);

					i1 = i1 + StepAccelerazioneBack;
					i2 = i2 + (StepAccelerazioneBack / deltaAcceleration);

					i1 = min(i1, speed);        // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					i2 = min(i2, speed - delta);  // per una maggior precisione nel movimento si introduce un rallentamento della velocità massima
					break;
				}//end if delta < 0 

			}//end if delta != 0

			else {                               //nel caso che il delta sia 0, le accelerazioni delle 2 ruote saranno identiche
				i1 = i1 + StepAccelerazioneBack;
				i2 = i2 + StepAccelerazioneBack;
				i1 = min(i1, speed);
				i2 = min(i2, speed);
			}//end else
		}//end else current millis
		break;

	}//and switchcase

	analogWrite(_pwmADX, i2);//assegno velocità mot 1
	analogWrite(_pwmBSX, i1);//assegno velocità mot 2 
}//end void back
 //------------------------------------------------------------------------------------
 //WAIT
 //------------------------------------------------------------------------------------

void MotoreClass::wait(int duration)
{
	countleft = 0; //resetta il contatore che controlla il conteggio di accelerazione
	countright = 0;
	countstraight = 0;
	countback = 0;

	digitalWrite(_standby, LOW);//attiva i motori disabilitando lo standby
	delay(duration);
}//end void wait

MotoreClass Motore;
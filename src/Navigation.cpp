// 
// 
// 

#include "Navigation.h"
#include "Motore.h"
#include "Sensors.h"
#include "Buzzer.h"
#include "SequenzeLed.h"
#include "Bluetooth.h"


//------------------------------------------------------------------------------------
//DEFINIZONE NOME DEI PIN FISICI
//------------------------------------------------------------------------------------

//ToggleSwitch pin
#define toggleSwitchPin 3 //pin interupt avvio
#define toggleSwitch2 52 //pin per avvio sequenza di inizializzazione
//Motori
#define AIN1 28
#define AIN2 26
#define PWMA 2
#define BIN1 32
#define BIN2 34
#define PWMB 4
#define stby 30
//Ping DX
#define triggDX 46
#define echoDX 48
//Ping SX
#define triggSX 44
#define echoSX 42
//Infrared
#define rxDX 50
#define rxSX 14
//Fotoresistori  
#define fotoDX A10
#define fotoSX A8
#define fotoC A9
//Gas
#define gasPin A11
//led PCB
#define ledRxDX 40
#define ledRxSX 38
#define ledPingDX 8
#define ledPingSX 12
#define ledFotoDX 7
#define ledFotoSX 11
#define ledFotoC 10
#define ledGas 9
//buzzer
#define pinBuzzer 13
//luci scocca
#define Led_Fendinebbia 45
#define Led_Abaglianti 5
#define Led_FrecciaDX 43
#define Led_FrecciaSX 23
#define Led_Stop 6

//pin pause per interupt 3




//------------------------------------------------------------------------------------
//COSANTI E VARIABILI PER LA GESTIONE DEI MOTPRI
//------------------------------------------------------------------------------------


//--------------------MOTORI------------------
//configurazioni motore.h
#define velMin1 50 //per definire la velocit� minima dei motori avanti e indietro
#define velMin2 60 //per definire la velocit� minima dei motori destra e sinistra
#define velMin3 80 //per definire la velocit� minima dei motori avanti e indietro in caso di luce

#define StepAccelerazioneStraight 5 //definisce di quanto deve incrementare ogni ciclo il valore del PWM
#define StepAccelerazioneBack 3 //definisce di quanto deve incrementare ogni ciclo il valore del PWM
#define StepAccelerazioneRotate 3 //definisce di quanto deve incrementare ogni ciclo il valore del PWM

#define TEMPOINCREMENTO 4 //ogni quanto deve incremetare il valore del pwm ai motori (ms) 
#define speedReduction 8 //definisce di quanto viene divisa la velocit� massima in caso di rotazione in streight
#define noSpeedReduction 1 //non introduce una riduzione della velocit� in quanto impone speed reduction = speed all'interno della classe motori

//velocit� massima dei motori in caso di assenza ostacoli VELOCITA MASSIMA che pu� raggiungere il robot
#define velocitaMax    255

//velocit� massima definita nell'eq ALTA VELOCITA non effettua curve brusche in questa modalit�
#define velocitaMaxD   250
#define velocitaMaxS   250


#define NOSTOP 45//impedisce che il motore opposto all'ostacolo si fermi completamente impedendo di scendere
//sotto di una certa velocit� l'equazioned della retta che controlla la Velocit�

//velocit� massima e delta rotazione ostacoli pericolosi MEDIA VELOCITA
#define velocitaMaxHD  185
#define eqHD  -170
#define velocitaMaxHS  185
#define eqHS   170

//velocit� massima e delta rotazione definita per la ricerca nel ciclo delle luci BASSA VELOCIA
#define velocitaMaxLD  100
#define eqLD  -50
#define velocitaMaxLS  100
#define eqLS   50

#define velocitaMaxLLD  80
#define eqLLD  -40
#define velocitaMaxLLS  80
#define eqLLS   40
//--------------------PING------------------
//dastanza massima ping
#define DistDxMax 13
#define CorrezionePingDX 1
#define DistSxMax 12
#define CorrezionePingSX 0

//--------------------GAS E LUCE------------------
//Imposta la sogia minima e massima della luce oltre al quale � considerato rumore o errore
#define LuxMIN 350
#define LuxMAX 1024  
//definisce entro quanto tempo deve smettere di ruotare in quanto le foto resistenze � da troppo che non rilevano
#define tGuardiaFoto1 250
//definisce per quanto tempo avanzare dopo che la precedente rotazione ha smesso di rilevare
#define tGuardiaFoto2 300
//definisce per quanto tempo continua ad avvicinarsi una volta individuato l'ostacolo nel ciclo luce per efettuare la rilevazione del gas
#define tAvvicinamentoStop 300

//Imposta la sogia minima del gas sotto al quale � considerato rumore
#define GasMIN 300
#define GasMAX 1024
//definisce per quanto tempo deve ruotare o a destra o a sinistra alla ricerca del gas
#define tRicercaGas1 900 
//definisce di quanto deve ruotare a destra una volta terminate le rilevazioni
#define tRotazioneEscape 900 
//definisce entro quanto tempo segnala errore durate il rientro in posizione su fotoC dopo la rilevasione si a destra che a sinistra
#define tRientroPosizione 3000 
//Valore per cui si � certi che ci sia un boccio dell'alchool
#define rilevamentoGasAlto 550 
//valore sotto al quale il robottino riprende a cercare, secessario per scaricare il gas depositato nel sensore
#define valueGasReset 400

//bluetooth
#define tBtPrint 1000 //definisce ogni quanti secondi deve stampare il bluetooth












//------------------------------------------------------------------------------------
//NAVIGATION::INIZIALIZATE
//------------------------------------------------------------------------------------
void NavigationClass::inizializate() {

	//inizializzazione pin motori e ping
	Motore.motoreDX(PWMA, AIN1, AIN2);       //PWMA,AIN1,AIN2 config pin della libreria motore
	Motore.motoreSX(PWMB, BIN1, BIN2);       //PWMB,BIN1,BIN2 config pin della libreria motore
	Motore.standby(stby);                  //pin standby    config pin della libreria motore

	Ping.inizializateDX(triggDX, echoDX);   //trigg,echo     config pin della libreria ping
	Ping.inizializateSX(triggSX, echoSX);   //trigg,echo     config pin della libreria ping

	Fotoresistor.inizializate(fotoDX, fotoSX, fotoC);

	Gas.inizializate(gasPin);

	Buzzer.inizializate(pinBuzzer);
	//inizializzazione pin per i sensori infrarossi

	pinMode(rxSX, INPUT_PULLUP);

	pinMode(ledRxDX, OUTPUT);
	pinMode(ledRxSX, OUTPUT);
	pinMode(ledPingDX, OUTPUT);
	pinMode(ledPingSX, OUTPUT);
	pinMode(ledFotoDX, OUTPUT);
	pinMode(ledFotoSX, OUTPUT);
	pinMode(ledFotoC, OUTPUT);
	pinMode(ledGas, OUTPUT);

	pinMode(Led_Fendinebbia, OUTPUT);
	pinMode(Led_Abaglianti, OUTPUT);
	pinMode(Led_FrecciaDX, OUTPUT);
	pinMode(Led_FrecciaSX, OUTPUT);
	pinMode(Led_Stop, OUTPUT);

	//inizializzazione pin per toggleSwitchPin
	pinMode(toggleSwitchPin, INPUT_PULLUP);

}//end inizializate

 //------------------------------------------------------------------------------------
 //START::PULSE
 //------------------------------------------------------------------------------------
void StartClass::pulse() {                     //il defaul della variabile toggleSwitch all'accensione � 0
  
	toggleSwitch = !toggleSwitch;          //inverte lo stato della variabile toggleSwitch a chiamata dell'iterupt
  
	digitalWrite(Led_Fendinebbia, HIGH);
	digitalWrite(Led_Abaglianti, HIGH);
	delay(300);
	digitalWrite(Led_Fendinebbia, LOW);
	digitalWrite(Led_Abaglianti, LOW);

	Motore.wait(1);
 
	Start.start();

}//end void pulse

 //------------------------------------------------------------------------------------
 //NAVIGATION::START
 //------------------------------------------------------------------------------------
void StartClass::start() {                                     //il defaul della variabile toggleSwitch all'accensione � 0

	if (testFatto == 0) {
		SequenzeLed.test(ledPingDX, ledPingSX, ledRxDX, ledRxSX, ledFotoDX, ledFotoSX, ledFotoC, ledGas, Led_Fendinebbia, Led_Abaglianti, Led_FrecciaDX, Led_FrecciaSX, Led_Stop);
		testFatto = 1;
	}// end if testFatto==0

	if (toggleSwitch == 1) {                                   //controlla lo stato della variabile toggleSwitch

				if (rotazioneCasuale == 1) {
					Navigation.move();
          
          Bluetooth.stato=3; // go
          Navigation.updateSensors();
          
					digitalWrite(Led_Abaglianti, LOW);
					digitalWrite(Led_Fendinebbia, LOW);
					analogWrite(Led_Abaglianti, 50);
					analogWrite(Led_Fendinebbia, 50);
				}//end if  rotazione casule == 1

				else {
					SequenzeLed.rotazione();
					Motore.wait(1);
					rotazioneCasuale = 1;
				}//end else
					//se � uno fa muovere il robottino  

	}//end if toggleSwitch==1
	else {
			Motore.wait(1);        //se � 0 blocca i motori, lasciano inalterata la capacit� del rilevamento ostacoli
     
      Bluetooth.stato=2; //ready
      
			Navigation.updateSensors();
 
			Buzzer.playMelody(1);  //la canzone viene scritta in base alle pause e all'intensit�, vedere buzzer.cpp

			digitalWrite(Led_Abaglianti, HIGH);
			digitalWrite(Led_Fendinebbia, HIGH);
			digitalWrite(Led_Stop, HIGH);
	}//end else

}//END VOID START

 //------------------------------------------------------------------------------------
 //NAVIGATION::UPDATESENSOR
 //------------------------------------------------------------------------------------
void NavigationClass::updateSensors() {

	//contolla i dati delle fotoresistenze per tenere i led sempre aggiornati ed evitare di chiamare pi� volte le stesse cose dentro le funzioni
	N_fotoresistor.cerca();
	//contolla i dati del sensore del gas
	N_gas.cerca();

	vRxDX = digitalRead(rxDX); //legge sensore ottico destro ciclicamente
	vRxDX = !vRxDX; //in quanto questo sensore da 0 in uscita in presenza ostacolo inverto il valore
	if (vRxDX == 1) {
		digitalWrite(ledRxDX, HIGH);
	}
	else {
		digitalWrite(ledRxDX, LOW);
	}


	vRxSX = digitalRead(rxSX); //legge sensore ottico sinistro ciclicamente
	vRxSX = !vRxSX; //in quanto questo sensore da 0 in uscita in presenza ostacolo inverto il valore
	if (vRxSX == 1) {
		digitalWrite(ledRxSX, HIGH);
	}
	else {
		digitalWrite(ledRxSX, LOW);
	}


	Ping.distanceDX(distanzaDX); //carica il valore letto tramite la classe Ping su una Variabile globale della classe Navigation
	Ping.distanceSX(distanzaSX);

	//controlla se il ping sinistro rileva un ostacolo nel range impostato
	if (distanzaDX >= 1 && distanzaDX <= DistDxMax) {
		vPingDX = 1;
		valuePWM = distanzaDX;
		valuePWM = map(valuePWM, DistSxMax, 1, 0, 250);
		analogWrite(ledPingDX, valuePWM);
	}//end if distanzaDX>=1 && distanzaDX<=DistDxMax
	else {
		vPingDX = 0;
		analogWrite(ledPingDX, 0);
	}

	//controlla se il ping destro rileva un ostacolo nel range impostato
	if (distanzaSX >= 1 && distanzaSX <= DistSxMax) {
		vPingSX = 1;
		valuePWM = distanzaSX;
		valuePWM = map(valuePWM, DistSxMax, 1, 0, 250);
		analogWrite(ledPingSX, valuePWM);
	}//end if distanzaSX>=1 && distanzaSX<=DistSxMax
	else {
		vPingSX = 0;
		analogWrite(ledPingSX, 0);
	}

	deltaPingDxSx = (distanzaDX+CorrezionePingDX) - (distanzaSX+CorrezionePingSX); //restituice quale ping � pi� distante da un ostacolo
											 //NEGATIVO vicino XD ----- POSITIVO vicino SX

	int lettura = (vPingDX << 3) | (vPingSX << 2) | (vRxSX << 1) | vRxDX; //converte i valori dei 4 sensori in un unico numero binario inserendo i bit nelle posizioni assegnate

																		  //controllo dei casi in cui sono attivi i vari sensori controllati ciclicamente e assegnazione di un nome tramite la funzione enum

																		  //    PingDX,PingSX,rxSX,rxDX  (valore dei bit secondo le posizioni)

	if (lettura == 0b0000) posizioneOstacolo = vuoto;         // (nessun sensore attivo)
	if (lettura == 0b0001) posizioneOstacolo = gradi70;       // (rxDX)
	if (lettura == 0b0010) posizioneOstacolo = gradi110;      // (rxSX)
	if (lettura == 0b0011) posizioneOstacolo = gradi90;       // (rxSX,rxDX)

	if (lettura == 0b0100) posizioneOstacolo = gradi135;      // (PingSX)
	if (lettura == 0b0101) posizioneOstacolo = casopSXrDX;    // (PingSX,rxDX)
	if (lettura == 0b0110) posizioneOstacolo = gradi120;      // (PingSX,rxSX)
	if (lettura == 0b0111) posizioneOstacolo = casopSXrSXrDX; // (PingSX,rxSX,rxDX)

	if (lettura == 0b1000) posizioneOstacolo = gradi45;       // (PingDX)
	if (lettura == 0b1001) posizioneOstacolo = gradi60;       // (PingDX,rxDX)
	if (lettura == 0b1010) posizioneOstacolo = casopDXrSX;    // (PingDX,rxSX)
	if (lettura == 0b1011) posizioneOstacolo = casopDXrSXrDX; // (PingDX,rxSX,rxDX)

	if (lettura == 0b1100) posizioneOstacolo = casopDXpSX;    // (PingDX,PingSX)
	if (lettura == 0b1101) posizioneOstacolo = casopDXpSXrDX; // (PingDX,PingSX,rxDX)
	if (lettura == 0b1110) posizioneOstacolo = casopDXpSXrSX; // (PingDX,PingSX,rxSX)
	if (lettura == 0b1111) posizioneOstacolo = casoALL;       // (PingDX,PingSX,rxSX,rxDX)

  //stampa tutti i valori nell'interfaccia grafica dopo averli aggiornati, con intervallo tBtPrint
  Bluetooth.BtPrint(tBtPrint);

}//end void update sensor

 //------------------------------------------------------------------------------------
 //MOVE  
 //------------------------------------------------------------------------------------
void NavigationClass::move() {

	//in base alle condizine imposte dai sensori attua le opportune correzioni della traiettoria
	Navigation.updateSensors(); //verifica la combinazione di sensori attivi aggiornando cos� posizione ostacolo
					 
	//con delta POSITIVO il robot gira a destra, con delta NEGATIVO il robot gira a sinistra
          
	float eqD = map(distanzaSX, 1, DistSxMax, -(velocitaMaxS - NOSTOP), -5);  //negativo
	float eqS = map(distanzaDX, 1, DistDxMax, (velocitaMaxD - NOSTOP), 5);  //positivo

	switch (posizioneOstacolo) {

		//------------------------------------

	case vuoto:
		//Serial.println("vuoto");

		Motore.straight(velocitaMax, TEMPOINCREMENTO, 0, speedReduction, StepAccelerazioneStraight, velMin1);

		N_fotoresistor.move();

		break;
		//end case vuoto

		//------------------------------------

	case gradi70:
		//Serial.println("gradi70");

		while (vPingSX == 1 || vRxDX == 1 || vRxSX == 1) {
			//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
			Motore.left(velocitaMaxHS, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vRxDX==1

		break;
		//end case gradi70

		//------------------------------------ 

	case gradi110:
		//Serial.println("gradi110");

		while (vPingDX == 1 || vRxDX == 1 || vRxSX == 1) {
			//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
			Motore.right(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}////end while vRxSX==1

		break;
		//end case gradi110

		//------------------------------------   

	case gradi90:
		//Serial.println("gradi90");

		if (deltaPingDxSx >= 0) {    //delta ping corrisponde a distanzaDX-distanzaSX
			while (vPingDX == 1 || vRxDX == 1 || vRxSX == 1) {
				Motore.right(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

				Navigation.updateSensors();
				N_fotoresistor.move();
			}//end while vRxSX==1
		}//end if deltaPing <=0
		else {
			while (vPingSX == 1 || vRxDX == 1 || vRxSX == 1) {
				Motore.left(velocitaMaxHS, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

				Navigation.updateSensors();
				N_fotoresistor.move();
			}//end while vRxDX==1
		}//end else  

		break;
		//end case gradi90

		//------------------------------------

	case gradi135:
		//Serial.println("gradi135");

		delta = eqD;
		//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
		Motore.straight(velocitaMaxD, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);

		N_fotoresistor.move();

		break;
		//end case gradi135

		//------------------------------------

	case casopSXrDX:
		//Serial.println("casopSXrDX");

		while (vRxDX == 1 || vRxSX == 1) {
			Motore.right(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingSX==1

		break;
		//end case casopSXrDX

		//------------------------------------

	case gradi120:
		//Serial.println("gradi120");

		delta = eqD;
		//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
		Motore.straight(velocitaMaxD, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);

		N_fotoresistor.move();

		break;
		//end case gradi120

		//------------------------------------

	case casopSXrSXrDX:
		//Serial.println("casopSXrSXrDX");

		while (vRxDX == 1 || vRxSX == 1) {
			delta = eqHS;
			Motore.back(velocitaMaxHS, TEMPOINCREMENTO, delta, StepAccelerazioneBack, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingSX==1 || vRxSX==1

		break;
		//end case casopSXrSXrDX

		//------------------------------------

	case gradi45:
		//Serial.println("gradi45");

		delta = eqS;
		//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
		Motore.straight(velocitaMaxS, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);

		Navigation.updateSensors();
		N_fotoresistor.move();

		break;
		//end case gradi45

		//------------------------------------

	case gradi60:
		//Serial.println("gradi60");

		delta = eqS;
		//funzione che restituisce un delta pi� alto all'avvicinarsi dell'ostacolo (equazione retta con calcolo coefficente angolare)
		Motore.straight(velocitaMaxS, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);

		Navigation.updateSensors();
		N_fotoresistor.move();

		break;
		//end case gradi60

		//------------------------------------  

	case casopDXrSX:
		//Serial.println("casopDXrSX");

		while (vRxDX == 1 || vRxSX == 1) {
			Motore.left(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingDX==1


		break;
		//end case casopDXrSX

		//------------------------------------

	case casopDXrSXrDX:
		//Serial.println("casopDXrSXrDX");

		while (vRxDX == 1 || vRxSX == 1) {
			delta = eqHD;
			Motore.back(velocitaMaxHD, TEMPOINCREMENTO, delta, StepAccelerazioneBack, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingDX==1 || vRxDX==1

		break;
		//end case casopDXrSXrDX


		//------------------------------------

	case casopDXpSX:
		//Serial.println("casopDXpSX");

		delta = eqD;
		Motore.straight(velocitaMaxD, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);
		delta = eqS;
		Motore.straight(velocitaMaxS, TEMPOINCREMENTO, delta, speedReduction, StepAccelerazioneStraight, velMin1);

		Navigation.updateSensors();
		N_fotoresistor.move();
		break;
		//end case casopSXpDX

		//------------------------------------

	case casopDXpSXrDX:
		//Serial.println("casopDXpSXrDX");

		while (vPingSX == 1 || vRxDX == 1 || vRxSX == 1) {
			Motore.left(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingSX==1


		break;
		//end case casopDXpSXrDX

		//------------------------------------

	case casopDXpSXrSX:
		//Serial.println("casopDXpSXrSX");

		while (vPingDX == 1 || vRxDX == 1 || vRxSX == 1) {
			Motore.right(velocitaMaxHD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin2);

			Navigation.updateSensors();
			N_fotoresistor.move();
		}//end while vPingDX==1

		break;
		//end case casopDXpSXrSX

		//------------------------------------

	case casoALL:
		//Serial.println("casoALL");

		if (deltaPingDxSx >= 0) { //delta ping Negativo vicino DX quindi gira a SX
			while (vPingSX == 1 || vPingDX == 1 || vRxDX == 1 || vRxSX == 1) { //fin quando i sensori di destra prendono continua a girare
				delta = eqHS;
				Motore.back(velocitaMaxHS, TEMPOINCREMENTO, delta, StepAccelerazioneBack, velMin2);

				Navigation.updateSensors();
				N_fotoresistor.move();;
			}//end while vPingSX==1 || vRxSX==1
		}//end if deltaPing <=0
		else {
			while (vPingDX == 1 || vPingSX == 1 || vRxDX == 1 || vRxSX == 1) {
				delta = eqHD;
				Motore.back(velocitaMaxHD, TEMPOINCREMENTO, delta, StepAccelerazioneBack, velMin2);

				Navigation.updateSensors();
				N_fotoresistor.move();
			}//end while vPingDX==1 || vRxDX==1
		}//end else

		break;
		//end case casoALL

	}//end switch case posizione ostacolo


}//end void move



 //------------------------------------------------------------------------------------
 //GAS::CERCA
 //------------------------------------------------------------------------------------

void N_GasClass::cerca() {
  
	Gas.lettura(valueGas);

	//controlla se il sensore del gas rileva vapori con intensit� nel range impostato
	if (valueGas >= GasMIN && valueGas <= GasMAX) {
		vGas = 1;
		valuePWM = valueGas;
		valuePWM = map(valuePWM, GasMIN, GasMAX, 5, 250);
		analogWrite(ledGas, valuePWM);
	}//end if valueGas>=GasMIN && valueGas<=GasMAX
	else {
		vGas = 0;
		analogWrite(ledGas, 0);
	}//end else

	 //verifica se il valore del sensore del gas � calato
	if (valueGas>valueGASprecedente) {
		dGas = 1;
	}//end if valueC>valueCprecedente
	else {
		dGas = 0;
	}//end else valueC>valueCprecedente
	valueGASprecedente = valueGas;

}//end void cerca

 //------------------------------------------------------------------------------------
 //GAS::MOVE
 //------------------------------------------------------------------------------------

void N_GasClass::move() {

  Bluetooth.stato=5; // find gas
  
	N_gas.cerca();

	//fase1
	currentMillis = millis();
	previousMillis = currentMillis;

	while (currentMillis - previousMillis <= tRicercaGas1) {  //conrolla se � passato il tempo di guardia per controllare a sinistra � finito

		Navigation.updateSensors();
		currentMillis = millis();

		Motore.left(velocitaMaxLLS, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin3);

		if(vGas == 1){
        if (valueGas>rilevamentoGasAlto) {
          Motore.wait(1);
          goto fine;
          break;
        }//end if vGas == 1
     }//end if gas == 1
	}//end while currentMillis - previousMillis >= tGuardia

	 //ritorno in posizione 
	currentMillis = millis();
	previousMillis = currentMillis;
	Navigation.updateSensors();

	while (N_fotoresistor.vFotoC == 0) {
    
		Navigation.updateSensors();
		currentMillis = millis();

		Motore.right(velocitaMaxLLD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin3);

		if (currentMillis - previousMillis >= tRientroPosizione) {
			break;
		}//end if currentMillis - previousMillis <= tRientroPosizione

	}//end while dFotoC == 0

	Motore.wait(500);

	 //fase2   
	currentMillis = millis();
	previousMillis = currentMillis;

	while (currentMillis - previousMillis <= tRicercaGas1) {  //conrolla se � passato il tempo di guardia per controllare a sinistra � finito

		Navigation.updateSensors();
		currentMillis = millis();

		Motore.right(velocitaMaxLLD, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin3);
   
    if(vGas == 1){
    		if (valueGas>rilevamentoGasAlto) {
    			Motore.wait(1);
    			goto fine;
    			break;
    		}//end if vGas == 1
     }//end if gas == 1
	}//end while currentMillis - previousMillis >= tGuardia

	 //ritorno in posizione 
	currentMillis = millis();
	previousMillis = currentMillis;
	Navigation.updateSensors();

	while (N_fotoresistor.vFotoC == 0) {

		Navigation.updateSensors();
		currentMillis = millis();

		Motore.left(velocitaMaxLLS, TEMPOINCREMENTO, 0, StepAccelerazioneRotate, velMin3);

		if (currentMillis - previousMillis >= tRientroPosizione) {
			Motore.wait(1);
			break;
		}//end if currentMillis - previousMillis <= tRientroPosizione

	}//end while dFotoC == 0

fine:
	Navigation.updateSensors();

	if (vGas == 1) {
    Motore.wait(1);
		gasTrovato();
	}//end if

	else {
    Motore.wait(1);
		gasNonTrovato();
	}//end else


}//end move

 //------------------------------------------------------------------------------------
 //N_GASCLASS::GASTROVATO
 //------------------------------------------------------------------------------------

void N_GasClass::gasTrovato() {

  Bluetooth.stato=5; // find gas
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

  Bluetooth.stato=9; //both found
  Navigation.updateSensors();
  
	for (int i = 0; i<tRotazioneEscape; i++) {
		Motore.right(200, 5, 0, 1, velMin1);
		delay(1);
	}//end for

	Motore.wait(1);
	while (valueGas > valueGasReset) { //aspetta che il sensore del gas torni a 0 per evitare di rilevare vapori fantasma
		N_gas.cerca();
		digitalWrite(Led_Stop, HIGH);
		delay(50);
		digitalWrite(Led_Stop, LOW);
		delay(50);
		Buzzer.playMelody(3);
    Motore.wait(1);
    Navigation.updateSensors();
	}//end while

}//end vosd gas trovato

 //------------------------------------------------------------------------------------
 //GAS::GASNONTROVATO
 //------------------------------------------------------------------------------------

void N_GasClass::gasNonTrovato() {

  Bluetooth.stato=10; //no gas
  Navigation.updateSensors();
  
	Motore.wait(1);
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

	for (int i = 0; i<tRotazioneEscape; i++) {
		Motore.right(200, 5, 0, 1, velMin1);
		delay(1);
	}//end for
}//end void gas non trovato


NavigationClass Navigation;
StartClass Start;
N_FotoresistorClass N_fotoresistor;
N_GasClass N_gas;

// Navigation.h

#ifndef _NAVIGATION_h
#define _NAVIGATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class StartClass 
{
 protected:

	//PULSANTE PER L'ARRESTO DEL ROBOT VOID PULSE
	bool toggleSwitch = 0;//variabile per il pulsante di start&stop (0 bloccato 1 in movimento)
	bool testFatto = 0;   //veriabile per eseguire il test dopo il reset (0 lo fa 1 lo esclude)
	bool rotazioneCasuale = 0; //variabile che permette di fare la rotazione casuale solo al primo avvio (0 lo fa 1 lo esclude)

 public:
	void pulse();
	void start();
 
};//end naviation

extern StartClass Start;

//------------------------------------------------------------------------------------

class NavigationClass 
{
 protected:
	//enum globale per update sensore e move
	//considero i gradi all'interno dell'enum come la circonferenza goniometrica
	enum ostacolo { vuoto, gradi70, gradi110, gradi90, gradi135, casopSXrDX, gradi120, casopSXrSXrDX, gradi45, gradi60, casopDXrSX, casopDXrSXrDX, casopDXpSX, casopDXpSXrDX, casopDXpSXrSX, casoALL };
	ostacolo posizioneOstacolo;
	//posizione ostacolo per capire dove legge l'ostacolo di tipo ostacolo dell'enumostacolo posizioneOstacolo;

	
	//necessario per mantenere una rotazione in caso rilevamento ostacoli multipli
	bool giratoDX;
	//necessario per mantenere una rotazione in caso rilevamento ostacoli multipli
	bool giratoSX;

	int valuePWM; //per il controllo della luminosit� dei led

	int delta;

 public:
	void inizializate();
	void updateSensors();
	void move();
    
	//COSTATNTI E VARIABILI PER LA GESTIONE DEL PING
	float distanzaDX; //viene dichiarata una variabile per caricare il valore letto dai ping
	float distanzaSX;
    float deltaPingDxSx;

	//stato dei ping
    bool vPingDX;
	bool vPingSX;

	//stato dei sensori infrarossi
	bool vRxDX;
	bool vRxSX;
	 
};

extern NavigationClass Navigation;

//----------------------------------------------------------------------------------

class N_FotoresistorClass 
{
 protected:
	int valuePWM;

	int delta;

	float deltaFotoDxSx;

	
	
	float valueDXprecedente;
	float valueSXprecedente;
	float valueCprecedente;

	enum Luce { vuoto, gradi40, gradi90, gradi65, gradi140, fSXfDX, gradi115, casoALL };
	Luce fonteLuce;

	unsigned long currentMillis;
	unsigned long previousMillis;

 public:
	void cerca();
	void move();
	void trovata();

    float valueDX;
	float valueSX;
	float valueC;

    //Variabili per il controllo dei valori
	bool dFotoDX;
	bool dFotoSX;
	bool dFotoC;
    bool vFotoDX;
	bool vFotoSX;
	bool vFotoC;
};

extern N_FotoresistorClass N_fotoresistor;

//----------------------------------------------------------------------------------

class N_GasClass 
{
 protected:

	int delta;

	
	bool vGas;
	int valueGASprecedente;
	bool dGas;

	int valuePWM;

	unsigned long currentMillis;
	unsigned long previousMillis;
 public:
	void cerca();
	void move();

	float valueGas;

	void gasTrovato();
	void gasNonTrovato();

};

extern N_GasClass N_gas;

#endif

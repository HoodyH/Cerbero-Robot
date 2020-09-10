/*
 Name:		RobottinoCerbero.ino
 Created:	22/01/2017 11:34:52
 Author:	Simone Not
 Version:   2.2.1
*/

//LIBRERIE
#include "Bluetooth.h"
#include "SequenzeLed.h"
#include "Sensors.h"
#include "Navigation.h"
#include "Motore.h"
#include "Buzzer.h"


/*
 Per il corretto funzionamento è da eseguire una taratura dei sensori

 Luce: Tarare le costanti di luminosità massima e di luminosità minima

 Ping Tarare le distanze a seconda dello spazio di manovra
 Infrarossi tarare le costanti che agiscono sulla agressività della rotazione in base a quando
 il sensore percepisce l'ostacolo

 Gas: tarare i valori di massimo e di minimo

 Impostare le canoni direttamente nella libreria
*/

//--------------------------------------------------------------------------------
//INIZIALIZZAZIONE
//--------------------------------------------------------------------------------

void setup() {
	Navigation.inizializate();// inizializza tutti i pin nella libreria navigation

	//inizializza l'interupt per il pulsante di avvio e di arresto
	attachInterrupt(1, button, RISING); //inizializza interupt su pin 3
	//Inizializzazione della comunicazione seriale
	Serial.begin(9600);
	Serial1.begin(115200); //per il bluetooth
    //inizializzazione trasmissione da arduino a bluetooth (seriale via cavo)

}//FINE INIZIALIZZAZIONE

 //--------------------------------------------------------------------------------
 //LOOP MAIN
 //--------------------------------------------------------------------------------

void loop() {
	Start.start();
}//FINE LOOP MAIN

 //--------------------------------------------------------------------------------
 //ACCESSO DELL'INTERUPT ALLE LIBRERIE 
 //--------------------------------------------------------------------------------
void button() {
	Start.pulse();
}
//--------------------------------------------------------------------------------
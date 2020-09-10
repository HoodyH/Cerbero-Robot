// 
// 
// 

#include "Buzzer.h"

//Canzoni da riprodurre

//1 lettera per la selezione della canzone
int wait[] = { NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5, 0, 0 };
int DurationsWait[] = { 4, 8, 8, 4, 4, 4, 4, 4, 1, 1 };
int nNoteWait = 10;

//2 lettera per la selezione della canzone
int luce[] = { NOTE_D5, NOTE_D5, NOTE_D6 };
int DurationsLuce[] = { 2, 8, 8 };
int nNoteLuce = 3;

//3 lettera per la selezione della canzone
int gasMelody[] = { NOTE_A5, NOTE_A5, NOTE_A6 };
int DurationsGasMelody[] = { 2, 8, 8 };
int nNoteGasMelody = 3;

//4 lettera per la selezione della canzone
int ostacolo[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};
int DurationsOstacolo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};
int nNoteOstacolo = 78;

//5 lettera per la selezione della canzone
int errore[] = { NOTE_A6, NOTE_A5, NOTE_A4, NOTE_A4 };
int DurationsErrore[] = { 2, 4, 4, 8 };
int nNoteErrore = 4;

//6 riprodotta durante il funzionamento
int canzoneCiclo[] = { NOTE_A5, NOTE_AS5, NOTE_D5, NOTE_G5, NOTE_AS5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_AS5, NOTE_D5, NOTE_DS5, NOTE_G5, NOTE_D5, NOTE_C5, 0 };
int DurationCanzoneCiclo[] = { 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 };
int nNoteCanzoneCiclo = 18;

//7 Segnala pronto per il primo avvio
int canzoneFirst[] = { NOTE_B3, NOTE_C4, 0, 0 };
int DurationCanzoneFirst[] = { 4, 4, 4, 4 };
int nNoteCanzoneFirst = 4;

//8 Segnala go
int go[] = { NOTE_B3 };
int DurationGo[] = { 1 };
int nNoteGo = 1;

//--------------------------------------------------------------------------------
//BUZZERCLASS:INIZIALIZATE
//--------------------------------------------------------------------------------

void BuzzerClass::inizializate(int pinBuzzer) {

	_pinBuzzer = pinBuzzer;

}//end void inizializate

 //--------------------------------------------------------------------------------
 //PLAYNOTE
 //--------------------------------------------------------------------------------

void BuzzerClass::playNote(int period, word length) {

	tone(_pinBuzzer, period, length);
	delay(length);

}//end void playNote

 //--------------------------------------------------------------------------------
 //PLAYMELODY
 //--------------------------------------------------------------------------------

void BuzzerClass::playMelody(int select) {

	switch (select) {

	case 1:
		for (int thisNote = 0; thisNote < nNoteWait; thisNote++) {
			int time = 1000 / DurationsWait[thisNote];
			playNote(wait[thisNote], time);
		}//end for
		break;

	case 2:
		for (int thisNote = 0; thisNote < nNoteLuce; thisNote++) {
			int time = 1000 / DurationsLuce[thisNote];
			playNote(luce[thisNote], time);
		}//end for
		break;

	case 3:;
		for (int thisNote = 0; thisNote < nNoteGasMelody; thisNote++) {
			int time = 1000 / DurationsGasMelody[thisNote];
			playNote(gasMelody[thisNote], time);
		}//end for
		break;

	case 4:
		for (int thisNote = 0; thisNote < nNoteOstacolo; thisNote++) {
			int time = 1000 / DurationsOstacolo[thisNote];
			playNote(ostacolo[thisNote], time);
		}//end for
		break;

	case 5:
		for (int thisNote = 0; thisNote < nNoteErrore; thisNote++) {
			int time = 1000 / DurationsErrore[thisNote];
			playNote(errore[thisNote], time);
		}//end for
		break;

	case 6:
		for (int thisNote = 0; thisNote < nNoteCanzoneFirst; thisNote++) {
			int time = 1000 / DurationCanzoneFirst[thisNote];
			playNote(canzoneFirst[thisNote], time);
		}//end for
		break;

	case 7:
		for (int thisNote = 0; thisNote < nNoteGo; thisNote++) {
			int time = 1000 / DurationGo[thisNote];
			playNote(go[thisNote], time);
		}//end for
		break;

	}//end switch script

}//end void play melody

 //--------------------------------------------------------------------------------
 //PLAYMELODYLOOP
 //--------------------------------------------------------------------------------

void BuzzerClass::playMelodyLoop() {

	unsigned long currentMillis = millis();
	int time = 1000 / DurationsErrore[thisNoteLoop];

	if (currentMillis - previousMillis >= time) {
		previousMillis = currentMillis;

		if (thisNoteLoop < nNoteCanzoneCiclo) {

			playNote(canzoneCiclo[thisNoteLoop], time);
			nNoteCanzoneCiclo++;

		}//end if thisNoteLoop < nNoteCanzoneCiclo

	}//end if currentMillis - previousMillis >= time

}//end void buzzer


BuzzerClass Buzzer;


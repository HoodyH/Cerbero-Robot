// 
// 
// 

#include "Bluetooth.h"
#include "Navigation.h"

void BluetoothClass::BtPrint(int tBtPrint)
{
	currentMillis = millis();
	if (currentMillis - previousMillis >= tBtPrint)  //conrolla se � passato il tempo di guardia prestabilito
	{
		currentMillis = previousMillis;
		//gas;foto1;foto2;foto3;ping sx;ping dx;infra sx; infra dx; stato
		int gas = N_gas.valueGas; //converto il valore da float in int
		Serial1.print(gas);
		Serial1.print(";");

		int foto1 = N_fotoresistor.valueDX;
		Serial1.print(foto1);
		Serial1.print(";");

		int foto2 = N_fotoresistor.valueC;
		Serial1.print(foto2);
		Serial1.print(";");

		int foto3 = N_fotoresistor.valueSX;
		Serial1.print(foto3);
		Serial1.print(";");

		int pingSX = Navigation.distanzaSX;
		Serial1.print(pingSX);
		Serial1.print(";");

		int pingDX = Navigation.distanzaDX;
		Serial1.print(pingDX);
		Serial1.print(";");

		Serial1.print(Navigation.vRxSX);
		Serial1.print(";");

		Serial1.print(Navigation.vRxDX);
		Serial1.print(";");

		Serial1.println(stato);

	}//end if
}


BluetoothClass Bluetooth;


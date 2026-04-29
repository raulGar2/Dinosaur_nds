// 2024-2025 ikasturtea

/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "jokuKontrola.h"
#include "jokoa01.h"

int EGOERA; // Automata zein egoeratan dagoen adierazteko erabilia
int seg1;   // Segundo bat pasa ote diren ikusten joateko
int lurrekoX; // Kaktus spritearen X koordenada
int airekoX; // Pterodaktiro spritearen X koordenada
int score; // Jokalariak lortutako puntuazioa gordetzeko aldagaia

void  tekEten(){
if (EGOERA == KORRIKA){	
	if (SakatutakoTekla()==A){
		// Jauzi egiten du
		EGOERA=AIREAN;
		salto();
		seg1=0;
	}
	if (SakatutakoTekla()==B){
		// Makurtuta egotera pasatzen da
		EGOERA=MAKURTUTA;
		makurtu();
		seg1=0;
	}
}

}

void tenpEten()
{
	if (EGOERA==KORRIKA || EGOERA==AIREAN || EGOERA==MAKURTUTA)
	{
		scoreakKudeatu();
		lurrekoaMugitu();
		if (score>=AIREKOA_HASI){
			// AIREKOA_HASI aldagaia gainditzen bada, pterodaktiloa spritea mugitzen hasiko da
			airekoaMugitu();
		} 
		if (EGOERA!=KORRIKA){
			seg1++;
			if (seg1==30){
				// segundu bat pasatzen bada, pertsonaia posizio arruntara bueltatuko da da
				korrikaraBueltatu();
				EGOERA=KORRIKA;
			}
		}
		if (ikututa()){
			// Dinosauri spritea kaktusarekin edo pterodaktiroarekin talka egiten duenean game over-a irudikatzen da
			// eta denbora gelditzen da erroreak sahiesteko
			ErlojuaGelditu();
			grafikoakBorratu();
			EGOERA=GAMEOVER;
			consoleClear();
			printGameOver();
		}
		if (EGOERA==KORRIKA){
			korrika();
		}
		if (EGOERA==MAKURTUTA){
			makurtuta();
		}
	}
	
}

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS,tekEten);
	irqSet(IRQ_TIMER0,tenpEten);
}





/***********************2024-2025*******************************/
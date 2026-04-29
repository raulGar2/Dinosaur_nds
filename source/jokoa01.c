// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

// Guk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "jokuKontrola.h"

int score; // puntuaketa neurtzen joateko
int maxScore; // maxScore aldagaia, jokalariak lortutako puntuazio maximoa gordetzeko
int dinPos; // Dinosauri spritearen posizioa



void jokoa01()
{	
	// Aldagaiak definitu
	int tekla; // Sakatutako tekla gordetzeko aldagaia
	EGOERA=MENUA; // Automataren egoera hasieran MENUA da
	int lurrekoX; // Kaktus spritearen X koordenada
	int airekoX; // Pterodaktiro spritearen X koordenada
	bool erakutsiAire; // Pterodaktiro spritea irudikatu edo ez
	bool erakutsiLur; // Kaktus spritea irudikatu edo ez
	int maxScore=0; // Jokalariak lortutako puntuazio maximoa 0 jarri
	touchPosition pant_dat; // Ukimen-pantailaren datuak gordetzeko aldagaia
	consoleClear(); 




	//******************************2.JARDUERAN************************************************//
	// ORDEN HONETAN ZEREGIN HAUEK EGITEA GOMENDATZEN DA:
	// Teklatua konfiguratu behar da.
	konfiguratuTeklatua(0x4003);	
	// Tenporizadorea konfiguratu behar da.
	konfiguratuTenporizadorea(56798, 0x00C1);
	// Etenen zerbitzu errutinak ezarri behar dira.
	etenZerbErrutEzarri();
	// Teklatuaren etenak baimendu behar dira.
	TekEtenBaimendu();
	// Tenporizadorearen etenak baimendu behar dira.
	DenbEtenBaimendu();
	// Etenak baimendu behar dira.
	EtenakBaimendu();
	//***************************************************************************************//
	printMenua();
	while (1)
	{	
		/*************************************1.JARDUERAN**************************************/
		// ZAI egoeran dagoela, hemen teklatuaren inkesta egin, sakatu den tekla pantailaratu, eta START
		// sakatzean egoera aldatu
		if (EGOERA==MENUA){
			tekla=SakatutakoTekla();
			if(tekla==START){
				//Jokura pasa
				consoleClear();
				EGOERA=KORRIKA;
				score=0;
				ErlojuaMartxanJarri();
				grafikoakHasieratu();
			}
		}
		if (EGOERA==GAMEOVER){
			printGameOver();
			tekla=SakatutakoTekla();
			if(ukimenIkutua()){
				if (PANT_DAT.px>75 && PANT_DAT.px<185 && PANT_DAT.py>90 && PANT_DAT.py<135){
					//Menura bueltatu
					EGOERA=MENUA;
					consoleClear();
					printMenua();
				}
				
			}
		}
	}
	etenakGalarazi();
	// Bukaeran etenak galarazi.
}






/***********************2024-2025*******************************/


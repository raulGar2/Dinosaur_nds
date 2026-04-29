#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"

int lurrekoX; // Kaktus spritearen X koordenada
int airekoX; // Pterodaktiro spritearen X koordenada
int jauzi=PERTSONAI_Y-20; // Dinosauri spritearen jauzi posizioa
int score; // Jokalariak lortutako puntuazioa gordetzeko aldagaia
bool erakutsiLur;
bool erakutsiAire;
int airKont, airPos; // Pterodaktiro spritearen posizioa eta animazioa kontrolatzeko aldagaia
bool airAldatu; // Pterodaktiro spritearen posizioa aldatzeko aldagaia
int dinKont, dinPos; // Dinosaurio spritearen animazioa kontrolatzeko aldagaiak
bool dinAldatu; // Dinosaurio spritea irudikatu edo ez
int maxScore; // Jokalariak lortutako puntuazio maximoa

void scoreakKudeatu(){
	// Score eta top-scorea kudeatzeko funtzioa
	iprintf("\x1b[2;0H Top-score: %d",maxScore);
	iprintf("\x1b[2;20H Score: %d",score);
	score++;
	if (score>maxScore){
			maxScore=score;
	}
}

void lurrekoaMugitu(){
	// Kaktus spritea mugitzeko funtzioa
	if (erakutsiLur){
		ErakutsiKaktusa(LURREKO_INDEX, LURREKO_HASIERA_X, LURREKO_Y);
		erakutsiLur=false;
		lurrekoX=LURREKO_HASIERA_X;
	}
	else{
		EzabatuKaktusa(LURREKO_INDEX, lurrekoX, LURREKO_Y);
		lurrekoX=lurrekoX-2;
		ErakutsiKaktusa(LURREKO_INDEX, lurrekoX, LURREKO_Y);
	}
	if (lurrekoX<=0){
		EzabatuKaktusa(LURREKO_INDEX, lurrekoX, LURREKO_Y);
		erakutsiLur=true;
	}
}

void airekoaMugitu(){
	// Pterodaktiro spritea mugitzeko eta animazioa egiteko funtzioa
	if (erakutsiAire){
		ErakutsiPterodaktilo1(AIREKO_INDEX, AIREKO_HASIERA_X, AIREKO_Y);
		erakutsiAire=false;
		airekoX=AIREKO_HASIERA_X;
		airKont=0;
		airAldatu=false;
		airPos=1;
	}
	else{
		if (airPos==1){
			EzabatuPterodaktilo1(AIREKO_INDEX, airekoX, AIREKO_Y);
			airekoX=airekoX-2;
			if (airAldatu){
				ErakutsiPterodaktilo2(AIREKO_INDEX, airekoX, AIREKO_Y);
				airPos=2;
				airKont=0;
				airAldatu=false;
			}
			else{
				ErakutsiPterodaktilo1(AIREKO_INDEX, airekoX, AIREKO_Y);
				airKont++;
			}
		}
		else{
			EzabatuPterodaktilo2(AIREKO_INDEX, airekoX, AIREKO_Y);
			airekoX=airekoX-2;
			if (airAldatu){
				ErakutsiPterodaktilo1(AIREKO_INDEX, airekoX, AIREKO_Y);
				airPos=1;
				airKont=0;
				airAldatu=false;
			}
			else{
				ErakutsiPterodaktilo2(AIREKO_INDEX, airekoX, AIREKO_Y);
				airKont++;
			}
		}
	}
	if (airekoX<=0){
		if (airPos==1){
			EzabatuPterodaktilo1(AIREKO_INDEX, airekoX, AIREKO_Y);
		}
		else{
			EzabatuPterodaktilo2(AIREKO_INDEX, airekoX, AIREKO_Y);
		}
		erakutsiAire=true;
	}
	if (airKont==10){
		airAldatu=true;
	}
}

void korrika(){
	// Dinosauri spritea mugitzeko animazioa ematen duen funtzioa
	if (dinAldatu){
		if (dinPos==1){
			EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			dinPos=2;
			dinKont=0;
			dinAldatu=false;
		}
		else{
			EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			dinPos=1;
			dinKont=0;
			dinAldatu=false;
		}
	}
	else{
		dinKont++;
	}
	if (dinKont==10){
		dinAldatu=true;
	}
}

void grafikoakHasieratu(){
	// Dinosauri spritea hasieratzeko funtzioa
	dinPos=1;
	ErakutsiDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
	erakutsiLur=true;
	lurrekoX=LURREKO_HASIERA_X;
	erakutsiAire=true;
	airekoX=AIREKO_HASIERA_X;
	erakutsiBasamortua();
}

void korrikaraBueltatu(){
	// Dinosauri spritea beste gauza bat egiten duenean korrikara bueltatzeko funtzioa
	if (EGOERA==AIREAN){
		if (dinPos==1){
			EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
			ErakutsiDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
		else{
			EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
		}
	}
	else if (EGOERA==MAKURTUTA){
		if (dinPos==1){
			EzabatuMakurtuta1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
		else{
			EzabatuMakurtuta2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
	}
}

void makurtu(){
	// Dinosauri spritea makurtzera pasatzeko funtzioa
	if (dinPos==1){
		EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		ErakutsiMakurtuta1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
	}
	else{
		EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		ErakutsiMakurtuta2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
	}
}

void makurtuta(){
	// Dinosauri spritea makurtuta dagoenean animazioa egiten duen funtzioa
	if (dinAldatu){
		if (dinPos==1){
			EzabatuMakurtuta1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiMakurtuta2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			dinPos=2;
			dinKont=0;
			dinAldatu=false;
		}
		else{
			EzabatuMakurtuta2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			ErakutsiMakurtuta1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
			dinPos=1;
			dinKont=0;
			dinAldatu=false;
		}
	}
	else{
		dinKont++;
	}
	if (dinKont==10){
		dinAldatu=true;
	}
}

void salto(){
	// Dinosauri spritea salto egiteko animazioa funtzioa
	if (dinPos==1){
		EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		ErakutsiDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
	}
	else{
		EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		ErakutsiDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
	}	
}

bool ikututa(){
	// Dinosauri spritea kaktusarekin edo pterodaktiroarekin talka egiten duenean true itzultzen du
	if (EGOERA!=AIREAN){
		if (lurrekoX>24 && lurrekoX<56){
			return true;
		}
	}
	if (EGOERA!=MAKURTUTA){
		if (airekoX>24 && airekoX<56){
			return true;
		}
	}
	return false;
}

void grafikoakBorratu(){
	// Dinosauri spritea, kaktus spritea eta pterodaktiro spritea ezabatzeko funtzioa
	if (EGOERA==KORRIKA){
		if (dinPos==1){
			EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
		else{
			EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
	}
	else if(EGOERA==AIREAN){
		if (dinPos==1){
			EzabatuDinosaur1(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
		}
		else{
			EzabatuDinosaur2(PERTSONAI_INDEX, PERTSONAI_X, jauzi);
		}
	}
	else{
		if (dinPos==1){
			EzabatuMakurtuta1(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
		else{
			EzabatuMakurtuta2(PERTSONAI_INDEX, PERTSONAI_X, PERTSONAI_Y);
		}
	}
	EzabatuKaktusa(LURREKO_INDEX, lurrekoX, LURREKO_Y);
	if (score>=AIREKOA_HASI){
		if (airPos==1){
			EzabatuPterodaktilo1(AIREKO_INDEX, airekoX, AIREKO_Y);
		}
		else{
			EzabatuPterodaktilo2(AIREKO_INDEX, airekoX, AIREKO_Y);
		}
	}
}

void printMenua(){
	// Menu pantaila irudikatzen du
	consoleClear();
	erakutsiMenu();
	iprintf("\x1b[0;0H KE-3-1 TALDEA");
	iprintf("\x1b[2;0H Ibai Martiarena, Elaia Erkizia, Xabat Vitoria eta Raul Garcia");
	iprintf("\x1b[8;0H Jokatzeko modua:");
	iprintf("\x1b[10;0H A tekla sakatu saltatzeko eta B makurtzeko");
	iprintf("\x1b[12;0H Kaktusak edo pterodaktiloak");
	iprintf("\x1b[13;0H ukitzen badituzu, galduko duzu");
	iprintf("\x1b[15;0H Top-score: %d",maxScore);
	iprintf("\x1b[17;0H Hasteko START sakatu");
}

void printGameOver(){
	// Game over pantaila irudikatzen du
	erakutsiGameOver();
	iprintf("\x1b[2;0H Galdu duzu");
	if (score<maxScore){
		iprintf("\x1b[4;0H Score: %d",score);
		iprintf("\x1b[5;0H Top-score: %d",maxScore);
	}
	else{
		iprintf("\x1b[4;0H NEW top-score: %d",maxScore);
	}
	iprintf("\x1b[10;0H Menura bueltatzeko menu");
	iprintf("\x1b[11;0H botoia sakatu");
}
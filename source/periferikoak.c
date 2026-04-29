// 2024-2025 ikasturtea

/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; // Sakatutako tekla gordetzeko aldagaia; baloratu ea behar den

int TeklaDetektatu() 
{
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int SakatutakoTekla() 
{

	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;SELECT=2;START=3;ESKUBI=4;EZKER=5;
	// GORA=6;BEHERA=7;R=8;L=9;
	if ((~TEKLAK_DAT & 0x0001)!=0) return A;
	else if ((~TEKLAK_DAT & 0x0002)!=0) return B;
	else if ((~TEKLAK_DAT & 0x0004)!=0) return SELECT;
	else if ((~TEKLAK_DAT & 0x0008)!=0) return START;
	else if ((~TEKLAK_DAT & 0x0010)!=0) return ESKUBI;
	else if ((~TEKLAK_DAT & 0x0020)!=0) return EZKER;
	else if ((~TEKLAK_DAT & 0x0040)!=0) return GORA;
	else if ((~TEKLAK_DAT & 0x0080)!=0) return BEHERA;
	else if ((~TEKLAK_DAT & 0x0100)!=0) return R;
	else if ((~TEKLAK_DAT & 0x0200)!=0) return L;

}

void konfiguratuTeklatua(int TEK_konf)
{
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	TEKLAK_KNT=TEK_konf;
	
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	DENB0_DAT=Latch;
	DENB0_KNT=DENB0_KNT|TENP_konf;
	
	
}

void TekEtenBaimendu()
{
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE=IE|0x1000;
	IME=1;
}

void TekEtenGalarazi()
{

	// Teklatuaren etenak galarazi
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE=IE&0xEFFF;
	IME=1;
}  

void DenbEtenBaimendu()
{

// Tenporizadore baten etenak baimendu (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE=IE|0x0008;
	IME=1;
}

void DenbEtenGalarazi()
{

// Tenporizadore baten etenak galarazi (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE=IE&0xFFF7;
	IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT=DENB0_KNT|0x0080;
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT=DENB0_KNT&0xFF7F;
}

void etenakGalarazi(){
	// Eten guztiak galarazi
	TekEtenGalarazi();
	ErlojuaGelditu();
	DenbEtenGalarazi();
}

bool ukimenIkutua(){
	// Ukimen-pantailaren datuak irakurri eta pantaila ikutua den ala ez itzultzen du
	touchRead(&PANT_DAT);
	return !(PANT_DAT.px==0 && PANT_DAT.py==0);
}

/***********************2024-2025*******************************/


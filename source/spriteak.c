// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

#include "spriteak.h"
#include "definizioak.h"

u16* gfxkaktusa;
u16* gfxpterodaktilo1;
u16* gfxpterodaktilo2;
u16* gfxdinosaur1;
u16* gfxdinosaur2;
u16* gfxmakurtuta1;
u16* gfxmakurtuta2;


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxkaktusa=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfxpterodaktilo1=oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxpterodaktilo2=oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdinosaur1=oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
	gfxdinosaur2=oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
	gfxmakurtuta1=oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
	gfxmakurtuta2=oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void PaletaNagusiaEzarri() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // 1 baliodun pixelak gorriak izango dira.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // 2 baliodun pixelak berdeak izango dira.
	SPRITE_PALETTE[3] = RGB15(0,0,31); // 3 baliodun pixelak urdinak izango dira.
}


u8 kaktusa[256]={
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 6,  

	0, 0, 0, 6, 6, 0, 6, 6, 0, 0, 0, 6, 6, 0, 6, 6,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  

	6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6,  

	0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6,  

	0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6,  

	0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6,  

	6, 0, 6, 6, 0, 0, 0, 0, 6, 0, 6, 6, 0, 0, 0, 0,  

	6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0,  

	6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  

	6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,
};

u8 pterodaktilo1[256]={
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0,  

	0, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6,  

	0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  

	6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0,  

	6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,  

	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,  

	0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

u8 pterodaktilo2[256]={
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0,  

	0, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6,  

	0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 6,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,  

	6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6,  

	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	6, 6, 6, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,  

	6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

u8 dinosaur1[256]={ 

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6,   
  
	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6,   
  
	0, 6, 0, 0, 0, 0, 0, 6, 0, 6, 0, 0, 0, 0, 6, 6,   
  
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
	6, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0,   
  
	6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0,   
  
	6, 6, 6, 6, 6, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,   
  
	0, 6, 6, 6, 0, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6,   
  
	0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6,   
  
	0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 0, 6,   
  
	0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 6, 6, 0, 6,   
  
	6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 0, 6, 0, 0, 0, 0,   
  
	6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,   
  
	6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
	0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  

}; 

u8 dinosaur2[256]={ 

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,   
  
	0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6,   
  
	0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 0, 0, 0, 0, 0, 6,   
  
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
	0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,   
  
	0, 6, 6, 6, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0,   
  
	6, 6, 6, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,   
  
	0, 6, 0, 0, 0, 0, 6, 6, 0, 6, 6, 6, 0, 6, 6, 6,   
  
	0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6,   
  
	0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
	0, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0,   
  
	6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0,   
  
	6, 6, 0, 6, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,   
 
	6, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,   

  	6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,  

}; 

u8 makurtuta1[256]={ 

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 6, 6, 6, 6, 6, 6, 0, 0, 6, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6,   
  
0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0,   
  
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,   
  
6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 0, 0, 0, 0, 0, 0,   
  
6, 6, 6, 6, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0,   
  
6, 6, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 
}; 

  

u8 makurtuta2[256]={ 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,   

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
  
0, 6, 6, 6, 6, 6, 6, 0, 0, 6, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6,   
  
0, 0, 6, 6, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 6,   
  
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,   
  
6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 0, 0, 0, 0, 0, 0,   
  
6, 6, 6, 6, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0,   
  
0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,  
}; 
/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde(){ 
	
int i;
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxkaktusa[i] = kaktusa[i*2] | (kaktusa[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxpterodaktilo1[i] = pterodaktilo1[i*2] | (pterodaktilo1[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxpterodaktilo2[i] = pterodaktilo2[i*2] | (pterodaktilo2[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxdinosaur1[i] = dinosaur1[i*2] | (dinosaur1[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxdinosaur2[i] = dinosaur2[i*2] | (dinosaur2[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxmakurtuta1[i] = makurtuta1[i*2] | (makurtuta1[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxmakurtuta2[i] = makurtuta2[i*2] | (makurtuta2[(i*2)+1]<<8);				
	}
}


void ErakutsiKaktusa(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxkaktusa,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuKaktusa(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxkaktusa,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}

void ErakutsiPterodaktilo1(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpterodaktilo1,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuPterodaktilo1(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpterodaktilo1,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}

void ErakutsiPterodaktilo2(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpterodaktilo2,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuPterodaktilo2(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpterodaktilo2,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}

void ErakutsiDinosaur1(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdinosaur1,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void EzabatuDinosaur1(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdinosaur1,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void ErakutsiDinosaur2(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdinosaur2,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuDinosaur2(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdinosaur2,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}

void ErakutsiMakurtuta1(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmakurtuta1,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuMakurtuta1(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmakurtuta1,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}

void ErakutsiMakurtuta2(int indizea, int x, int y)
{
oamSet(&oamMain, 
		indizea,           
		x, y,   
		0,                   
		0,					  	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmakurtuta2,
		-1,                    
		false,              
		false,			
		false, false,
		false	
		); 
oamUpdate(&oamMain); 
}

void EzabatuMakurtuta2(int indizea, int x, int y)
{

oamSet(&oamMain, 
		indizea,   
		x, y,   
		0,      
		0,			
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmakurtuta2,
		-1,          
		false,     
		true,		
		false, false,
		false	
		); 
oamUpdate(&oamMain); 

}
/***********************2024-2025*******************************/


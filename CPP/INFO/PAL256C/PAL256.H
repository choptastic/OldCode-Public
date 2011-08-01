/*
 PAL256.h - C/C++ Palette functions example version 1.0 for DOS

 This file contains some information about palette programming

 Programmed by FJTC for e-Software GP in 9/14/1997
 Last Upadate: 9/14/1997

 We will Not assume any damage that the contents of this file cause
 in your computer, brain or anything related you.

 You are free to use, modify and distribute it free of charge but you can
 not sell it. Use only for educational pupouse only.

 e-Software
       Contact-us at:
	       http://www.icmsc.sc.usp.br/~andreeta/e-Software
       or e-Mail us at:
	       chino@icmsc.sc.usp.br (FJTC)
*/

#if !defined(_PAL256_H)
#define _PAL245_H

#include <DOS.H>

/* Define Constants of VGA Palette Port */
#define MAXCOLORS 256				/* Max colors in the palette */
#define PALETTEPORTSET 0x03C8			/* Palette Set Port */
#define PALETTEPORTGET 0x03C7			/* Palette Get Port */
#define PALETTEPORTRW PALETTEPORTSET + 1	/* Palette Write/Read Port */

/* Data Types */
#if !defined(BYTE)
typedef unsigned char BYTE;
#endif
typedef struct {
	BYTE red;
	BYTE green;
	BYTE blue;
} RGBUnit;

/*Functions*****************************************************************/

void getpalette256(RGBUnit pal[]);
/* Get current palette */

void setpalette256(RGBUnit pal[]);
/* Set current palette */

void getpaletteatt(BYTE Att, BYTE * red, BYTE * green, BYTE * blue);
/* Get current palette  attribute */

void setpaletteatt(BYTE Att, BYTE red, BYTE green, BYTE blue);
/* Get current palette  attribute */

/* Bodies *******************************************************************/

/* Get current palette */
void getpalette256(RGBUnit pal[]){
	int w;

	outp(PALETTEPORTGET, 0);
	for (w = 0; w < MAXCOLORS; w ++){
		pal[w].red = inportb(PALETTEPORTRW);
		pal[w].green = inportb(PALETTEPORTRW);
		pal[w].blue = inportb(PALETTEPORTRW);
	}/* End for*/
}/* End getpalette256 */

/* Set current palette */
void setpalette256(RGBUnit pal[]){
	int w;

	outp(PALETTEPORTSET, 0);
	for (w = 0; w < MAXCOLORS; w ++){
		outportb(PALETTEPORTRW, pal[w].red);
		outportb(PALETTEPORTRW, pal[w].green);
		outportb(PALETTEPORTRW, pal[w].blue);
	}/* End for*/
}/* End setpalette256 */

/* Get current palette  attribute */
void getpaletteatt(BYTE Att, BYTE * red, BYTE * green, BYTE * blue){

	outp(PALETTEPORTGET, Att);
	*red = inportb(PALETTEPORTRW);
	*green = inportb(PALETTEPORTRW);
	*blue = inportb(PALETTEPORTRW);
}/* End getpaletteatt */


/* Get current palette  attribute */
void setpaletteatt(BYTE Att, BYTE red, BYTE green, BYTE blue){

	outportb(PALETTEPORTSET, Att);
	outportb(PALETTEPORTRW, red);
	outportb(PALETTEPORTRW, green);
	outportb(PALETTEPORTRW, blue);
}/* End setpaletteatt */

#endif
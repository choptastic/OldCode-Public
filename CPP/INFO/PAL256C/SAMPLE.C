/*
 Sample.c - C/C++ Palette functions example program version 1.0 for DOS

 This file is a sample program of palette programming.

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

#include "pal256.h"
#include "graph.h"
#include <stdio.h>
#include <dos.h>

#define DELAY 1000		/* Delay Loop - Ajust it */

void printlines(void);
/* Print color lines */

void rotatepal(RGBUnit pal[]);
/* rotate palette */

void main(void){
	RGBUnit pal[MAXCOLORS];

	initgraph();
	getpalette256(pal);	// Get BIOS palette

	printlines();
	printf("Press ESC to exit...");
	do{
		rotatepal(pal);
		setpalette256(pal);
		delay(30);
	}while(inportb(0x60) != 1);
	endgraph();
}/*End main*/


/* Print color lines */
void printlines(void){
	int X;
	int Y;

	for(X = 0; X < 256; X++)
		for(Y = 0; Y < 200; Y++){
			pset(X, Y, X);
		}/*End For*/
	/*End For*/

	for(X = 0; X < 256; X++)
		for(Y = 80; Y < 120; Y++){
			pset(X, Y, 256 - X);
		}/*End For*/
	/*End For*/
}/* end printlines*/

/* rotate palette */
void rotatepal(RGBUnit pal[]){
	RGBUnit temp;
	int w;

	temp = pal[1];
	for(w = 1; w< MAXCOLORS - 1; w++){
		pal[w] = pal[w + 1];
	}/* end For*/
	pal[MAXCOLORS - 1] = temp;
}/* End rotatepal */


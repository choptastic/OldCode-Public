/* This is a simple unit to starts and plot a pixel on the screen mode 13H
	Version 1.0

	By FJTC - Created in 11/7/1996.
	E-Mail address: fjtc@ensino.icmsc.sc.usp.br
 	Web address: http://www.geocities.com/SiliconValley/Heights/1378/

	Free to use and modify and you can not sell this code

	It's a simple code to starts the mode 13H (320 x 200 x 256), plot
	points and restore the default text mode.

If you want to use this information, I assume no responsibility for any effect
that the content of this file can do with your computer, mind and anything
related you. 

*/
#if !defined(__GRAPH_H)
#define __GRAPH_H

#include <DOS.H>

typedef unsigned char byte;

typedef unsigned short word;

void initgraph(void);
/* Start Graph Mode 13H - 320 x 200 x 256 (the most popular mode for game pro-
gramming. It's Fast and easy to use)*/

void endgraph(void);
/* Return to default text mode */

void pset(word X, word Y, byte color);
/* Plot a pixel in the screen (mode 13H only) in the coord. X, Y and color
attribute color using memory access */

/*------------------------Function Body-------------------------------------*/

/* Start Graph Mode 13H - 320 x 200 x 256 (the most popular mode for game pro-
gramming. It's Fast and easy to use)*/
void initgraph(void){
	union REGS IN, OUT; /* Register variables */

	IN.h.al = 0x13; /* Video mode parameter - mode 13H */
	IN.h.ah = 0x00; /* Interrupt 10H - service 0H */
	int86(0x10, &IN, &OUT); /* Call the interrupt 10H (Video Control)*/
}/*End Function*/

/* Return to default text mode */
void endgraph(void){
	union REGS IN, OUT; /* Register variables */

	IN.h.al = 0x3; /* Video mode parameter - mode 3H*/
	IN.h.ah = 0x00; /* Interrupt 10H - service 0H */
	int86(0x10, &IN, &OUT); /* Call the interrupt 10H (Video Control)*/
}/*End Function*/

/* Plot a pixel in the screen (mode 13H only) in the coord. X, Y and color
attribute color using memory access */
void pset(word X, word Y, byte color){
	/* unhappy it's more easy to use assembly */
	asm{
		mov DI, 0xA000 	/* We need to set the memory segment in ES. */
		mov ES, DI     	/* But we can't do it directly. Becose this
				   we must do:
				    DI = 0xA000 and then ES = DI */
		mov AX, Y 	/* We need this result: Y * 320 + X */
		mov BX, Y	/* But we will do this: */
		shl AX, 8 	/* 	AX = Y * 256 */
		shl BX, 6 	/*	BX = Y * 64 */
		add AX, BX	/*  	AX = Y * 320 */
		add AX, X	/* 	AX = AX + X */
		mov DI, AX	/* Then DI = Y * 256 + Y * 64 * X is equal to
				   Y * 320 + X but faster than it */
		mov AL, color	/* Set in AL the color attribute */
		mov ES:[DI],  AL/* Set the pixel on the screen */
	}/*End ASM*/
}/*End Function*/
#endif


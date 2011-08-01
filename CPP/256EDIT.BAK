#include<ctype.h>
#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include"graph.h"
#include<mouse.h>
#include<bios.h>
#include<dos.h>


const int UP=0;
const int DOWN=1;
const int STARTX=50;
const int STARTY=50;
int sizex=50,sizey=50;

void drawborder()
{
	rectangle(STARTX-1,STARTY-1,STARTX+sizex+1,STARTY+sizey+1,15);
	gotoxy(10,23);
	cout << "                        ";
}
void clearborder()
{
	rectangle(STARTX-1,STARTY-1,STARTX+sizex+1,STARTY+sizey+1,0);
}

void drawcolormap()
{
	int lx,ly;
	for(ly=0;ly<128;ly++)
		for(lx=200;lx<210;lx++)
			pset(lx,ly+20,ly);
	for(ly=0;ly<128;ly++)
		for(lx=210;lx<220;lx++)
			pset(lx,ly+20,ly+128);

}


void main()
{
	initgraph();
	drawborder();
	drawcolormap();

	byte *loc=getimage(200,40,220,100);
	setback(1);
		putimage(100,100,loc);

	getch();
	delete loc;

}
#if !defined(__GRAPH_H)
#define __GRAPH_H

#include <math.h>
#include <mem.h>
#include <alloc.h>
#include <DOS.H>


typedef unsigned char byte;

typedef unsigned short word;



void initgraph(void);
void endgraph(void);
void pset(word X, word Y, byte color);
byte pgetset(word X, word Y, byte color);
byte pget(word X, word Y);
void swap(int &, int &);
void rectangle(word X1, word Y1, word X2, word Y2, byte color);
void line(int X1, int Y1, int X2, int Y2, byte color);
void setback(byte color);
void setpal(byte index, byte r, byte g, byte b);

void set_virt();
void set_vga();
void draw_virt();

byte *_VGA;
byte *_virt;
byte *VGA;

const int MAXX=320;
const int MAXY=200;
const int half_X=MAXX/2;
const int half_Y=MAXY/2;


#include <pcx.cpp>


/*------------------------Function Body-------------------------------------*/

void set_virt()
{
	VGA=_virt;

}

void set_vga()
{
	VGA=_VGA;
}

void draw_virt()
{
	memcpy(_VGA,_virt,64000);
}




void initgraph(void){
	union REGS IN, OUT; /* Register variables */

	IN.h.al = 0x13;
	IN.h.ah = 0x00;
	int86(0x10, &IN, &OUT);
	_VGA=(byte*) MK_FP(0xA000,0);
	_virt=(byte*) malloc(64000);
	memset(_virt,0,64000);
	VGA = _VGA;

}




void endgraph(void){
	union REGS IN, OUT;

	IN.h.al = 0x3;
	IN.h.ah = 0x00;
	int86(0x10, &IN, &OUT);
}



void setpal(byte index, byte r, byte g, byte b)
{
	outp(0x03c8,index);
	outp(0x03c9,r);
	outp(0x03c9,g);
	outp(0x03c9,b);
}




void swap(word &x, word &y)
{
	int temp=x;
	x=y;
	y=temp;
}


void pset(word X, word Y, byte color)
{
	if(X<MAXX&&Y<MAXY)
		VGA[X+(Y<<6)+(Y<<8)]=color;
}


byte pgetset(word X, word Y, byte color)
{
	byte rcolor=VGA[X+Y<<6+Y<<8];
	VGA[X+Y<<6+Y<<8]=color;
	return rcolor;
}


byte pget(word X, word Y)
{
	return VGA[X+Y<<6+Y<<8];
}


void rectangle(word X1, word Y1, word X2, word Y2, byte color)
{
	if(Y1>Y2) swap(Y1,Y2);
	if(X1>X2) swap(X1,X2);
	int loop;
	for(loop=Y1;loop<=Y2;loop++)
	{
		pset(X1,loop,color);
		pset(X2,loop,color);
	}
	for(loop=X1;loop<=X2;loop++)
	{
		pset(loop,Y1,color);
		pset(loop,Y2,color);
	}
}

void fillrectangle(word X1, word Y1, word X2, word Y2, byte color)
{
	if(Y1>Y2) swap(Y1,Y2);
	if(X1>X2) swap(X1,X2);
	int length=X2-X1;
	byte far *vgaline=VGA+(Y1<<6)+(Y1<<8)+X1;
	for(int ly=Y1;ly<=Y2;ly++)
	{
		memset(vgaline,color,length);
		vgaline+=320;
	}

}

void setback(byte color)
{
	memset(VGA,color,64000);
}


void line(int X1, int Y1, int X2, int Y2, byte color)
{
	int loopx,loopy;
	int dy=1,dx=1;
	float m;

	if(Y1>Y2) dy=-1;
	if(X1==X2)
	{
		for(loopy=Y1;loopy!=Y2;loopy+=dy)
			pset(X1,loopy,color);
		pset(X2,Y2,color);
		return;
	}
	if(X1>X2) dx=-1;
	if(Y1==Y2)
	{
		for(loopx=X1;loopx!=X2;loopx+=dx)
			pset(loopx,Y1,color);
		pset(X2,Y2,color);
		return;
	}

	m=(Y2-Y1)/float(X2-X1);
	float x=X1,y=Y1;
	if(fabs(m)<=1)
	{

		for(loopx=X1;loopx!=X2;loopx+=dx)
		{
			pset(loopx,y,color);
			y+=m*dx;
		}
	}

	else
	{
		m=1/m;
		for(loopy=Y1;loopy!=Y2;loopy+=dy)
		{
			pset(x,loopy,color);
			x+=m*dy;
		}
	}
	pset(X2,Y2,color);


}


#endif



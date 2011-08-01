#include <stdlib.h>
#include <iostream.h>
#include <malloc.h>
#include <conio.h>
#include <fstream.h>
#include <mouse.h>


const int w_MAXROWS=60;
const char* w_empty="                    ";


int numitems;
int w_item[w_MAXROWS];
char* w_name[w_MAXROWS];


struct _select
{
	int index;
	void select(int x, int y);
	void draw();
	void increment(){w_item[index]++;draw();}
	void decrement(){if(w_item[index]>0) w_item[index]--;draw();}
}selected;

void runwaste();

void w_save();
void w_loadinfo();

int w_getcommand();

void w_drawitem(int index);
void w_drawallitems();

void w_drawproginfo();
void w_drawbuttons();

int w_mousex(){return (readmousex()>>3)+1;}
int w_mousey(){return (readmousey()>>3)+1;}


void runwaste()
{
	_setcursortype(_NOCURSOR);
	w_loadinfo();
	textbackground(0);
	textcolor(7);
	clrscr();
	w_drawallitems();
	w_drawbuttons();
	w_drawproginfo();
	selected.select(1,1);
	while(w_getcommand()!=1);
	textcolor(7);
	textbackground(0);
	clrscr();

}

int w_getcommand()
{
	int mx,my;
	if(mousereleased(0))
	{
		mx=w_mousex();
		my=w_mousey();
		if(mx<=60)
			selected.select(mx,my);
		else if(mx>=60 && mx<=64)
		{
			if(my>=18 && my<=20)
				selected.increment();
			else if(my>=22 && my <=24)
				selected.decrement();
		}
		else if(mx>=60 && mx<=76 && my>=14 && my <=16)
		{
			w_save();
			return 1;
		}
	}
	return 0;
}

void w_drawitem(int index)
{
	char v[6];

	for(int loop=0;loop<6;loop++)
		v[loop]=0;

	int x,y;
	x=(index/25)*20+1;
	y=index%25+1;
	gotoxy(x,y);
	cprintf(w_empty);
	gotoxy(x,y);
	cout << w_name[index];
	gotoxy(x+16,y);
	cout << w_item[index];
}

void w_drawallitems()
{
	for(int loop=0;loop<numitems;loop++)
		w_drawitem(loop);
}


void w_loadinfo()
{
	ifstream in;
	int loop;




	numitems=0;
	in.open(listloc);
	while(!in.eof())
	{
		w_name[numitems]=(char*)malloc(20);
		in.getline(w_name[numitems],17);
		fixstring(w_name[numitems++]);
	}
	in.close();

	while(w_name[numitems-1][0]<'A' || w_name[numitems-1][0]>'z')
		numitems--;

	for(loop=0;loop<numitems;loop++)
		w_item[loop]=0;

	loop=0;
	in.open(wasteloc);
	while(!in.eof() && numitems>loop)
		in >> w_item[loop++];
	in.close();

}

void w_save()
{
	ofstream out(wasteloc);
	for(int loop=0;loop<numitems;loop++)
		out << w_item[loop] << endl;
	out.close();
}


void w_drawbuttons()
{
	gotoxy(60,11); cout << "Press this button";
	gotoxy(60,12); cout << "when wastes are";
	gotoxy(60,13); cout << "all inputted.";
	gotoxy(60,14); cout << "ษอออออออออออออออป";
	gotoxy(60,15); cout << "บ    D O N E    บ";
	gotoxy(60,16); cout << "ศอออออออออออออออผ";
	gotoxy(60,18);	cout << "ษอออป Press these";
	gotoxy(60,19); cout << "บ  บ buttons to ";
	gotoxy(60,20); cout << "ศอออผ increment or";textcolor(1+BLINK);textbackground(2);
	gotoxy(60,21); cprintf("Whoa!Productions");textcolor(7);textbackground(0);
	gotoxy(60,22);	cout << "ษอออป decrement the";
	gotoxy(60,23); cout << "บ  บ waste numbers";
	gotoxy(60,24); cout << "ศอออผ";
}

void w_drawproginfo()
{
	gotoxy(60,1); cout << "Marcus Counts";
	gotoxy(60,2); cout << "Calculator 1.0";
	gotoxy(60,3); cout << "-=-=WASTES=-=-";
}
void _select::select(int x, int y)
{
	int i;
	i=(x/20)*25;
	i+=y-1;
	if(i<numitems)
	{
		textbackground(0);
		w_drawitem(index);
		textbackground(4);
		w_drawitem(i);
		index=i;
	}
}

void _select::draw()
{
	textbackground(4);
	w_drawitem(index);
}






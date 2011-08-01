// Counts program
#include <stdio.h>
#include <malloc.h>
#include <iostream.h>
#include <dos.h>
#include <conio.h>
#include <fstream.h>
#include <iomanip.h>
#include <mouse.h>
#include <stdlib.h>

const int MAXY=22;
const int COLS=7;
const int MAXROWS=40;
const int COLWID=6;
const int ITEMLEN=15;

const int CHECKCOUNTS=203;
const int RECOUNTS=204;
const int COUNTSDONE=205;

const char* empty="     ";
const char* fields[COLS]={
				"Stock","Cab","Case1",
				"Case2","Case3","Case4","Total"};

const char* iniloc="counts.ini";
char listloc[50];
char textloc[50];
char checkloc[50];
char saveloc[50];


int ROWS;
int cposition=0;
char calcvalue[COLWID+1]="0";
char* itemname[MAXROWS];
unsigned int item[MAXROWS][COLS];
int waste[MAXROWS];


int ypos=0;


void setup();     // this loads the file
void restore();

void drawvalues();
void drawtop();
void drawbottom();
void drawrow(int r);
void drawcalc();

void add(char c);
void del();
void clearcalc();
void total(int r);

void buttonpress(int x, int y, int w, int h);
void getcommand();

void totextfile();
void text_drawbottom(ofstream &out);
void text_drawvalues(ofstream& out);
void text_drawtop(ofstream &out);

void tocheckfile();
int wait_response();
void save();
void load();

int mousex();
int mousey();


struct editing
{
	int r, c;
	void set(char* value);
	void select(int _r, int _c);
	void unselect();
	void increment();
};

editing edit;









void main()
{
	_wscroll=0;
	_setcursortype(_NOCURSOR);

	setup();
	textcolor(7);
	textbackground(0);
	clrscr();

	initmouse();
	mouselimit(0,0,639,199);
	//showmouse();

	drawvalues();
	drawtop();
	drawbottom();
	drawcalc();



	while(!kbhit())
		getcommand();
	totextfile();
	restore();
}


void drawtop()
{
	gotoxy(1,1);
	cout << "Item";
	for(int loop=0;loop<COLS;loop++)
	{
		gotoxy(ITEMLEN+loop*(COLWID)+1,1);
		cout << fields[loop];
	}
	gotoxy(1,2);
	cout << 'Ú';
	for(loop=0;loop<ITEMLEN-2;loop++)
		cout << 'Ä';
	for(loop=0;loop<COLS;loop++)
	{
		cout << 'Â';
		for(int loop2=0;loop2<(COLWID)-1;loop2++)
			cout << 'Ä';
	}
	cout << '¿';
}

void drawbottom()
{
	gotoxy(1,25);
	cout << 'À';
	for(int loop=0;loop<ITEMLEN-2;loop++)
		cout << 'Ä';
	for(loop=0;loop<COLS;loop++)
	{
		cout << 'Á';
		for(int loop2=0;loop2<(COLWID)-1;loop2++)
			cout << 'Ä';
	}
	cout << 'Ù';
}



void drawvalues()
{
	edit.select(edit.r,edit.c);
	for(int r=ypos;r<MAXY+ypos;r++)
		drawrow(r);
}



void setup()
{
	ROWS=0;
	clearcalc();
	// get the main initialization file
	clrscr();
	for(int loop=0;loop<50;loop++)
	{
		listloc[loop]=0;
		textloc[loop]=0;
		checkloc[loop]=0;
		saveloc[loop]=0;
	}
	ifstream in(iniloc);
	in >> listloc;
	in >> textloc;
	in >> checkloc;
	in >> saveloc;
	in.close();
	//cout << listloc << endl << textloc << endl << checkloc << endl;

	char filename[13];
	filename[13];
	filename[8]='.';
	filename[9]='t';
	filename[10]='x';
	filename[11]='t';
	filename[12]='\0';
	char y[5],d[3],m[3];
	date cur;

	int end;
	for(end=0;textloc[end]!='\0';end++);  // find end of string

	getdate(&cur);
	itoa(cur.da_year,y,10);
	itoa(int(cur.da_mon),m,10);
	itoa(int(cur.da_day),d,10);

	if(d[1]=='\0')
	{
		d[1]=d[0];
		d[0]='0';
	}
	if(m[1]=='\0')
	{
		m[1]=m[0];
		m[0]='0';
	}
	memcpy(&filename[4],m,2);
	memcpy(&filename[6],d,2);
	memcpy(&filename[0],y,4);
	memcpy(&textloc[end],filename,13);

	//get the item list
	in.open(listloc);
	while(!in.eof())
	{
		itemname[ROWS]=(char*)malloc(ITEMLEN);
		in >> itemname[ROWS];
		ROWS++;
	}
	in.close();
}
void restore()
{
	for(int loop=0;loop<ROWS;loop++)
		free(itemname[loop]);
	textcolor(7);
	textbackground(0);
	clrscr();
	_setcursortype(_NORMALCURSOR);
}



void getcommand()
{
	int x,y;
	if(mousereleased(0))
	{
		x=mousex();
		y=mousey();
		if(x<=ITEMLEN+(COLS-1)*COLWID && x>ITEMLEN-1 && y>=3 && y<=2+MAXY)
		{
			edit.unselect();
			int sx,sy;
			sx=(x-ITEMLEN-1)/(COLWID);
			sy=ypos+y-3;
			edit.select(sy,sx);
		}
		else if(x>=60 && x<=64 && y>=18 && y<=20 && ypos>0)
		{
			edit.unselect();
			ypos--;
			drawvalues();
		}
		else if(x>=60 && x<=64 && y>=22 && y<=24 && ypos+MAXY<ROWS)
		{
			edit.unselect();
			ypos++;
			drawvalues();
		}
		else if(x>=68 && y>=18 && y<=20)
			tocheckfile();
		else if(x>=68 && x<=73 && y>=22 && y<=24)
			save();
		else if(x>=75 && y>=22 && y<=24)
			load();
		else if(x>=61 && x<=79 && y<=16)
		{
			if(x<67)
			{
				if(y>13)
					clearcalc();
				else if(y>10)
					add('1');
				else if(y>=7)
					add('4');
				else if(y>=4)
					add('7');
			}
			else if(x<=73)
			{
				if(y>13)
					add('0');
				else if(y>10)
					add('2');
				else if(y>=7)
					add('5');
				else if(y>=4)
					add('8');
			}
			else
			{
				if(y>13)
					edit.set(calcvalue);
				else if(y>10)
					add('3');
				else if(y>=7)
					add('6');
				else if(y>=4)
					add('9');
				else
					del();
			}
		}
	}
}


void add(char c)
{
	if(cposition>=COLWID-2)
		return;
	calcvalue[cposition++]=c;
	gotoxy(63,2);
	cout <<calcvalue;
}

void del()
{
	if(cposition>0)
	{
		calcvalue[--cposition]='\0';
		gotoxy(63,2);
		cout << calcvalue << ' ';
	}
}





void editing::select(int _r, int _c)
{
	int x,y;

	x=ITEMLEN+_c*(COLWID)+1;
	y=_r+3-ypos;

	if(x<2 || x>(COLWID)*(COLS+1) || y<3 || y>2+MAXY)
		return;

	char v[COLWID];
	gotoxy(x,y);
	textbackground(1);
	textcolor(15);
	cprintf(empty);

	gotoxy(x,y);
	itoa(item[_r][_c],v,10);
	cprintf(v);
	edit.r=_r;
	edit.c=_c;
}


void editing::unselect()
{
	int x,y;

	x=ITEMLEN+c*(COLWID)+1;
	y=r+3-ypos;

	if(x<2 || x>(COLWID)*(COLS+1) || y<3 || y>2+MAXY)
		return;
	char v[COLWID];

	gotoxy(x,y);
	textbackground(0);
	textcolor(7);
	cprintf(empty);

	gotoxy(x,y);
	textcolor(7);
	textbackground(0);
	itoa(item[r][c],v,10);
	cprintf(v);
}



void editing::increment()
{
	unselect();
	c++;
	if(c>=COLS-1)
	{
		c=0;
		r++;
		if(r>=ROWS)
		{
			r=0;
			ypos=0;
			drawvalues();
		}

	}
	select(r,c);
}


void editing::set(char* value)
{
	item[r][c]=atoi(value);
	clearcalc();
	total(r);
	increment();
}



void clearcalc()
{
	gotoxy(63,2);
	cout << empty;
	for(int loop=0;loop<COLWID-1;loop++)
		calcvalue[loop]='\0';
	cposition=0;
}



void total(int r)
{
	item[r][COLS-1]=0;
	for(int loop=0;loop<COLS-1;loop++)
		item[r][COLS-1]+=item[r][loop];
	drawrow(r);
}



void drawrow(int r)
{
	gotoxy(1,r+3-ypos);
	cout << '³' << itemname[r];
	while(wherex()<ITEMLEN+1)
		cout << ' ';
	for(int c=0;c<COLS;c++)
	{
		gotoxy(ITEMLEN+c*(COLWID),r-ypos+3);
		cout << '³';
		cout << item[r][c];
		while(wherex()<ITEMLEN+(c+1)*(COLWID))
			cout << ' ';
	}
	gotoxy(ITEMLEN+COLS*(COLWID),r-ypos+3);
		cout << '³';
}



int mousex()
{return (readmousex()>>3)+1;}
int mousey()
{return (readmousey()>>3)+1;}





void drawcalc()
{
	gotoxy(60,1);	cout << "ÉÍÍÍÍÍÍÍÍÍÍÍËÑÍÍÍÍÍÑ»";
	gotoxy(60,2);	cout << "º           º³ <<< ³º";
	gotoxy(60,3);	cout << "ÌÍÍÍÍÍÍÍÍÍÍÍ¼³ Del ³º";
	gotoxy(60,4);	cout << "ºÚÄÄÄÄÄÂÄÄÄÄÄÅÄÄÄÄÄ´º";
	gotoxy(60,5);	cout << "º³     ³     ³     ³º";
	gotoxy(60,6);	cout << "º³  7  ³  8  ³  9  ³º";
	gotoxy(60,7);	cout << "ºÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´º";
	gotoxy(60,8);	cout << "º³     ³     ³     ³º";
	gotoxy(60,9);	cout << "º³  4  ³  5  ³  6  ³º";
	gotoxy(60,10);	cout << "ºÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´º";
	gotoxy(60,11);	cout << "º³     ³     ³     ³º";
	gotoxy(60,12);	cout << "º³  1  ³  2  ³  3  ³º";
	gotoxy(60,13);	cout << "ºÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´º";
	gotoxy(60,14);	cout << "º³     ³     ³     ³º";
	gotoxy(60,15);	cout << "º³Clear³  0  ³ Set ³º";
	gotoxy(60,16);	cout << "ºÀÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÙº";
	gotoxy(60,17); cout << "ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼";
	gotoxy(60,18);	cout << "ÉÍÍÍ»   ÉÍÍÍÍÍÍÍÍÍÍÍ»";
	gotoxy(60,19); cout << "º  º   º   Send    º";
	gotoxy(60,20); cout << "ÈÍÍÍ¼   ÈÍÍÍÍÍÍÍÍÍÍÍ¼";textcolor(1+BLINK);textbackground(2);
	gotoxy(60,21); cprintf("Whoa! Productions....");textcolor(7);textbackground(0);
	gotoxy(60,22);	cout << "ÉÍÍÍ»   ÉÍÍÍÍ» ÉÍÍÍÍ»";
	gotoxy(60,23); cout << "º  º   ºSaveº ºLoadº";
	gotoxy(60,24); cout << "ÈÍÍÍ¼   ÈÍÍÍÍ¼ ÈÍÍÍÍ¼";
	gotoxy(60,25); cout << "     by Jesse Gumm  ";
}

void buttonpress(int x, int y, int w, int h)
{
	textbackground(6);

	for(int loopx=x; loopx<x+w;loopx++)
		for(int loopy=y; loopy<y+h;loopy++)
		{
			gotoxy(loopx,loopy);
			cprintf(" ");
		}
}

void totextfile()
{
	date cur;

	ofstream out(textloc);
	out << "Marcus Counts -- End of the Day\n";
	out << "For the date of :";
	getdate(&cur);
	out << int(cur.da_mon) << "/" << int(cur.da_day) << "/" << cur.da_year << endl;
	text_drawtop(out);
	text_drawvalues(out);
	text_drawbottom(out);
	out << endl << "Marcus Counts v1.0 by Whoa! Productions";
	out.close();
}


void text_drawbottom(ofstream &out)
{
	out << 'À';
	for(int loop=0;loop<ITEMLEN-2;loop++)
		out << 'Ä';
	for(loop=0;loop<COLS;loop++)
	{
		out << 'Á';
		for(int loop2=0;loop2<COLWID-1;loop2++)
			out << 'Ä';
	}
	out << 'Ù' << endl;
}

void text_drawtop(ofstream &out)
{
	long beginning;
	out << endl;
	beginning=out.tellp();
	out << "Item";
	while(out.tellp()-beginning<ITEMLEN)
		out << ' ';
	for(int loop=0;loop<COLS;loop++)
	{
		beginning=out.tellp();
		while(out.tellp()-beginning<COLWID-5)
			out << ' ';
		out << fields[loop];
	}
	out << endl;

	out << 'Ú';
	for(loop=0;loop<ITEMLEN-2;loop++)
		out << 'Ä';
	for(loop=0;loop<COLS;loop++)
	{
		out << 'Â';
		for(int loop2=0;loop2<COLWID-1;loop2++)
			out << 'Ä';
	}
	out << '¿' << endl;
}

void text_drawvalues(ofstream &out)
{
	long beginning;
	for(int r=0;r<ROWS;r++)
	{
		beginning=out.tellp();
		out << '³' << itemname[r];
		while(out.tellp()-beginning<ITEMLEN-1)
			out << ' ';
		for(int c=0;c<COLS;c++)
		{
			out << '³';
			beginning=out.tellp();
			out << item[r][c];
			while(out.tellp()-beginning<COLWID-1)
				out << ' ';
		}
		out << '³';
		out << endl;
	}
}

void tocheckfile()
{
	ofstream out(checkloc);
	out << CHECKCOUNTS;
	for(int loop=0;loop<ROWS;loop++)
		out << item[loop][COLS-1] << endl;
	out.close();
}


void save()
{
	ofstream out(saveloc);
	for(int c=0;c<COLS;c++)
		for(int r=0;r<ROWS;r++)
			out << item[r][c] << endl;
	out.close();
}

void load()
{
	ifstream in(saveloc);
	for(int c=0;c<COLS;c++)
		for(int r=0;r<ROWS;r++)
			in >> item[r][c];
	in.close();
	drawvalues();
}

/*
int wait_response()
{
	int inmessage=CHECKCOUNTS;
	ifstream in(checkfile);
	do {
		in.seekg(0);
		in >> inmessage;
	}while(inmessage==CHECKCOUNTS);
	switch(inmessage)
	{
		case(RECOUNTS):	while(!




}
*/
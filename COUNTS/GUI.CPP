#include <dir.h>

#include <fstream.h>
#include <iostream.h>

#include <stdlib.h>
#include <mem.h>
#include <graphics.h>
#include <conio.h>
#include <malloc.h>
#include <mouse.h>

//irrelevant things
int SHOWMOUSE=0; // 1 for yes 0 for no

const unsigned int MSG_YES=1;
const unsigned int MSG_NO=0;


const int MSG_WID=300;
const int MSG_HEIGHT=200;
const int MSG_X1=320-(MSG_WID/2);
const int MSG_Y1=240-(MSG_HEIGHT/2);
const int MSG_BSIZEX=MSG_WID/5;
const int MSG_BSIZEY=MSG_HEIGHT/6;


// max things
const int MAXTABLES=10;
const int MAXBUTTONS=70;

// mouse things
const int JUSTCLICKED=1;
const int NOTHING=0;

int _mousestatus=0;

const int rowwidth=15;
const int depth=4; // button 3d depth effect
const int tdepth=4; // table depth

struct objectlibrary;
class table;
class button;
class msgbox;


//********************************************
//********************************************
//********************************************
//********************************************


struct objectlibrary
{
	int numtables,numbuttons;
	table *tables[MAXTABLES];
	button *buttons[MAXBUTTONS];

	objectlibrary():numtables(0),numbuttons(0){};
	void addtable(table *t);
	void addbutton(button *b);

	int checkall();  // returns index of button pressed if any
	void drawall();
	void dis();
	void en();
};

//objectlibrary objects;



class table
{
	friend objectlibrary;
	char *mselected;
	int index;
	char far *value;
	int enabled;
	int selected;
	int ROWS;
	int COLS;
	int x1,y1,x2,y2;
	int windowposx,windowposy;
	int visiblecolumns;
	int visiblerows;
	int colwidth;
	int maxsize;
	int justify;

	public:

	table(objectlibrary *o,int i,int xx, int yy, int c, int r,
			int visc, int visr, int cwidth, int max, int just);
	~table();

	void setvalue(int column, int row, unsigned int val);
	void setvalue(int column, int row, char* val);

	unsigned int getvalue(int column, int row);
	char *getcvalue(int column,int row);


	void setselectedvalue(unsigned int val);
	void setselectedvalue(char* val);
	unsigned int getselectedvalue();
	char *getselectedcvalue(){return getcvalue(selected%COLS,selected/COLS);}

	int getselectedrow(){return selected/COLS;}
	int getselectedcol(){return selected%COLS;}

	int numcols(){return COLS;}
	int numrows(){return ROWS;}

	int getindex(){return index;}

	void scrollup();
	void scrolldown();
	void scrollleft();
	void scrollright();

	void click(); // this needs mouse coords to speed up so no
										// recalculation of mouse coords
	void select(int col, int row);
	void mselect(int c, int r);
	void munselect(int c, int r);
	void clear(){memset(value,0,ROWS*COLS*maxsize);draw();}

	void draw();
	void drawvalues();
	void drawvalue(int col,int row,int fcolor,int bcolor);
	void drawvalue(int col, int row);
	void drawselected();

	void dis(){enabled=0;}
	void en(){enabled=1;}

	void nextcell();

	int mouseover();
};

class button
{
	friend objectlibrary;
	int index;
	int x1,x2,y1,y2;
	int enabled;
	int visible;
	char *caption;

	public:
	button(objectlibrary *o,int i, int x, int y, int xwid, int ywid, char* cap);
	button(){}
	button(objectlibrary *o){o->addbutton(this);}

	void set(int i, int x, int y, int xwid, int ywid, char* cap);
	void set(objectlibrary *o){o->addbutton(this);}

	int mouseover(); // returns 1 if mouse is over
	void drawup();
	void drawdown();
	void click();

	int getindex(){return index;}

	void dis(){enabled=0;}
	void en(){enabled=1;}

	void hide();
	void show();

};

class msgbox
{
	objectlibrary mb;
	char* message;
	char background [long(MSG_WID)*long(MSG_HEIGHT)+10];
	button b_yes;
	button b_no;
	public:
		msgbox();
		int raise(char* message, int buttons);
}msg;

//********************************************
//********************************************
//********************************************
//********************************************



void mouse(); // sets all the mouse attributes gotten from mousestatus
void mousestatus(int &status); // status either JUSTRELEASED or 0

void setupgraphics();


//********************************************
//********************************************
//********************************************
//********************************************



void objectlibrary::addtable(table *t)
{
	tables[numtables]=t;
	numtables++;
}

void objectlibrary::addbutton(button *b)
{
	buttons[numbuttons]=b;
	numbuttons++;
}

void objectlibrary::dis()
{
	for(int loop=0;loop<numbuttons;loop++)
		buttons[loop]->dis();
	for(loop=0;loop<numtables;loop++)
		tables[loop]->dis();
}

void objectlibrary::en()
{
	for(int loop=0;loop<numbuttons;loop++)
		buttons[loop]->en();
	for(loop=0;loop<numtables;loop++)
		tables[loop]->en();
}

int objectlibrary::checkall()
{
	int loop,temp,clicked;
	mouse();
	mousestatus(clicked);
	if(clicked)
	{
		for(loop=0;loop<numbuttons;loop++)
		{
			if(buttons[loop]->mouseover() && buttons[loop]->enabled)
			{
				if(SHOWMOUSE) hidemouse();
				buttons[loop]->click();
				if(SHOWMOUSE) showmouse();
				return buttons[loop]->getindex();
			}
		}
		for(loop=0;loop<numtables;loop++)
		{
			if(tables[loop]->mouseover() && tables[loop]->enabled)
			{
				if(SHOWMOUSE) hidemouse();
				tables[loop]->click();
				if(SHOWMOUSE) showmouse();
				return tables[loop]->getindex();
			}
		}
	}
	return -1;
}

void objectlibrary::drawall()
{
	int loop;
	for(loop=0;loop<numbuttons;loop++)
		buttons[loop]->drawup();
	for(loop=0;loop<numtables;loop++)
		tables[loop]->draw();
}


//********************************************
//********************************************
//********************************************
//********************************************


void mouse()
{
	_mousestatus=mouseclicked(0);
}

void mousestatus(int &status)
{
	status=_mousestatus;
}

void drawwindow(int x1, int y1, int x2, int y2)
{
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);

	setcolor(15);
	int i;
	for(i=0;i<tdepth+1;i++)
	{
		line(x1+i,y1+i,x1+i,y2-i);
		line(x1+i,y1+i,x2-i,y1+i);
	}
	setcolor(8);
	for(i=0;i<tdepth+1;i++)
	{
		line(x2-i,y2-i,x1+i,y2-i);
		line(x2-i,y2-i,x2-i,y1+i);
	}
	setcolor(0);
	rectangle(x1,y1,x2,y2);
	rectangle(x1+tdepth,y1+tdepth,x2-tdepth,y2-tdepth);
	line(x1+tdepth,y1+tdepth,x1,y1);
	line(x2-tdepth,y1+tdepth,x2,y1);
	line(x1+tdepth,y2-tdepth,x1,y2);
	line(x2-tdepth,y2-tdepth,x2,y2);

}

void setupgraphics()
{

	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "egavga.bgi");
	setfillstyle(1,7);
	bar(0,0,640,480);
}

int strpos(char* v, char c)
{
	for(int loop=0;v[loop]!=c && v[loop]!=0;loop++);
	if(v[loop]==0) return -1;
	else return loop;
}


//********************************************
//********************************************
//********************************************
//********************************************


table::table(objectlibrary *o,int i,int xx, int yy, int c, int r,
			int visc, int visr, int cwidth, int max, int just):
			index(i),x1(xx),y1(yy),ROWS(r),COLS(c),
			colwidth(cwidth),visiblecolumns(visc),visiblerows(visr),
			maxsize(max),justify(just)
{
	mselected=(char*)malloc(COLS*ROWS);
	memset(mselected,0,COLS*ROWS);
	enabled=1;
	if(visc>c) visiblecolumns=COLS;
	if(visr>r) visiblerows=ROWS;
	x2=x1+(colwidth*visiblecolumns);
	y2=y1+(rowwidth*visiblerows);

	value=(char far*)farmalloc(ROWS*COLS*maxsize);
	if(value==0)
		cout << "Error...not enough memory";
	else
	{
		memset(value,0,ROWS*COLS*maxsize);
		windowposx=windowposy=0;
		o->addtable(this);
		selected=0;
		//draw();
	}
}

table::~table()
{
	farfree(value);
}


void table::setvalue(int column, int row, unsigned int val)
{
	if(row<ROWS && column<COLS)
	{
		ultoa(val,&value[(COLS*row+column)*maxsize],10);
		drawvalue(column,row);
	}
	else
		cout << "Error: Reaching out of table limits\n";
}

void table::setvalue(int column, int row, char* val)
{
	if(row<ROWS && column<COLS)
	{
		memcpy(&value[(COLS*row+column)*maxsize],val,maxsize);
		drawvalue(column,row);
	}
	else
		cout << "Error: Reaching out of table limits\n";
}
unsigned int table::getvalue(int column, int row)
{
	if(row<ROWS && column<COLS)
		return atoi(&value[(COLS*row+column)*maxsize]);
	else
		cout << "Error: Reaching out of table limits\n";
	return 0;
}


char* table::getcvalue(int column, int row)
{
	if(row<ROWS && column< COLS)
		return &value[(row*COLS+column)*maxsize];
	else
	{
		cout << "Error: Reaching out of table limits\n";
		return 0;
	}
}

void table::setselectedvalue(unsigned int val)
{
	if(selected<ROWS*COLS)
	{
		ultoa(val,&value[selected*maxsize],10);
		drawselected();
	}
	else
		cout << "Error: Reaching out of table limits\n";
}

void table::setselectedvalue(char* val)
{
	if(selected<ROWS*COLS)
	{
		memcpy(&value[selected*maxsize],val,maxsize);
		drawselected();
	}
	else
		cout << "Error: Reaching out of table limits\n";
}
unsigned int table::getselectedvalue()
{
	if(selected<ROWS*COLS)
		return atoi(&value[selected*maxsize]);
	else
		cout << "Error: Reaching out of table limits\n";
	return 0;
}


void table::scrollup()
{
	if(windowposy>0)
	{
		windowposy--;
		drawvalues();
	}
}

void table::scrolldown()
{
	if(windowposy+visiblerows<ROWS)
	{	windowposy++;
		drawvalues();
	}
}

void table::scrollleft()
{
	if(windowposx>0)
	{
		windowposx--;
		drawvalues();
	}
}

void table::scrollright()
{
	if(windowposx+visiblecolumns<COLS)
	{
		windowposx++;
		drawvalues();
	}

}


void table::drawvalues()
{
	for(int r=windowposy;r<windowposy+visiblerows;r++)
		for(int c=windowposx;c<windowposx+visiblecolumns;c++)
			drawvalue(c,r);
}


void table::draw()
{
	setcolor(8);
	int i;
	for(i=1;i<tdepth;i++)
	{
		line(x1-i,y1-i,x1-i,y2+i);
		line(x1-i,y1-i,x2+i,y1-i);
	}
	setcolor(15);
	for(i=1;i<tdepth;i++)
	{
		line(x2+i,y2+i,x1-i,y2+i);
		line(x2+i,y2+i,x2+i,y1-i);
	}
	setcolor(0);
	line(x1-tdepth,y1-tdepth,x1,y1);
	line(x2+tdepth,y1-tdepth,x2,y1);
	line(x1-tdepth,y2+tdepth,x1,y2);
	line(x2+tdepth,y2+tdepth,x2,y2);
	rectangle(x1-tdepth,y1-tdepth,x2+tdepth,y2+tdepth);

	setfillstyle(1,15);
	bar(x1,y1,x2,y2);
	setcolor(0);
	int xpos=x1,ypos=y1;
	for(int loop=0;loop<=visiblecolumns;loop++)
	{
		line(xpos,y1,xpos,y2);
		xpos+=colwidth;
	}
	for(loop=0;loop<=visiblerows;loop++)
	{
		line(x1,ypos,x2,ypos);
		ypos+=rowwidth;
	}
	drawvalues();
}

void table::drawvalue(int col, int row, int fcolor, int bcolor)
{
	if(row>=windowposy && row<=windowposy+visiblerows-1 &&
		col>=windowposx && col<=windowposx+visiblecolumns-1)
	{
		settextjustify(justify,BOTTOM_TEXT);
		int x,y;
		x=x1+(col-windowposx)*colwidth;
		y=y1+(row-windowposy)*rowwidth;
		setfillstyle(1,bcolor);
		bar(x+1,y+1,x+colwidth-1,y+rowwidth-1);
		switch(justify)
		{
			case(RIGHT_TEXT):	x=x1+(col-windowposx+1)*colwidth;
									y=y1+(row-windowposy+1)*rowwidth;
									break;
			case(LEFT_TEXT):	x=x1+(col-windowposx)*colwidth+3;
									y=y1+(row-windowposy+1)*rowwidth-3;
									break;

		}

		setcolor(fcolor);
		outtextxy(x,y,getcvalue(col,row));
	}
}

void table::drawvalue(int col, int row)
{
	if(selected==(row*COLS+col))
		drawvalue(col,row,WHITE,RED);
	else if(mselected[row*COLS+col]==1)
		drawvalue(col,row,WHITE,GREEN);
	else
		drawvalue(col,row,BLACK,WHITE);
}

void table::drawselected()
{
	drawvalue(selected%COLS,selected/COLS,15,4);
}


void table::nextcell()
{
	drawvalue(selected%COLS,selected/COLS,0,15);
	int r,c;
	r=selected/COLS;
	c=selected%COLS;
	if(++r>=ROWS)
	{
		r=0;
		if(++c>=COLS)
			c=0;
	}
	select(c,r);
}


int table::mouseover()
{
	int temp,x,y;
	x=readmousex();
	y=readmousey();
	mousestatus(temp);
	return (x>x1 && x<x2 && y>y1 && y<y2);
}

void table::click()
{
	int x,y,col,row;
	x=readmousex();
	y=readmousey();
	col=x-x1;
	row=y-y1;
	col/=colwidth;
	row/=rowwidth;
	select(col+windowposx,row+windowposy);
}

void table::select(int col, int row)
{
	int srow, scol,oc,or;
	int x,y;
	char v[6];
	srow=selected/COLS;
	scol=selected%COLS;
	oc=scol;
	or=srow;

	//drawvalue(scol,srow,0,15);
	srow=row;
	scol=col;
	selected=srow*COLS+scol;
	drawvalue(oc,or);
	drawvalue(scol,srow);
}

void table::mselect(int c, int r)
{
	mselected[r*COLS+c]=1;
	drawvalue(c,r);
}

void table::munselect(int c, int r)
{
	mselected[r*COLS+c]=0;
	drawvalue(c,r);
}




//********************************************
//********************************************
//********************************************
//********************************************



button::button(objectlibrary *o,int i, int x, int y, int xwid, int ywid, char* cap):
		index(i),x1(x),y1(y)
{
	x2=x1+xwid;
	y2=y1+ywid;
	caption=cap;
	o->addbutton(this);
	enabled=1;
	visible=1;
	drawup();
}

void button::set(int i, int x, int y, int xwid, int ywid, char* cap)
{
	index=i;
	x1=x;
	y1=y;
	x2=x1+xwid;
	y2=y1+ywid;
	caption=cap;
	enabled=1;
	visible=1;
}



void button::hide()
{
	visible=0;
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
}

void button::show()
{
	visible=1;
	drawup();
}


int button::mouseover()
{
	int temp,x,y;
	x=readmousex();
	y=readmousey();
	mousestatus(temp);
	return (x>=x1 && x<=x2 && y>=y1 && y<=y2);
}

void button::click()
{
	drawdown();
	delay(50);
	drawup();
}

void button::drawup()
{
	int ywidth=y2-y1;
	int xwidth=x2-x1;
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	setcolor(16);
	rectangle(x1+depth,y1+depth,x2-depth,y2-depth);
	line(x1,y1,x1+depth,y1+depth);
	line(x2,y2,x2-depth,y2-depth);
	line(x1,y2,x1+depth,y2-depth);
	line(x2,y1,x2-depth,y1+depth);
	rectangle(x1-1,y1-1,x2+1,y2+1);
	setfillstyle(1,8);
	floodfill(x1+depth/2,y1+ywidth,0);
	floodfill(x1+xwidth,y1+depth/2,0);
	setfillstyle(1,15);
	floodfill(x2-depth/2,y2-ywidth,0);
	floodfill(x2-xwidth,y2-depth/2,0);
	setfillstyle(1,7);
	floodfill(x1+xwidth/2,y1+ywidth/2,0);
	setcolor(15);
	settextjustify(1,1);
	outtextxy(x1+xwidth/2,y1+ywidth/2,caption);
	setcolor(16);
	outtextxy(x1+xwidth/2+1,y1+ywidth/2+1,caption);

	setcolor(16);
}


void button::drawdown()
{
	int ywidth=y2-y1;
	int xwidth=x2-x1;

	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	setcolor(16);
	rectangle(x1+depth,y1+depth,x2-depth,y2-depth);
	line(x1,y1,x1+depth,y1+depth);
	line(x2,y2,x2-depth,y2-depth);
	line(x1,y2,x1+depth,y2-depth);
	line(x2,y1,x2-depth,y1+depth);
	rectangle(x1-1,y1-1,x2+1,y2+1);
	setfillstyle(1,15);
	floodfill(x1+depth/2,y1+ywidth,0);
	floodfill(x1+xwidth,y1+depth/2,0);
	setfillstyle(1,8);
	floodfill(x2-depth/2,y2-ywidth,0);
	floodfill(x2-xwidth,y2-depth/2,0);
	setfillstyle(1,7);
	floodfill(x1+xwidth/2,y1+ywidth/2,0);
	setcolor(15);
	settextjustify(1,1);
	outtextxy(x1+xwidth/2+3,y1+ywidth/2+2,caption);
	setcolor(16);
	outtextxy(x1+xwidth/2+3+1,y1+ywidth/2+2+1,caption);
}


//********************************************
//********************************************
//********************************************
//********************************************


msgbox::msgbox()
{
	setupgraphics();
	b_yes.set(&mb);
	b_no.set(&mb);
	b_yes.set(MSG_YES,MSG_X1+25,MSG_Y1+MSG_HEIGHT-(MSG_BSIZEY+15),MSG_BSIZEX,MSG_BSIZEY,"Yes");
	b_no.set(MSG_NO,MSG_X1+MSG_WID-MSG_BSIZEX-25,MSG_Y1+MSG_HEIGHT-(MSG_BSIZEY+15),MSG_BSIZEX,MSG_BSIZEY,"No");
	b_yes.hide();
	b_no.hide();
	b_yes.dis();
	b_no.dis();
	closegraph();
}

int msgbox::raise(char* message, int buttons)
{
	char m[80];
	int x1=MSG_X1;
	int y1=MSG_Y1;
	int x2=MSG_X1+MSG_WID;
	int y2=MSG_Y1+MSG_HEIGHT;
	getimage(x1,y1,x2,y2,background);
	drawwindow(x1,y1,x2,y2);

	int texty=y1+20;
	int pos=0,opos=0;
	settextjustify(CENTER_TEXT,CENTER_TEXT);

	while(message[opos-1]!=0 || opos<1)
	{
		pos++;
		if(message[pos]=='\n' || message[pos]==0)
		{
			memset(m,0,80);
			memcpy(m,&message[opos],pos-opos);
			outtextxy(320,texty,m);
			texty+=20;
			opos=pos+1;
		}
	}


	b_yes.show();
	b_yes.en();
	if(buttons==2)
	{
		b_no.show();
		b_no.en();
	}
	int status=-1;
	while(status!=MSG_YES && status!=MSG_NO)
		status=mb.checkall();

	putimage(MSG_X1,MSG_Y1,background,0);
	return status;
}

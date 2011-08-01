#include<c:\tc\bin\chops\include.h>
#include<c:\warchops\image.h>

//#include<h:\include.h>
//#include<h:\warchops\image.h>

const int size=15;
const int screen_ysize=31;
const int screen_xsize=37;
const int xsize=37;
const int ysize=31;
const int xsmall=75;
const int ysmall=10;

const int h1=1;
const int h2=2;
const int b1=3;
const int b2=4;
const int t1=5;
const int t2=6;
const int p1=7;
const int p2=8;
const int w1=9;
const int w2=10;
const int z1=11;
const int z2=12;
const int m=13;
const int g=14;
const int w=15;

int selected=0;
int x,y;

small_image hall1;
small_image hall2;
small_image barrack1;
small_image barrack2;
small_image temple1;
small_image temple2;
small_image mine;
small_image peon1;
small_image peon2;
small_image warr1;
small_image warr2;
small_image wizard1;
small_image wizard2;
small_image grass;
small_image water;

struct coord_type
{
	char terrain;
	char unit;
} map[xsize][ysize];
int mousestatus;

void mousestat()
{
	if(mousestatus==4) mousestatus=2;
	else if(mousestatus==3) mousestatus=1;
	else if(mousereleased(0)==1) mousestatus=4;
	else if(mouseclicked(0)==1) mousestatus=3;
}




void draw_coord(int x, int y)
{
	//terrain
	if(map[x][y].terrain==g) grass.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].terrain==w) water.draw(xsmall+x*size,ysmall+y*size,0);

	//units
	if(map[x][y].unit==h1) hall1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==h2) hall2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==b1) barrack1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==b2) barrack2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==t1) temple1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==t2) temple2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==p1) peon1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==p2) peon2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==w1) warr1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==w2) warr2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==z1) wizard1.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==z2) wizard2.draw(xsmall+x*size,ysmall+y*size,0);
	else if(map[x][y].unit==m) mine.draw(xsmall+x*size,ysmall+y*size,0);

}

void drawall()
{
	for(int loopx=0;loopx<xsize;loopx++)
	{
		for(int loopy=0;loopy<ysize;loopy++)
		{
			draw_coord(loopx,loopy);
		}
	}
}


void clear()
{
	for(int loopx=0;loopx<xsize;loopx++)
	{
		for(int loopy=0;loopy<ysize;loopy++)
		{
			map[loopx][loopy].terrain=g;
			map[loopx][loopy].unit=0;
			draw_coord(loopx,loopy);
		}
	}
}

void load()
{
	mine.load("c:\\warchops\\mine.wcp");
	hall2.load("c:\\warchops\\hall2.wcp");
	hall1.load("c:\\warchops\\hall1.wcp");
	barrack1.load("c:\\warchops\\barrack1.wcp");
	barrack2.load("c:\\warchops\\barrack2.wcp");
	temple1.load("c:\\warchops\\temple1.wcp");
	temple2.load("c:\\warchops\\temple2.wcp");


	peon1.load("c:\\warchops\\peon1.wcp");
	peon2.load("c:\\warchops\\peon2.wcp");
	warr1.load("c:\\warchops\\warr1.wcp");
	warr2.load("c:\\warchops\\warr2.wcp");
	wizard1.load("c:\\warchops\\wizard1.wcp");
	wizard2.load("c:\\warchops\\wizard2.wcp");

	grass.load("c:\\warchops\\grass.wcp");
	water.load("c:\\warchops\\water.wcp");
	clear();



}

void drawselected()
{
	setfillstyle(1,0);
	bar(10,200,25,215);
	if(selected==h1) hall1.draw(10,200,0);
	else if(selected==h2) hall2.draw(10,200,0);
	else if(selected==b1) barrack1.draw(10,200,0);
	else if(selected==b2) barrack2.draw(10,200,0);
	else if(selected==t1) temple1.draw(10,200,0);
	else if(selected==t2) temple2.draw(10,200,0);
	else if(selected==p1) peon1.draw(10,200,0);
	else if(selected==p2) peon2.draw(10,200,0);
	else if(selected==w1) warr1.draw(10,200,0);
	else if(selected==w2) warr2.draw(10,200,0);
	else if(selected==z1) wizard1.draw(10,200,0);
	else if(selected==z2) wizard2.draw(10,200,0);
	else if(selected==m) mine.draw(10,200,0);
	else if(selected==g) grass.draw(10,200,0);
	else if(selected==w) water.draw(10,200,0);
}

void select()
{
	x=readmousex();
	y=readmousey();
	if(x>=10 && x<=40 && y>=10 && y<=130 && mousestatus==3)
	{
		if(y<25)
		{
			if(x<25) selected=h1;
			else selected=h2;
		}
		else if(y<40)
		{
			if(x<25) selected=p1;
			else selected=p2;
		}
		else if(y<55)
		{
			if(x<25) selected=w1;
			else selected=w2;
		}
		else if(y<70)
		{
			if(x<25) selected=z1;
			else selected=z2;
		}
		else if(y<85)
		{
			if(x<25) selected=m;
		}
		else if(y<100)
		{
			if(x<25) selected=b1;
			else selected=b2;
		}
		else if(y<115)
		{
			if(x<25) selected=t1;
			else selected=t2;
		}
		else if(y<130)
		{
			if(x<25) selected=g;
			else selected=w;
		}
		drawselected();
	}
}


void place()
{
	int x1,x2,y1,y2;
	if(x>xsmall && x<xsmall+size*xsize && y>ysmall && y<ysmall+size*ysize && mousestatus==1)
	{
		for(int loopx=0;loopx<xsize;loopx++)
		{
			for(int loopy=0;loopy<ysize;loopy++)
			{
				x1=xsmall+loopx*size;
				x2=x1+size;
				y1=ysmall+loopy*size;
				y2=y1+size;
				if(x>=x1 && x<x2 && y>=y1 && y<y2)
				{
					if(selected==g)
					{
						map[loopx][loopy].terrain=g;
						map[loopx][loopy].unit=0;
						hidemouse();
						draw_coord(loopx,loopy);
						showmouse();
					}
					else if(selected==w)
					{
						map[loopx][loopy].terrain=w;
						map[loopx][loopy].unit=0;
						hidemouse();
						draw_coord(loopx,loopy);
						showmouse();
					}
					else if(map[loopx][loopy].unit!=selected)
					{
						map[loopx][loopy].terrain=g;
						map[loopx][loopy].unit=selected;
						hidemouse();
						draw_coord(loopx,loopy);
						showmouse();
					}

				}
			}
		}
	}
}




void savefile()
{
	ofstream file;
	file.open("c:\\warchops\\map1.map");
	for(int loopx=0;loopx<xsize;loopx++)
	{
		for(int loopy=0;loopy<ysize;loopy++)
		{
			map[loopx][loopy].terrain+=50;
			map[loopx][loopy].unit+=50;
			file << map[loopx][loopy].terrain << endl;
			file << map[loopx][loopy].unit << endl;
			map[loopx][loopy].terrain-=50;
			map[loopx][loopy].unit-=50;
		}
	}
	file.close();
}

void loadfile()
{
	ifstream file;
	file.open("c:\\warchops\\map1.map");
	for(int loopx=0;loopx<xsize;loopx++)
	{
		for(int loopy=0;loopy<ysize;loopy++)
		{
			file >> map[loopx][loopy].terrain;
			file >> map[loopx][loopy].unit;
			map[loopx][loopy].terrain-=50;
			map[loopx][loopy].unit-=50;
		}
	}
	file.close();
	drawall();
}


void main()
{
	char choice;
	setup();
	load();
	setcolor(15);
	rectangle(xsmall-1,ysmall-1,xsmall+(size*screen_xsize)+1,ysmall+(size*screen_ysize)+1);


	hall1.draw(10,10,0);
	hall2.draw(25,10,0);
	peon1.draw(10,25,0);
	peon2.draw(25,25,0);
	warr1.draw(10,40,0);
	warr2.draw(25,40,0);
	wizard1.draw(10,55,0);
	wizard2.draw(25,55,0);
	mine.draw(10,70,0);
	barrack1.draw(10,85,0);
	barrack2.draw(25,85,0);
	temple1.draw(10,100,0);
	temple2.draw(25,100,0);
	grass.draw(10,115,0);
	water.draw(25,115,0);
	showmouse();
	do
	{
		do
		{
			mousestat();
			select();
			place();
		}while(bioskey(1)==0);
		choice=toupper(getch());
		switch(choice)
		{
			case('S'):
			{
				savefile();
				break;
			}
			case('L'):
			{
				loadfile();
				break;
			}
			case('N'):
			{
				clear();
				break;
			}
		}
	}while(choice!='Q');
	closegraph();

}
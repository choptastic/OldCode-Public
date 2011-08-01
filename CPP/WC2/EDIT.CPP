#include<dir.h>
#include<BIOS.H>
#include<CONIO.H>
#include<CTYPE.H>
#include<DOS.H>
#include<GRAPHICS.H>
#include<IOSTREAM.H>
#include<STDIO.H>
#include<STDLIB.H>
#include<mouse.h>
#include<fstream.h>
#include<c:\cpp\wc2\image.h>

const int size=30;
const int xscreen=17;
const int yscreen=11;
const int xsize=99;
const int ysize=99;
const int xvisual=120;
const int yvisual=15;

small_image grass1;
small_image mud1;
small_image water1;
small_image hall1;
small_image mine1;
small_image pointer;

const int grass=200;
const int mud=201;
const int water=202;
const int mine=106;

char startx[2];
char starty[2];
int xbottom=0;
int ybottom=0;
int page=0;
int selection=0;


class map_type
{
	public:
	unsigned char terrain;
}map[100][100];

class mine_type
{
	public:
	char x,y;
}mines[8];

map_type old[xscreen+1][yscreen+1][2];

char minimaps[100][100][2];

int mousestatus;

int pointback[30][30][2];
int x,y;

void clearpointback()
{
	for(int loopx=0;loopx<30;loopx++)
	for(int loopy=0;loopy<30;loopy++)
	{

		pointback[loopx][loopy][1]=-1;
		pointback[loopx][loopy][0]=-1;
	}
}
void drawpointback()
{
	for(int loopx=0;loopx<30;loopx++)
	for(int loopy=0;loopy<30;loopy++)
	{

		if(pointback[loopx][loopy][page]!=-1) putpixel(loopx+x,loopy+y,pointback[loopx][loopy][page]);
	}
}

void getback()
{
	for(int loopx=0;loopx<30;loopx++)
	for(int loopy=0;loopy<30;loopy++)
	{

		pointback[loopx][loopy][page]=getpixel(loopx+x,loopy+y);
	}
}

void hidepointer()
{
	drawpointback();
	x=readmousex();
	y=readmousey();
	clearpointback();
}


void drawpointer()
{

	if(mousemoved()==1)
	{
		hidepointer();
		getback();
		pointer.draw(x,y,0,0);
		/*
		if(selection==0) hall1.draw(x,y,0,selection+3);
		else if(selection==1) hall1.draw(x,y,0,selection+3);
		else if(selection==water) water1.draw(x,y,0,0);
		else if(selection==mud) mud1.draw(x,y,0,0);
		else if(selection==grass) grass1.draw(x,y,0,0);
		else if(selection==mine) mine1.draw(x,y,0,0);
		*/
	}
}

void mousestat()
{
	if(mousestatus==4) mousestatus=2;
	else if(mousestatus==3) mousestatus=1;
	else if(mousereleased(0)==1) mousestatus=4;
	else if(mouseclicked(0)==1) mousestatus=3;
}


void setup()
{
   int gdriver = EGA, gmode = EGAHI, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
}


void loadpics()
{
	grass1.load("grass.wcp");
	mud1.load("mud.wcp");
	water1.load("water.wcp");
	hall1.load("hall.wcp");
	mine1.load("mine.wcp");
	pointer.load("pointer.pnt");
}
void drawbase()
{
	setactivepage(0);
	setcolor(15);
	rectangle(xvisual,yvisual,xvisual+size*xscreen,yvisual+size*yscreen);
	rectangle(1,1,102,102);
	setactivepage(1);
	setcolor(15);
	rectangle(xvisual-2,yvisual-2,xvisual+size*xscreen,yvisual+size*yscreen);
	rectangle(1,1,102,102);
}

void clear()
{
	for(int loopx=0;loopx<100;loopx++)
	for(int loopy=0;loopy<100;loopy++)
	{
		map[loopx][loopy].terrain=grass;
	}
	for(int loop=0;loop<8;loop++) mines[loop].x=-1;
}


void minimap()
{

	for(int loopx=0;loopx<100;loopx++)
	for(int loopy=0;loopy<100;loopy++)
	{

		if(map[loopx][loopy].terrain==grass && minimaps[loopx][loopy][page]!=2)
		{
			putpixel(loopx+2,loopy+2,2);
			minimaps[loopx][loopy][page]=2;
		}
		else if(map[loopx][loopy].terrain==mud && minimaps[loopx][loopy][page]!=6)
		{
			putpixel(loopx+2,loopy+2,6);
			minimaps[loopx][loopy][page]=6;
		}
		else if(map[loopx][loopy].terrain==water && minimaps[loopx][loopy][page]!=1)
		{
			putpixel(loopx+2,loopy+2,1);
			minimaps[loopx][loopy][page]=1;
		}
	}


	for(int loop=0;loop<2;loop++)
	{
		if(minimaps[startx[loop]][starty[loop]][page]!=loop+3)
		{
			minimaps[startx[loop]][starty[loop]][page]=loop+3;
			putpixel(startx[loop]+2,starty[loop]+2,loop+3);
		}
	}
	for(loop=0;loop<8;loop++)
	{
		if(minimaps[mines[loop].x][mines[loop].y][page]!=14)
		{
			minimaps[mines[loop].x][mines[loop].y][page]=14;
			putpixel(mines[loop].x+2,mines[loop].y+2,14);
		}
	}

	for(loop=xbottom;loop<=xbottom+xscreen;loop++) minimaps[loop][ybottom][page]=15;
	for(loop=ybottom;loop<=ybottom+yscreen;loop++) minimaps[xbottom][loop][page]=15;
	for(loop=xbottom;loop<=xbottom+xscreen;loop++) minimaps[loop][ybottom+yscreen][page]=15;
	for(loop=ybottom;loop<=ybottom+yscreen;loop++) minimaps[xbottom+xscreen][loop][page]=15;

	rectangle(xbottom+2,ybottom+2,xbottom+2+xscreen,ybottom+2+yscreen);
}



void oldscreen()
{

	for(int loopx=0;loopx<xscreen;loopx++)
	for(int loopy=0;loopy<xscreen;loopy++)
	{
		old[loopx][loopy][page].terrain=map[loopx+xbottom][loopy+ybottom].terrain;
	}
	for(int loop=0;loop<2;loop++)
	{
		if(startx[loop]>=xbottom && startx[loop]<xbottom+xscreen && starty[loop]>=ybottom && starty[loop]<ybottom+yscreen)
		old [startx[loop]-xbottom] [starty[loop]-ybottom][page].terrain=loop;
	}
	for(loop=0;loop<8;loop++)
	{
		if(mines[loop].x>=xbottom && mines[loop].x<xbottom+xscreen && mines[loop].y>=ybottom && mines[loop].y<ybottom+yscreen)
		old [mines[loop].x-xbottom] [mines[loop].y-ybottom][page].terrain=mine;
	}
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void drawmap()
{

	drawpointback();
	int loop;
	if(page==0) page=1;
	else page=0;
	//drawpointback();
	//hidepointer();
	setactivepage(page);
	int x,y;
	for(int loopx=0;loopx<xscreen;loopx++)
	for(int loopy=0;loopy<yscreen;loopy++)
	{
		x=xbottom+loopx;
		y=ybottom+loopy;
		if(map[x][y].terrain!=old[loopx][loopy][page].terrain)
		{
			if(map[x][y].terrain==grass) grass1.draw(xvisual+loopx*size,yvisual+loopy*size,0,0);
			else if(map[x][y].terrain==mud) mud1.draw(xvisual+loopx*size,yvisual+loopy*size,0,0);
			else if(map[x][y].terrain==water) water1.draw(xvisual+loopx*size,yvisual+loopy*size,0,0);
		}
	}

	for(loop=0;loop<2;loop++)
	{
		x=startx[loop];
		y=starty[loop];
		if(x>=xbottom && x<xbottom+xscreen && y>=ybottom && y<ybottom+yscreen)
		hall1.draw(xvisual+(x-xbottom)*size,yvisual+(y-ybottom)*size,0,loop+3);
	}
	for(loop=0;loop<8;loop++)
	{
		if(mines[loop].x!=-1)
		{
			x=mines[loop].x;
			y=mines[loop].y;
			if(x>=xbottom && x<xbottom+xscreen && y>=ybottom && y<ybottom+yscreen)
			mine1.draw(xvisual+(x-xbottom)*size,yvisual+(y-ybottom)*size,0,0);
		}
	}

	minimap();
	clearpointback();
	setvisualpage(page);

	//drawpointer();
	oldscreen();
}

void changescreen()
{
	int x=readmousex();
	int y=readmousey();
	if(x<2 && xbottom>0)
	{
		xbottom--;
		drawmap();
	}
	else if(x>638 && xbottom<xsize-xscreen)
	{
		xbottom++;
		drawmap();
	}

	if(y<2 && ybottom>0)
	{
		ybottom--;
		drawmap();
	}
	else if(y>348 && ybottom<ysize-yscreen)
	{
		ybottom++;
		drawmap();
	}
}

void checkclick()
{
	int x,y,added,gonnabreak=0;
	x=readmousex();
	y=readmousey();
	if(mousestatus==1)
	{

		if(x>=xvisual && y>=yvisual)
		{
			for(int loopx=0;loopx<xscreen;loopx++)
			for(int loopy=0;loopy<yscreen;loopy++)
			{
				if(x>=xvisual+loopx*size && x<xvisual+loopx*size+size && y>=yvisual+loopy*size && y<yvisual+loopy*size+size)
				{
					if(selection<2)
					{
						startx[selection]=loopx+xbottom;
						starty[selection]=loopy+ybottom;
						drawmap();
					}
					else if(selection==grass)
					{
						map[loopx+xbottom][loopy+ybottom].terrain=grass;
						drawmap();
					}
					else if(selection==mud)
					{
						map[loopx+xbottom][loopy+ybottom].terrain=mud;
						drawmap();
					}
					else if(selection==water)
					{
						map[loopx+xbottom][loopy+ybottom].terrain=water;
						drawmap();
					}

				}

			}
		}
		else if(x>=2 && x<102 && y>=2 && y<102)
		{
			xbottom=x-2-8;
			ybottom=y-2-5;
			if(xbottom<0) xbottom=0;
			if(ybottom<0) ybottom=0;
			drawmap();
		}

	}
	if(selection==mine && mousestatus==3)
	{
		//for(int loop=0;loop<8;loop++)
		//{
			for(int loopx=0;loopx<xscreen;loopx++)
			{
				for(int loopy=0;loopy<yscreen;loopy++)
				{
					if(x>=xvisual+loopx*size && x<xvisual+loopx*size+size && y>=yvisual+loopy*size && y<yvisual+loopy*size+size)
					{
						//if(mines[loop].x!=loopx && mines[loop].y!=loopy)
						//{
							for(int loop1=7;loop1>0;loop1--) mines[loop1]=mines[loop1-1];

							mines[0].x=loopx+xbottom;
							mines[0].y=loopy+ybottom;

							gonnabreak=1;
							break;
						//}
					}

				}
				if(gonnabreak==1) break;
			}
			if(gonnabreak==1)
			{
				drawmap();
				//break;
			}
		//}
	}

}

void save()
{
	ofstream file;
	file.open("map");
	for(int loopx=0;loopx<100;loopx++)
	for(int loopy=0;loopy<100;loopy++)
	{
		file << map[loopx][loopy].terrain << endl;
	}
	for(int loop=0;loop<2;loop++)
	{
		startx[loop]+=27;
		starty[loop]+=27;

		file << startx[loop] << endl;
		file << starty[loop] << endl;

		startx[loop]-=27;
		starty[loop]-=27;
	}
	for(loop=0;loop<8;loop++)
	{

		mines[loop].x+=27;
		mines[loop].y+=27;

		file << mines[loop].x << endl;
		file << mines[loop].y << endl;

		mines[loop].x-=27;
		mines[loop].y-=27;
	}
	file.close();

}
void load()
{
	ifstream file;
	file.open("map");
	for(int loopx=0;loopx<100;loopx++)
	for(int loopy=0;loopy<100;loopy++)
	{
		file >> map[loopx][loopy].terrain;
	}
	for(int loop=0;loop<2;loop++)
	{
		file >> startx[loop];
		startx[loop]-=27;
		file >> starty[loop];
		starty[loop]-=27;
	}
	for(loop=0;loop<8;loop++)
	{
		file >> mines[loop].x;
		mines[loop].x-=27;
		file >> mines[loop].y;
		mines[loop].y-=27;
	}
	file.close();
	drawmap();

}





void main()
{
	chdir("c:\\cpp\\wc2");
	char choice;
	setup();
	mouselimit(1,1,640,350);
	x=1;
	y=300;
	initmouse();
	drawbase();
	loadpics();
	clear();
	page=1;
	drawmap();
	drawmap();
	//drawpointer();
	//showmouse();
	do
	{
		do
		{
			changescreen();
			checkclick();
			mousestat();
			drawpointer();
			//drawmap();
			//delay(20);
		}while(bioskey(1)==0);
		choice=toupper(getch());
		if(choice=='0') selection=0;
		else if(choice=='1') selection=1;
		else if(choice=='U') selection=mud;
		else if(choice=='W') selection=water;
		else if(choice=='G') selection=grass;
		else if(choice=='S') save();
		else if(choice=='L') load();
		else if(choice=='M') selection=mine;
	}while(choice!='Q');

}






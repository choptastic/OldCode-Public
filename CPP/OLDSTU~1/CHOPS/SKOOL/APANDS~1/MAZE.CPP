#include<d:\tc\bin\chops\skool\include\include.h>


const int maxx=62,maxy=46;
const int size=10;
int maze[maxx][maxy];
int fastest[maxx][maxy];
int cx,cy;

void drawmaze();
void createmaze();
int move(int ox, int oy,int x, int y);
void drawfastest();
void save();
void load();
void newmaze();
void drawsection(int loopx, int loopy);

void main()
{
	setup();
	cleardevice();
	createmaze();
	for(int loopx=1;loopx<maxx;loopx++)
	{
		for(int loopy=1;loopy<maxx;loopy++)
		{
			if(maze[loopx][loopy]==2)
			{
				cx=loopx;
				cy=loopy;
			}

			bar(cx*size-size,cy*size-size,cx*size,cy*size);
		}
	}
	drawmaze();
	getch();
	for(loopx=0;loopx<maxx;loopx++)
	{
		for(int loopy=0;loopy<maxy;loopy++)
		{
			fastest[loopx][loopy]=0;
		}
	}
	move(0,0,cx,cy);
	drawfastest();
	getch();
}

void drawsection(int loopx, int loopy)
{
	if(maze[loopx][loopy]==1) setfillstyle(1,1);
	else if(maze[loopx][loopy]==0)setfillstyle(1,0);
	else if(maze[loopx][loopy]==2)setfillstyle(1,2);
	else if(maze[loopx][loopy]==3)setfillstyle(1,3);
	bar(loopx*size-size,loopy*size-size,loopx*size,loopy*size);
}

void drawcursor()
{
	setfillstyle(1,15);
	bar(cx*size-size,cy*size-size,cx*size,cy*size);

}



void drawmaze()
{
	for(int loopx=1;loopx<maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			drawsection(loopx,loopy);
		}
	}
	drawcursor();

}



void drawfastest()
{
	cx=0;cy=0;
	drawmaze();
	for(int x=1;x<maxx;x++)
	{
		for(int y=1;y<maxy;y++)
		{
			if(fastest[x][y]==1)
			{
				setfillstyle(1,15);
				bar(x*size-size+size*.25,y*size-size+size*.25,x*size-size*.25,y*size-size*.25);
			}
		}
	}
}



int move(int ox, int oy,int x, int y)
{
	int madeit=0;

	if(maze[x][y]==3)
	{
		outtextxy(300,300,"made it");
		getch();

		return 1;
	}

	delay(15);

	drawsection(cx,cy);

	cx=x;
	cy=y;
	drawcursor();

	if(maze[x][y+1]!=1 && y+1!=oy) madeit=move(x,y,x,y+1);
	if(madeit==1)
	{
		fastest[x][y+1]=1;
		return 1;
	}
	if(maze[x][y-1]!=1 && y-1!=oy) madeit=move(x,y,x,y-1);
	if(madeit==1)
	{
		fastest[x][y-1]=1;
		return 1;
	}
	if(maze[x+1][y]!=1 && x+1!=ox) madeit=move(x,y,x+1,y);
	if(madeit==1)
	{
		fastest[x+1][y]=1;
		return 1;
	}

	if(maze[x-1][y]!=1 && x-1!=ox) madeit=move(x,y,x-1,y);
	if(madeit==1)
	{
		fastest[x-1][y]=1;
		return 1;
	}

	return 0;

}


void save()
{
	ofstream outfile;
	outfile.open("maze.sav");
	for(int loopx=1;loopx<maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			outfile << maze[loopx][loopy] << endl;
		}
	}
	outfile.close();
	drawmaze();
}

void load()
{
	ifstream infile;
	infile.open("maze.sav");
	for(int loopx=1;loopx<maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			infile >> maze[loopx][loopy];
		}
	}
	infile.close();
}


void newmaze()
{
	for(int loopx=0;loopx<=maxx;loopx++)
	{
		for(int loopy=0;loopy<maxx;loopy++)
		{
			maze[loopx][loopy]=1;
		}
	}
	cx=1;cy=1;
}


void createmaze()
{
	char choice;
	newmaze();
	drawmaze();
	do
	{

		choice=toupper(getch());
		drawsection(cx,cy);
		switch(choice)
		{
			case('W'):
			{
				maze[cx][cy]=1;
				break;
			}
			case('S'):
			{
				maze[cx][cy]=2;
				break;
			}
			case('F'):
			{
				maze[cx][cy]=3;
				break;
			}
			case(8):
			{
				maze[cx][cy]=0;
				break;
			}
			case('4'):
			{
				cx--;

				if(cx<1) cx=maxx-1;

				break;
			}
			case('6'):
			{
				cx++;
				if(cx>maxx-1) cx=1;
				break;
			}

			case('8'):
			{
				cy--;
				if(cy<1) cy=maxy-1;
				break;
			}
			case('5'):
			{
				cy++;
				if(cy>maxy-1) cy=1;
				break;
			}
			case('V'):
			{
				save();
				drawmaze();
				break;
			}
			case('L'):
			{
				load();
				drawmaze();
				break;
			}
			case('N'):
			{
				newmaze();
				break;
			}


		}

		drawcursor();

	}while(choice!='D');

}








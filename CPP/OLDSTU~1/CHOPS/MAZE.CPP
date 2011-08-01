#include<include.h>


const int maxx=30;
const int maxy=30;
int wall[maxx][maxy];


void find(int x, int y);
void createmaze();
void drawmaze();

void main()
{
	setup();
	createmaze();
}


void drawmaze()
{


void createmaze()
{
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<=maxy;loopy++)
		{
			if(wall[loopx][loopy]==1) setfillstyle(1,1);
			else(setfillstyle(1,0);
			bar(loopx*10
		}
	}

	//clearing maze
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<=maxy;loopy++)
		{
			wall[loopx][loopy]=1;
		}
	}




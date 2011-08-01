#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<ctype.h>
#include<bios.h>

int density;
int tdelay;
int numdudes=0;
const int maxx=30;
const int maxy=15;

int changedraw=0;

struct type_dude
{
	int age;
	int exist;
}dude[81][26];

type_dude bdude[81][26];

void check_n_change();
void createdudes();
void drawdudes();
int checksingle(int x, int y);
void createdude(int x, int y);
void check_n_change();
void setarray();
int countdudes();





void main()
{
	randomize();
	textcolor(7);
	clrscr();
	char quit;
	cout << "How dense (in percent) do ya want these dudes, to start : ";
	cin >> density;

	cout << "Delay (in milliseconds) to watch the dudes change: ";
	cin >> tdelay;
	createdudes();
	clrscr();
	do
	{
		drawdudes();
		check_n_change();
		getch();
		//delay(tdelay);
		setarray();
		numdudes=countdudes();

	}while(numdudes>0);

}


void setarray()
{
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			dude[loopx][loopy].exist=bdude[loopx][loopy].exist;
			dude[loopx][loopy].age=bdude[loopx][loopy].age;
		}
	}

}

int countdudes()
{
	int num=0;
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			if(dude[loopx][loopy].exist==1) num++;
		}
	}
	return num;
}


void createdudes()
{
	randomize();
	int num;
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			num=random(100);
			if(num<density)
			{
				bdude[loopx][loopy].exist=1;
				bdude[loopx][loopy].age=1;
				numdudes++;
				if(changedraw==1)
				{
					gotoxy(loopx,loopy);
					cout << dude[loopx][loopy].age;
				}
			}
			else bdude[loopx][loopy].exist=0;
		}
	}
}

void drawdudes()
{

	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			if(dude[loopx][loopy].exist==1)
			{


				// Method 1: using colors to show age
				textcolor(dude[loopx][loopy].age);
				clreol();
				gotoxy(loopx,loopy);
				cout << "";


				/*
				//Method 2: using numbers to show age
				gotoxy(loopx,loopy);
				cout << dude[loopx][loopy].age;
				*/
			}
			else
			{
				gotoxy(loopx,loopy);
				cout << " ";
			}
		}
	}

}


int checksingle(int x, int y)
{
	int dudes_around=-1;

	for(int loopx=x-1;loopx<=x+1;loopx++)
	{
		for(int loopy=y-1;loopy<=y+1;loopy++)
		{
			if(dude[loopx][loopy].exist==1) dudes_around++;
		}
	}
	if(dudes_around<2) return 0;
	else if(dudes_around<4) return 1;
	else if(dudes_around<6) return 2;
	else return 0;
}

void createdude(int x, int y)
{
	for(int loopx=x-1;loopx<=x+1;loopx++)
	{
		for(int loopy=y-1;loopy<=y+1;loopy++)
		{
			if(dude[loopx][loopy].exist!=1 && bdude[loopx][loopy].exist!=1)
			{
				bdude[loopx][loopy].exist=1;
				bdude[loopx][loopy].age=1;
				if(changedraw==1)
				{

					gotoxy(loopx,loopy);
					cout << dude[loopx][loopy].age;
				}
				//numdudes++;
				return;
			}
		}
	}
}



void check_n_change()
{
	int result;
	for(int loopx=1;loopx<=maxx;loopx++)
	{
		for(int loopy=1;loopy<maxy;loopy++)
		{
			if(dude[loopx][loopy].exist==1)
			{
				result=checksingle(loopx,loopy);
				if(result==0)
				{
					bdude[loopx][loopy].exist=0;
					if(changedraw==1)
					{
						gotoxy(loopx,loopy);
						cout << " ";
					}
					//numdudes--;
				}
				else if(result==1)
				{
					bdude[loopx][loopy].age=dude[loopx][loopy].age+1;;
					if(changedraw==1)
					{
						gotoxy(loopx,loopy);
						cout << dude[loopx][loopy].age;
					}
				}
				else if(result==2)
				{
					bdude[loopx][loopy].age=dude[loopx][loopy].age+1;
					createdude(loopx,loopy);
					if(changedraw==1)
					{
						gotoxy(loopx,loopy);
						cout << dude[loopx][loopy].age;
					}
				}
			}
		}
	}

}

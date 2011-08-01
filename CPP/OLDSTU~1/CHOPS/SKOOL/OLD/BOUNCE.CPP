#include <iostream.h>
#include <dos.h>
#include <conio.h>
//#include <graphics.h>
#include <stdlib.h>
//#include <stdio.h>

void main()
{


	randomize();
	clrscr();
	int i;
	int xcoord;
	int ycoord;
	int xleft;
	int yup;
	int soundon;
	xcoord=1;
	ycoord=1;
	xleft=0;
	yup=0;
	int col;
	while(!kbhit())
	{
		if(xcoord>=55)
		{
			xleft=1;
			goto sstart;

		}
		if(xcoord<=1)
		{
			xleft=0;
			goto sstart;
		}
		if(ycoord>=25)
		{
			yup=1;
			goto sstart;
		}
		if(ycoord<=1)
		{
			yup=0;
			goto sstart;
		}
		goto paststart;

		sstart:
		sound(1000);
		soundon=1;
		col=(random(14))+1;
		textcolor(col);

		paststart:
		gotoxy(xcoord,ycoord);
		cout << "Chops is God";

		clrscr();


		if(xleft==0)
		{
			xcoord++;
		}
		if(xleft==1)
		{
			xcoord=xcoord-1;
		}
		if(yup==0)
		{
			ycoord++;
		}
		if(yup==1)
		{
			ycoord=ycoord-1;
		}

		//gotoxy(xcoord,ycoord);
		//cout << xcoord << endl << ycoord << endl;
		gotoxy(xcoord,ycoord);
		cout << "Chops made this in C++";
		delay(15);
		if(soundon==1)
		{
			nosound();
			soundon=0;
		}
		//delay(10);
	}

	clrscr();
	gotoxy(35,12);
	{
	//textcolor();

	cout << "Coded by Chops"<< endl;
	cout << "Mike Gaynor is my god"<<endl;
	cout << "Mike Gaynor is better than I can ever hope to be";
	sleep(3);
	}

}

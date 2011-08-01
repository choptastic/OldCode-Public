#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <bios.h>
#include <stdlib.h>5




void help()
{
clrscr();
cout
<< "Q=Quit" << endl
<< "H=Help" << endl
<< "A=Move left Paddle Up" << endl
<< "Z=Move left Paddle Down" << endl
<< "8=Move right paddle Up" << endl
<< "5=Move right paddle Down" << endl;
cout << "Press any Key to exit Help";
getch();
clrscr();
return;
}

void main()
{
	clrscr();
	int s_on=1,speed=50,quit=0,s,p2y=12,ballx=11,bally=3,p1y=12,bxdir=1,bydir=1,p2dir=0,p1dir=0, p2score=0,p1score=0;
	char choice;
	gotoxy(30,12);
	cout << "Chops's Pong";
	getch();
	help();
	clrscr();
	do
	{
		do
		{
		// Write scores
		gotoxy(1,1);
		cout << p2score;
		gotoxy(75,1);
		cout << p1score;



		//clear paddle
		gotoxy(10,p2y+0); cout << " ";
		gotoxy(10,p2y+1); cout << " ";
		gotoxy(10,p2y+2); cout << " ";
		gotoxy(10,p2y+3); cout << " ";

		gotoxy(70,p1y+0); cout << " ";
		gotoxy(70,p1y+1); cout << " ";
		gotoxy(70,p1y+2); cout << " ";
		gotoxy(70,p1y+3); cout << " ";
		// Draw 2p paddle
		if(p2y==21 || p2y==1) p2dir=0;
		if(p1y==21 || p1y==1) p1dir=0;
		if(p2dir==1)
		{
			p2y++;
			if(p2y>=21) p2y=20;
		}
		if(p2dir==-1)
		{
			p2y--;
			if(p2y<=1) p2y=2;
		}
		if(p1dir==1)
		{
			p1y++;
			if(p1y>=21) p1y=20;
		}
		if(p1dir==-1)
		{
			p1y--;
			if(p1y<=1) p1y=2;
		}
		gotoxy(10,p2y+0); cout << "л";
		gotoxy(10,p2y+1); cout << "л";
		gotoxy(10,p2y+2); cout << "л";
		gotoxy(10,p2y+3); cout << "л";

		// Draw p1 paddle
		gotoxy(70,p1y+0); cout << "л";
		gotoxy(70,p1y+1); cout << "л";
		gotoxy(70,p1y+2); cout << "л";
		gotoxy(70,p1y+3); cout << "л";

		// Draw Ball
		gotoxy(ballx,bally);
		cout << "лл";
		delay(speed);
		nosound();
		gotoxy(ballx,bally);
		cout << "  ";


		//Changing ball coords
		if(bxdir==1) ballx=ballx+2;
		if(bxdir==0) ballx=ballx-2;
		if(bydir==1) bally++;
		if(bydir==0) bally--;
		if(ballx<=1)
		{
			p1score++;
			speed=50;
			if(s_on==1)
			{
				for(s=1000;s>500;s--)
				{
					sound(s);
					delay(3);
				}
			}
			nosound();

			getch();
			if(p1score==5)
			{
				clrscr();

				do
				{
					gotoxy(30,11);
					cout << "Right Player Wins ";
					if(p2score==0) cout << "With a Shutout";
					gotoxy(30,12);
					cout << "Game over";
					gotoxy(30,13);
					cout << "Play Again? Y/N";
					choice=getch();
					choice=toupper(choice);
					if(choice=='Y') main();
					if(choice=='N') exit(1);
				}
				while(quit!=1);
			}
			ballx=11;
			bally=3;
			bxdir=1;
			bydir=1;
		}
		if(ballx>=79)
		{

			p2score++;
			speed=50;
			if(s_on==1)
			{
				for(s=1000;s>500;s--)
				{
					sound(s);
					delay(3);
				}
			}
			nosound();
			if(p2score==5)
			{
				clrscr();

				do
				{
					gotoxy(30,11);
					cout << "Right Player Wins ";
					if(p1score==0) cout << "With a Shutout";
					gotoxy(30,12);
					cout << "Game over";
					gotoxy(30,13);
					cout << "Play Again? Y/N";
					choice=getch();
					choice=toupper(choice);
					if(choice=='Y') main();
					if(choice=='N') exit(1);
				}
				while(quit!=1);


			}
			getch();
			ballx=11;
			bally=3;
			bxdir=1;
			bydir=1;

		}
		if(ballx==11 && bally>p2y-2 && bally <p2y+5)
		{
			bxdir=1;
			if(bally<=p2y) bydir=0;
			if(bally>=p2y+3) bydir=1;

			if(s_on==1) sound(500);
		}
		if(ballx==69 && bally>p1y-2 && bally <p1y+5)
		{
			bxdir=0;
			if(s_on==1) sound(500);
			if(bally<=p1y)
			{
				bydir=0;
				speed=speed-5;
			}
			if(bally>=p1y+3)
			{
				bydir=1;
				speed=speed-5;
			}
		}
		if(bally<=1)
		{
			bydir=1;
			bally=1;
			if(s_on==1)sound(1000);
		}
		if(bally>=24)
		{
			bydir=0;
			bally=24;
			if(s_on==1) sound(1000);
		}

		}
		while(bioskey(1)==0);
		choice=getch();
		choice=toupper(choice);
		switch(choice)
		{
			case('Q'):
			{
				quit=1;
				break;
			}
			case('8'):
			{
				p1dir=-1;
				break;
			}
			case('5'):
			{
				p1dir=1;
				break;
			}
			case('A'):
			{
				p2dir=-1;
				break;
			}
			case('Z'):
			{
				p2dir=1;
				break;
			}
			case('P'):
			{
				gotoxy(ballx,bally);
				cout << "Paused";
				getch();
				gotoxy(ballx,bally);
				cout << "      ";
			}
			case('H'):
			{
				help();
			}
			case('S'):
			{
				if(!s_on) s_on=1;
				if(s_on) s_on=0;
			}


		}


	}
	while(!quit);
	clrscr();
}
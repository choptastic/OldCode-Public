#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <bios.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>



const int ospeed=15;
const int radius=8;
const int psize=30;
const int obyspeed=8;

int p1calc(int ballx, int bally, int bxdir, int bydir ,int byspeed)
{

	while(ballx>70+radius)
	{
		if(bxdir==1) ballx=ballx+10;
		if(bxdir==0) ballx=ballx-10;
		if(bydir==1) bally=bally+byspeed;
		if(bydir==0) bally=bally-byspeed;

		if(bally<1+radius)
		{
				bydir=1;
				bally=radius;
		}
		if(bally>480-radius)
		{
				bydir=0;
				bally=480-radius;
		}

	}
return bally;
}


int p2calc(int ballx, int bally, int bxdir, int bydir ,int byspeed)
{

	while(ballx<570-radius)
	{
		if(bxdir==1) ballx=ballx+10;
		if(bxdir==0) ballx=ballx-10;
		if(bydir==1) bally=bally+byspeed;
		if(bydir==0) bally=bally-byspeed;

		if(bally<1+radius)
		{
				bydir=1;
				bally=radius;
		}
		if(bally>480-radius)
		{
				bydir=0;
				bally=480-radius;
		}

	}
return bally;
}




void setup()
{
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics mode */
	initgraph(&gdriver, &gmode, "");

	/* read result of initialization */
	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}

}

void help()
{
char choice;
cleardevice();
gotoxy(1,1);
cout
<< "Q=Quit" << endl
<< "H=Help this help screen" << endl
<< "P=Pause" << endl
<< "S=Sound Toggle " << endl << endl
<< "R=Move left Paddle Up" << endl
<< "F=Move left Paddle Down" << endl
<< "V=Stop left paddle" << endl
<< "8=Move right paddle Up" << endl
<< "5=Move right paddle Down" << endl
<< "2=Stop right paddle" << endl;
// cout << endl <<"B=blowjob,insert $5 in A drive"<<endl;
cout << "Press any Key to exit Help or Q to quit";
choice=getch();
choice=toupper(choice);
if(choice=='Q') exit(1);
cleardevice();
return;
}

void main()
{
	setup();
	cleardevice();
	randomize();
	int byspeed=8,autoplay,autoplay2,s_on=1,speed=ospeed,quit=0,s;
	int p2y=200,ballx=100,bally=random(480)+1,p1y=200,bxdir=1,bydir=1;
	int p2dir=0,p1dir=0, p2score=0,p1score=0;
	int oldp1,oldp2,oldballx,oldbally;
	int p2int,p1int;
	char choice;


	gotoxy(30,12);
	cout << "Chops's Pong";
	getch();
	help();


	// 1 player mode
	while(choice!='1' && choice!='2' && choice!= '0')
	{

	cout << endl << endl << "0 or 1 or 2 player : ";
	choice=getch();
	}
	if(choice=='1')
	{
		autoplay=0;
		autoplay2=1;
	}
	if(choice=='2')
	{
		autoplay=0;
		autoplay2=0;
	}
	if(choice=='0')
	{
		autoplay=1;
		autoplay2=1;
	}
	cleardevice();
	// end 1 player mode



	do
	{

		setcolor(2);
		line(1,1,640,1);
		line(1,479,640,479);
		do
		{

		// Write scores
		gotoxy(1,1);
		cout << p2score;
		gotoxy(80,1);
		cout << p1score;






// Draw paddles
		oldp1=p1y;
		oldp2=p2y;

		oldballx=ballx;
		oldbally=bally;



		if(autoplay==1)
		{
			p2int=p2calc(ballx,bally,bxdir,bydir,byspeed);
			if(p2int>p2y+psize-radius) p2dir=1;
			if(p2int<p2y-psize+radius) p2dir=-1;
			if(p2int<=p2y+psize-5 && p2int>=p2y-psize+radius) p2dir=0;
		}
		if(autoplay2==1)
		{

			p1int=p1calc(ballx,bally,bxdir,bydir,byspeed);
			if(p1int>p1y+psize-radius) p1dir=1;
			if(p1int<p1y-psize+radius) p1dir=-1;
			if(p1int<=p1y+psize-radius && p1int>=p1y-psize+radius) p1dir=0;
		}

		if(p2y>475-psize || p2y<psize+5) p2dir=0;
		if(p1y>475-psize || p1y<psize+5) p1dir=0;
		if(p2dir==1)
		{
			p2y=p2y+10;
			if(p2y>475-psize) p2y=475-psize;
		}
		if(p2dir==-1)
		{
			p2y=p2y-10;
			if(p2y<psize+5) p2y=psize+5;
		}
		if(p1dir==1)
		{
			p1y=p1y+10;
			if(p1y>475-psize) p1y=475-psize;
		}
		if(p1dir==-1)
		{
			p1y=p1y-10;
			if(p1y<psize+5) p1y=psize+5;
		}




		//Changing ball coords
		if(bxdir==1) ballx=ballx+10;
		if(bxdir==0) ballx=ballx-10;
		if(bydir==1) bally=bally+byspeed;
		if(bydir==0) bally=bally-byspeed;

		// if the ball passes the paddle
		if(ballx<=10)
		{
			p1score++;
			speed=ospeed;
			if(s_on==1)
			{
				for(s=1000;s>500;s--)
				{
					sound(s);
					delay(3);
				}
			}
			nosound();

			if(p1score==5)
			{
				cleardevice();
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
			getch();
			ballx=100;
			bally=200;
			bxdir=1;
			bydir=1;
			p1y=p2y=200;
			p2dir=p1dir=0;
			byspeed=obyspeed;

		}
		if(ballx>=630)
		{

			p2score++;
			speed=ospeed;
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
				cleardevice();
				do
				{
					gotoxy(30,11);
					cout << "Left Player Wins ";
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
			ballx=100;
			bally=200;
			bxdir=1;
			bydir=1;
			p2y=p1y=200;
			p2dir=p1dir=0;
			byspeed=obyspeed;
		}
		//#######################
		//# If ball Hits paddle #
		//#######################

		if(ballx<=70+radius && ballx>=69 && bally>p1y-(psize+radius) && bally<p1y+(psize+radius))
		{
			ballx=70+radius;

			if(bydir==p1dir) byspeed=byspeed++;
			if(bydir==0 && p1dir==-1) byspeed=byspeed++;
			if(bydir==0 && p1dir==1) byspeed=byspeed-3;
			if(bydir==1 && p1dir==-1) byspeed=byspeed-3;
			//if(p1dir==0) byspeed--;
			//if(p1dir==0) speed--;

			bxdir=1;
			if(s_on==1) sound(500);
			if(bally<=p1y-psize)
			{
				bydir=0;
				speed=speed-5;

			}
			if(bally>=p1y+psize)
			{
				bydir=1;
				speed=speed-5;
			}

		}

		if(ballx>=570-radius && ballx<=571 && bally>p2y-(psize+5) && bally<p2y+(psize+5))
		{
			ballx=570-radius;

			if(bydir==p2dir) byspeed=byspeed++;
			if(bydir==0 && p2dir==-1) byspeed=byspeed++;
			if(bydir==0 && p2dir==1) byspeed=byspeed-3;
			if(bydir==1 && p2dir==-1) byspeed=byspeed-3;

			bxdir=0;
			if(s_on==1) sound(500);
			if(bally<=p2y-psize)
			{
				bydir=0;
				speed=speed-5;
			}
			if(bally>=p2y+psize)
			{
				bydir=1;
				speed=speed-5;
			}

		}

		if(speed<0) speed=0;

		//###################
		// Ball hitting wall#
		//###################
		if(bally<3+radius)
		{
			bydir=1;
			bally=radius+3;
			if(s_on==1)sound(1000);
		}
		if(bally>478-radius)
		{
			bydir=0;
			bally=478-radius;
			if(s_on==1) sound(1000);
		}


		//clear paddle
		if(oldp1!=p1y)
		{
			setfillstyle(1,0);
			bar(50,oldp1-psize,70,oldp1+psize);
		}
		if(oldp2!=p2y)
		{
			setfillstyle(1,0);
			bar(570,oldp2-psize,590,oldp2+psize);
		}
		setcolor(0);
		setfillstyle(1,0);
		fillellipse(oldballx,oldbally,radius,radius);

		//********************************************
		//********************************************

		// draw paddles paddle
		//f2if(oldp1!=p2y)
		//{
			setfillstyle(1,1);
			bar(50,p1y-psize,70,p1y+psize);
		//}
		//if(oldp1!=p2y)
		//{
			setfillstyle(1,2);
			bar(570,p2y-psize,590,p2y+psize);
		//}
		// Draw Ball
		setcolor(5);
		setfillstyle(1,5);
		fillellipse(ballx,bally,radius,radius);

		delay(speed);

		nosound();




		} //end of the while loop

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
				if(autoplay!=1) p2dir=-1;
				break;
			}
			case('5'):
			{
				if(autoplay!=1) p2dir=1;
				break;
			}
			case('2'):
			{
				if(autoplay!=1) p2dir=0;
				break;
			}
			case('F'):
			{
				if(autoplay2!=1)	p1dir=1;
				break;
			}
			case('R'):
			{
				if(autoplay2!=1) p1dir=-1;
				break;
			}
			case('V'):
			{
				if(autoplay2!=1)	p1dir=0;
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
				else s_on=0;
			}


		}


	}
	while(!quit);
	cleardevice();
	closegraph();
	clrscr();
}
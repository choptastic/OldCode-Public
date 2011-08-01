#include <iostream.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <bios.h>


void table()
{
	clrscr();
	cout << "ษอออออออออออออออออออออออออออออออออออออออออป" << endl;
	cout << "บ                Input :                  บ" << endl;
	cout << "ฬอออออออออออออออออออออออออออออออออออออออออน" << endl;
	cout << "บ                Results                  บ" << endl;
	cout << "ฬอออออออออออออออออออหอออออออออออออออออออออน" << endl;
	cout << "บSin :              บCos :                บ" << endl;
	cout << "ฬอออออออออออออออออออฮอออออออออออออออออออออน" << endl;
	cout << "บTan :              บAbs :                บ" << endl;
	cout << "ฬอออออออออออออออออออฮอออออออออออออออออออออน" << endl;
	cout << "บSqRt:              บLog :                บ" << endl;
	cout << "ศอออออออออออออออออออสอออออออออออออออออออออผ" << endl;
}

void osetup()
{
	int t=63;
	gotoxy(t,13);
	cout << "ษออออออออออออออออป" << endl;gotoxy(t,14);
	cout << "บ1=Do calculationบ" << endl;gotoxy(t,15);
	cout << "ฬออออออออออออออออน" << endl;gotoxy(t,16);
	cout << "บ2=Speed up      บ" << endl;gotoxy(t,17);
	cout << "ฬออออออออออออออออน" << endl;gotoxy(t,18);
	cout << "บ3=Slow down     บ" << endl;gotoxy(t,19);
	cout << "ฬออออออออออออออออน" << endl;gotoxy(t,20);
	cout << "บ4=Rand speed:OFFบ" << endl;gotoxy(t,21);
	cout << "ฬอออออออหออออออออน" << endl;gotoxy(t,22);
	cout << "บ5=SoundบQ=Quit  บ" << endl;gotoxy(t,23);
	cout << "ศอออออออสออออออออผ" << endl;gotoxy(t,24);
}
void ctable()
{

	gotoxy(8,6);
	cout << "             ";
	gotoxy(8,8);
	cout << "             ";
	gotoxy(8,10);
	cout << "             ";
	gotoxy(28,6);
	cout << "             ";
	gotoxy(28,8);
	cout << "             ";
	gotoxy(28,10);
	cout << "             ";
}

void bull(int s_on)
{
	int loop;
	for(loop=1;loop<25;loop++)
	{
		if(s_on==1) sound(1000);
		delay(5);
		nosound();
		gotoxy(8,6);
		cout << random(10000);
		delay(5);
		gotoxy(8,8);
		cout << random(10000);
		delay(5);
		gotoxy(8,10);
		cout << random(10000);
		delay(5);
		gotoxy(28,6);
		cout << random(10000);
		delay(5);
		gotoxy(28,8);
		cout << random(10000);
		delay(5);
		gotoxy(28,10);
		cout << random(10000);
	}

	ctable();
	return;
}

void input(int sound)
{
	ctable();
	double num;
	gotoxy(26,2);
	cin >> num;
	bull(sound);
	gotoxy(8,6);
	cout << sin(num);
	gotoxy(8,8);
	cout << tan(num);
	gotoxy(28,6);
	cout << cos(num);
	gotoxy(28,8);
	cout << abs(num);
	while(num>0)
	{
		gotoxy(28,10);
		cout << log(num);
		gotoxy(8,10);
		cout << sqrt(num);
		num=-1;
	}
	return;
}

char waiting(int px, int py, int speed, int xdir,int ydir,int s_status,int r_speed, int s_on)
{

	char choice;
	choice='0';
	do
	{
		gotoxy(px,py);
		cout << "Choose";
		delay(speed);
		gotoxy(px,py);
		cout << "       ";
		if(s_status==1 && speed>5) speed--;
		if(speed<6) speed=6;
		if(s_status==-1 && speed<75) speed++;
		if(speed>75) speed=74;
		if(px==1) xdir=1;
		if(px==70) xdir=0;
		if(py==1) ydir=1;
		if(py==24) ydir=0;
		if(px==44 && py<=12) xdir=1;
		if(px==56 && py>=15) xdir=0;
		if(py==12 && px<=44) ydir=1;
		if(py==12 && px>=56) ydir=0;
		if(px==44 && py<=12 && r_speed==1) speed=random(75);
		if(px==56 && py>=15 && r_speed==1) speed=random(75);
		if(py==12 && px<=44 && r_speed==1) speed=random(75);
		if(py==12 && px>=56 && r_speed==1) speed=random(75);
		if(ydir==1) py++;
		if(ydir==0) py--;
		if(xdir==1) px++;
		if(xdir==0) px--;

	}
	while(bioskey(1)==0);
	choice=getch();
	choice=toupper(choice);
	if(choice=='Q') return choice;
	if(choice=='5')
	{
		if(s_on!=1) s_on=1;
		else s_on=0;
	}

	if(choice=='1')
	{
		choice=0;
		gotoxy(26,2);
		cout << "             ";
		input(s_on);
	}
	if(choice=='2')
	{
		if(s_status==0)
		{
			s_status=1;
			gotoxy(66,16);
			cout << "Stop Speeding";
			gotoxy(66,18);
			cout << "Slow Down    ";
		}
		else
		{
			s_status=0;
			gotoxy(66,16);
			cout << "Speed up     ";
			gotoxy(66,18);
			cout << "Slow Down    ";
		}
	}


	if(choice=='3')
	{
		if(s_status==0)
		{
			s_status=-1;
			gotoxy(66,18);
			cout << "Stop Slowing";
			gotoxy(66,16);
			cout << "Speed up     ";
		}
		else
		{
			s_status=0;
			gotoxy(66,18);
			cout << "Slow Down    ";
			gotoxy(66,16);
			cout << "Speed up     ";
		}
	}
	if(choice=='4')
	{
		if(r_speed==0)
		{
			r_speed=1;
			gotoxy(77,20);
			cout << "ON ";
		}
		else
		{
			r_speed=0;
			gotoxy(77,20);
			cout << "OFF";
		}
	}
	choice='0';
	waiting(px,py,speed,xdir,ydir,s_status,r_speed, s_on);
}


void main()
{
	int speed,px,py,ydir,xdir,s_status,r_speed,s_on;
	char choice;
	table();
	osetup();
	speed=15;
	s_on=1;
	px=8;
	py=23;
	ydir=1;
	xdir=1;
	s_status=0;
	r_speed=0;
	waiting(px,py,speed,xdir,ydir,s_status,r_speed, s_on);

}
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
	cout << "浜様様様様様様様様様様様様様様様様様様様様�" << endl;
	cout << "�                Input :                  �" << endl;
	cout << "麺様様様様様様様様様様様様様様様様様様様様�" << endl;
	cout << "�                Results                  �" << endl;
	cout << "麺様様様様様様様様様僕様様様様様様様様様様�" << endl;
	cout << "�Sin :              �Cos :                �" << endl;
	cout << "麺様様様様様様様様様陵様様様様様様様様様様�" << endl;
	cout << "�Tan :              �Abs :                �" << endl;
	cout << "麺様様様様様様様様様陵様様様様様様様様様様�" << endl;
	cout << "�SqRt:              �Log :                �" << endl;
	cout << "藩様様様様様様様様様瞥様様様様様様様様様様�" << endl;
}

void osetup()
{
	int t=63;
	gotoxy(t,13);
	cout << "浜様様様様様様様融" << endl;gotoxy(t,14);
	cout << "�1=Do calculation�" << endl;gotoxy(t,15);
	cout << "麺様様様様様様様郵" << endl;gotoxy(t,16);
	cout << "�2=Speed up      �" << endl;gotoxy(t,17);
	cout << "麺様様様様様様様郵" << endl;gotoxy(t,18);
	cout << "�3=Slow down     �" << endl;gotoxy(t,19);
	cout << "麺様様様様様様様郵" << endl;gotoxy(t,20);
	cout << "�4=Rand speed:OFF�" << endl;gotoxy(t,21);
	cout << "麺様様様僕様様様郵" << endl;gotoxy(t,22);
	cout << "�5=Sound�Q=Quit  �" << endl;gotoxy(t,23);
	cout << "藩様様様瞥様様様夕" << endl;gotoxy(t,24);
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
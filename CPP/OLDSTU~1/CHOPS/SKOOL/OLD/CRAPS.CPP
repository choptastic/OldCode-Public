//
//Hour 1
#include <include.h>

//**************************************************
//***********************craps**********************
//**************************************************
int winning(int bamount)
{
	randomize();
	int win, point=0, pointnum=0, loop, d1, d2,done=0;
	while(done!=1)
	{
		cout << endl << "Press any key to roll the dice";
		getch();

		for(loop=1;loop<50;loop++)
		{
			gotoxy(40,12);
			cout << random(6)+1 << " " << random(6)+1;
			sound(500);
			delay(3);
			nosound();
			delay(loop);
			clrscr();
		}

		nosound();
		d1=random(6)+1;
		d2=random(6)+1;
		cout << d1 << " " << d2;
		if(pointnum==1)
		{
			if(d1+d2==point)
			{
				cout << endl << "YAY" << endl;
				win=bamount;
				pointnum=0;
				done=1;
				goto finished;
			}
			if(d1+d2==7)
			{
				cout << endl << "Ya Lost" << endl;
				win=0-bamount;
				pointnum=0;
				done=1;
				goto finished;
			}
			if((3<d1+d2<7) || (7<d1+d2<11))
			{
				cout << endl << "The point is " << point << endl;
				pointnum=1;
				done=0;
				goto finished;
			}

		}
		else
		{
			if((d1+d2==7) || (d1+d2==11))
			{
				cout << endl << "YAY" << endl;
				pointnum=0;
				win=bamount;
				done=1;
				goto finished;
			}
			if((d1+d2==2) || (d1+d2==3) || (d1+d2==12))
			{
				cout << endl << "Ya Lost" << endl;
				win=0-bamount;
				pointnum=0;
				done=1;
				goto finished;
			}
			if((3<d1+d2<7) || (7<d1+d2<11))
			{
				point=d1+d2;
				cout << endl << "The point is " << point << endl;
				pointnum=1;
				done=0;
				goto finished;
			}
		}
		finished:


	}
	return win;

}

int craps(int total)
{
	nosound();
	//randomize();
	int bamount=0,loop;
	char choice;
	clrscr();
	while(choice!='N' && total>0)
	{
		cout << endl;
		cout << "Amount you gotzt : " << total << endl;
		swell:
		cout << "Place your bet : ";
		cin >> bamount;
		if(total-bamount<0) goto swell;
		total=total+winning(bamount);
		if(total>0)
		{
			cout << "You have " << total << " bone, continue? Y/N";
			choice=getch();
			choice=toupper(choice);
		}
	}
	cout << endl << "Press any Key to Leave Street Craps";
	getch();
	return total;
}

int blackjack(int total)
{
	cout << "Sorry bro, it ain't done dude";
	getch();
	clrscr();
	return total;
}

int slots(int total)
{
	int p1,p2,p3,bamount,loop;
	char choice;
	/*
	cout << "Sorry bro, it ain't done dude";
	getch();
	clrscr();
	return total;
	*/
	while(choice!='N')
	{
	clrscr();
	cout << endl <<"Amout you gotzt : " << total << endl;
	cout << "Put how much in the machine : ";
	cin >> bamount;
	for(loop=1;loop<50;loop++)
	{

		sound(500);
		p1=random(4);
		p2=random(4);
		p3=random(4);
		gotoxy(30,12);
		cout << p1;
		gotoxy(40,12);
		cout << p2;
		gotoxy(50,12);
		cout << p3;
		nosound();
		delay(loop);


	}
	if(p1==p2==p3)
	{
		cout << endl << "YAY, ya done won a bunch of stuff" << endl;
		total=total+(bamount*10);
	}
	else
	{
		cout << endl << "Ya didn't win";
		total=total-bamount;
	}
	cout << endl << "Play again Y/N" << endl;
	choice=getch();
	choice=toupper(choice);

	}
	return total;
}

int roulette(int total)
{
	cout << "Sorry bro, it ain't done dude";
	getch();
	clrscr();
	return total;
}

void quit(int total)
{
	cout << "okay, so you left the casino with " << total << " Dollars";
	return;
}

void main()
{
	int total=100;
	char choice;
	clrscr();
	cout << "Crappy program gambling game";
	gotoxy(12,12);
	cout << "Press any key to get on da street";
	getch();
	while(choice!='Q')
	{
		clrscr();
		cout << "Dollars : " << total << endl;
		cout << "(C)raps" << endl << "(B)lackjack" << endl << "(R)oulette" << endl << "(S)lots" << endl << "(Q)uit";
		choice=getch();
		choice=toupper(choice);
		switch(choice)
		{
			case('C'):
			{
				clrscr();
				total=craps(total);
				break;
			}
			case('B'):
			{
				clrscr();
				total=blackjack(total);
				break;
			}
			case('Q'):
			{
				clrscr();
				quit(total);
				getch();
				break;
			}
			case('R'):
			{
				clrscr();
				total=roulette(total);
				break;
			}
			case('S'):
			{
				total=slots(total);
				break;
			}
		}
	}
}

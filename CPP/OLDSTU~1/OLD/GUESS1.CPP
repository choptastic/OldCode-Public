#include <include.h>

const guesses=7;
void endprog()
{
	char choice;
	clrscr();
	cout << "Tell ya what, since your loser self was a good sport, i'll let you play pong if you wanna" << endl;
	cout << "Press P to play pong, or anything else to quit";
	choice=getch();
	choice=toupper(choice);
	if(choice=='P') execv("grphpong.exe", 0);
	exit(1);
}


void main()
{
	textcolor(7);
	clrscr();
	randomize();
	int guess, actual=random(100)+1, hrange=100, lrange=1,timeleft=5,gleft=guesses;
	int change;
	char choice;
	while(guess!=actual && gleft!=0)
	{
		cout << endl << "You can aways enter a 0 to give up" << endl;
		cout << "Guesses you gotzt left : " << gleft << endl;
		cout << endl << "Enter a number from " << lrange << " to " << hrange << endl;
		cin >> guess;
		gleft--;
		change=1;
		if(guess>hrange)
		{
			cout << endl << "Poop Stain, that number is bigger than the range, you lose 2 chances for that" << endl;		if(guess<actual)
			change=0;
			gleft--;
		}
		if(guess<lrange)
		{
			if(guess!=0)
			{
				cout << endl << "Retard, that number is lower than the range, you lose 2 chances for that" << endl;
				change=0;
				gleft--;
			}
			else gleft=0;
		}
		if(gleft<0) gleft=0;

		while(change!=0)
		{
		if(guess<actual)
		{
			lrange=guess+1;
			cout << endl <<"Too Low, foomaster" << endl;
		}
		if(guess>actual)
		{
			hrange=guess-1;
			cout << endl << "To High, cheezmasterwong" << endl;
		}
		change=0;
		}

	}
	clrscr();

	if(gleft==0)
	{
		cout << "Your wussie self couldn't even get it in " << guesses << " tries";
		cout << endl << "the number was " << actual << endl;
	}
	else cout << "Yay, ya won!!!  The number was " << actual << endl;


	cout << endl << endl << "Press a key in the next 5 seconds to play again";
	do
	{
		delay(1000);
		timeleft=timeleft-1;
		sound(567);
		delay(5);
		nosound();
		gotoxy(40,12);
		cout << timeleft;
		if(timeleft<=0) endprog();
	}
	while(bioskey(1)==0);

	main();
}


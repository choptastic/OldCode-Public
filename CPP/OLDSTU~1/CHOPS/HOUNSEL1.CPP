#include <iostream.h>
#include <conio.h>
#include  <STDLIB.H>


void main()
{
	randomize();
	clrscr();
	gotoxy(25,12);
	cout << "Biff's Cool Ass Number Game" << endl;
	getch();
	int num,loop=7;
	int high=100,low=1;
	int guess;
	num=random(99)+1;
	while(guess!=num && loop>0)
	{
		clrscr();
		cout << loop << " guesses left" << endl;
		cout << "Break Yoself, gimme yo Goddam numba from " << low << " to " << high << endl;
		cin >> guess;
		if(guess!=num)
		{
			if(guess<num) low=guess;
			if(guess>num) high=guess;
			loop--;
		}
	}
	if(loop>0) cout << "You win shiney new gold toof!" << endl;
	else cout << "You lose, I get your pager, gold chain, and your fake Rolex" << endl;
	getch();

}
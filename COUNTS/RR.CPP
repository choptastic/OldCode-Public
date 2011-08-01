#include<iostream.h>
#include <conio.h>

int numof(int i, int[], int length);


void main()
{
	int players[100];
	memset(players,0,200);
	int numplayers,numrr,max,lastmax;
	clrscr();
	cout << "How many players: ";
	cin >> numplayers;
	cout << "How mabny different Round Robins";
	cin >> numrr;
	max=numplayers/numrr+1;
	cout << endl;
	for(int loop=0;loop<numplayers;loop++)
	{
		while(numof(players[loop],players,numplayers)<max)
			players[loop]=random(numrr)+1;
	}
	for(int loop=0;loop<numrr;loop++)
	{
		cout << "Group " << loop << ": ";
		for(int loop1=0;loop1<numplayers;loop1++)
			if(players[loop1]==loop)
				cout << loop1 << ", ";
		cout << endl << endl;
	}
	getch();

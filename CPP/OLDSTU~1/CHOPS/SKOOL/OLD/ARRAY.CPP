#include <include.h>

int stuff[12];
const int clearall=1;
const int changeall=3;
const int displayall=4;
const int displayone=5;
const int changeone=2;
const int dvalue=2;

void action(int type)
{
	int loop;
	switch(type)
	{
		case(clearall):
		{
			for(loop=0; loop<12;loop++) stuff[loop]=0;
			cout << endl << "You got no more Drugs on Inventory" << endl;
			break;
		}
		case(changeall):
		{
			for(loop=0;loop<12;loop++)
			{
				cout << endl << "How many Kilos in bag #" << loop +1 << " : ";
				cin >> stuff[loop];
			}
			cout << endl << "AHHHH Drugs" << endl;
			break;
		}
		case(displayall):
		{
			int sum=0;
			for(loop=0;loop<12;loop++)
			{
				cout << endl << loop +1 << " : " << stuff[loop];
				sum=stuff[loop]+sum;
			}
			cout << endl << "You gotzt " << sum << " Kilos of Crack" << endl;
			break;
		}
		case(displayone):
		{
			cout << endl << "Which bag of Crack you wanna see value for Kilos : ";
			cin >> loop;
			cout << endl << loop << " : " << stuff[loop-1];
			break;
		}
		case(changeone):
		{
			cout << endl << "Change Kilos in bag : ";
			cin >> loop;
			cout << endl << "How Many Kilos : ";
			cin >> stuff[loop-1];
			break;
		}
	}

}

void main()
{
	char choice;
	clrscr();
	do{
		cout << endl << "The Drug Inventory Program";
		cout << endl << "1=Clear Inventory"
		<< endl << "2=Change All Values of Crack"
		<< endl << "3=Display All Values of all Bags of Crack"
		<< endl << "4=Display One Value of Crack"
		<< endl << "5=Change One Value of Crack"
		<< endl << "6=Quit the Crack inventory Program" << endl;
		choice=getch();
		choice=toupper(choice);
		switch(choice)
		{
			case('1'):
			{
				action(clearall);
				break;
			}
			case('2'):
			{
				action(changeall);
				break;
			}
			case('3'):
			{
				action(displayall);
				break;
			}
			case('4'):
			{
				action(displayone);
				break;
			}
			case('5'):
			{
				action(changeone);
				break;
			}
		}
	}
	while(choice!='6');
	cout << endl << "Next Shipment October 12, at Dock 12";
	delay(2000);
}



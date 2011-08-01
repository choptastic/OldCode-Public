#include <include.h>

unsigned int fact(int num)
{
	unsigned int num2=1,swell=1;
	for(swell=1;swell<=num;swell++)
	{
		num2=num2*swell;
	}
	return num2;
}

unsigned int count(unsigned int num, unsigned int num2)
{
	int swell=1,result=0;
	for(swell=num;swell<=num2;swell++)
	{
		result=result+swell;
	}
	return result;
}


void main()
{
	char choice;
	unsigned int num,num2;
	cout << "Program" << endl;
	while(choice!='Q')
	{
		cout << "(Q)uit--(C)ount--(F)actorial" << endl;
		choice=getch();
		choice=toupper(choice);
		switch(choice)
		{
			case('F'):
			{
				cout << "Number to factorial" << endl;
				cin >> num;
				cout << endl << fact(num);
				break;
			}
			case('C'):
			{
				cout << "Starting number" << endl;
				cin >> num;
				cout << "Ending Number" << endl;
				cin >> num2;
				cout << endl << count(num,num2);
				break;
			}
		}
		cout << endl;
	}
}
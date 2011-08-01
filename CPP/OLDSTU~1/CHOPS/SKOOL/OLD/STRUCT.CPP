#include <include.h>

const char d='*';
int title()
{
	int osel;
	clrscr();
	char choice;
	int selected=1;
	gotoxy(1,1);
	cout << "Press <Space> to select";
	gotoxy(29,5);
	cout << "  Change Age";
	gotoxy(29,7);
	cout << "  Change Hours";
	gotoxy(29,9);
	cout << "  Change Wage";
	gotoxy(29,11);
	cout << "  Change All";
	gotoxy(29,13);
	cout << "  View Stats";
	gotoxy(29,15);
	cout << "  Clear All";
	gotoxy (29,17);
	cout << "  Quit";
	while(choice!=' ')
	{
	if(osel==1)
	{
		gotoxy(29,5);
		cout << "  ";
	}
	else if(osel==2)
	{
		gotoxy(29,7);
		cout << "  ";
	}
	else if(osel==3)
	{
		gotoxy(29,9);
		cout << "  ";
	}
	else if(osel==4)
	{
		gotoxy(29,11);
		cout << "  ";
	}
	else if(osel==5)
	{
		gotoxy(29,13);
		cout << "  ";
	}
	else if(osel==6)
	{
		gotoxy(29,15);
		cout << "  ";
	}
	else if(osel==7)
	{
		gotoxy (29,17);
		cout << "  ";
	}

	if(selected==1)
	{
		gotoxy(29,5);
		cout << d;
	}
	else if(selected==2)
	{
		gotoxy(29,7);
		cout << d;
	}
	else if(selected==3)
	{
		gotoxy(29,9);
		cout << d;
	}
	else if(selected==4)
	{
		gotoxy(29,11);
		cout << d;
	}
	else if(selected==5)
	{
		gotoxy(29,13);
		cout << d;
	}
	else if(selected==6)
	{
		gotoxy(29,15);
		cout << d;
	}
	else if(selected==7)
	{
		gotoxy(29,17);
		cout << d;
	}
	gotoxy(80,25);
	choice=toupper(getch());


	osel=selected;
	switch(choice)
	{
		case('H'):
		{
			selected--;
			break;
		}
		case('P'):
		{
			selected++;
			break;
		}

	}
	if(selected==8) selected=1;
	if(selected==0) selected=7;
	}
	return selected;

}

void main()
{
	textcolor(7);
	clrscr();
	//setup();
	int choice;
	int num;
	//int selected=1;
	char move;
	struct type
	{
		int age;
		float hrs;
		float wage;
	}
	worker[100];
	/*for(num=0;num<101;num++)
	{
		worker[num].age=0;
		worker[num].wage=0;
		worker[num].hrs=0;
	} */

	while(choice!=7)
	{
		choice=title();
		clrscr();
		switch(choice)
		{
			case(1):
			{
				cout << "Change age for which worker? : ";
				cin >> num;
				cout << endl << "Change to what? : ";
				cin >> worker[num].age;
				break;
			}
			case(2):
			{
				cout << "Change hours worked for which member? : ";
				cin >> num;
				cout << endl << "Change to what? : ";
				cin >> worker[num].hrs;
				break;
			}
			case(3):
			{
				cout << "Change wage for which employee? : ";
				cin >> num;
				cout << endl << "Change to what? : ";
				cin >> worker[num].wage;

				break;
			}
			case(4):
			{
				cout << "Change for which worker? : ";
				cin >> num;
				cout << endl << "Change Age to what? : ";
				cin >> worker[num].age;
				cout << endl << "Change Hours to what? : ";
				cin >> worker[num].hrs;
				cout << endl << "Change Wage to what? : ";
				cin >> worker[num].wage;
				break;
			}
			case(5):
			{
			cout << "View stats for which employee? : ";
				cin >> num;
				cout << endl <<
					"Age : " << worker[num].age << endl <<
					"Hours : " << worker[num].hrs << endl <<
					"Wage : " << worker[num].wage << endl <<
					"Pay so far : " << worker[num].hrs*worker[num].wage << endl;
				break;
			}
			case(6):
			{
				for(num=0;num<11;num++)
				{
					worker[num].age=0;
					worker[num].wage=0;
					worker[num].hrs=0;
				}
				break;
			}
		}
		if(choice!=7)
		{
			cout << endl << "Press a key to continue";
			getch();
		}



	}


}

#include<stack.h>
#include<h:\include.h>


const int maxsize=10;
int stack[maxsize];




void add()
{
	int input;
	cout << "Number : ";
	cin >> input;


}

void rem()
{

}


void main()
{
	clrscr():
	char choice;
	do
	{
		cout << endl << "1=add";
		cout << endl << "2=rem";
		cout << endl << "3=quit";
		choice=toupper(getch());
		if(choice=='1') add();
		else if(choice=='2') rem();
	}while(choice!='3');
}
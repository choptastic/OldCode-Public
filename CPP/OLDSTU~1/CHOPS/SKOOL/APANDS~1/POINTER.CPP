#include<h:\include.h>
const int size=10;

struct node
{
	int data;
	node *next;
};

node *loc1,*loc2,*top;
int amt=0;




void q_rem()
{
	loc2=top;
	loc1=top;
	//while(loc2->next!=0)
	do
	{
		loc1=loc2;
		loc2=loc2->next;

	}while(loc2->next!=0);
	delete loc2;
	loc1->next=0;
	amt--;

}

void q_add()
{
	int in;
	cout << "add: ";
	cin >> in;
	cout << endl << endl;
	if(amt>0)loc2=top;
	amt++;
	top=new node;
	top->next=loc2;
	top->data=in;
	if(amt==1)top->next=0;
}


void display()
{
	loc2=top;
	do
	{
		cout << loc2->data << endl;
		loc2=loc2->next;

	}while(loc2->next!=0);
	cout << endl;
}

void menu()
{
	/*
	cout << "1=Push" << endl;
	cout << "2=pop" << endl;
	*/
	cout << "3=add que" << endl;
	cout << "4=rem que" << endl;
	cout << "5=display" << endl;
	cout << "6=quit" << endl;
}

void main()
{

	char choice=0;
	clrscr();
	do
	{
		menu();
		choice=toupper(getch());
		/*
		if(choice=='1') push();
		else if(choice=='2') pop();

		else*/ if(choice=='3') q_add();
		else if(choice=='4') q_rem();
		else if(choice=='5') display();
		cout << endl << endl;
	}while(choice!='6');

}


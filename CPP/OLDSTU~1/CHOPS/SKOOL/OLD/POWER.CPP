#include <iostream.h>
#include <conio.h>
#include <ctype.h>




float power(double num,double p_num)
{
	double num2;
	num2=num;
	int num3;
	for(num3=1;num3!=p_num;num3++)
	{
		num=num2*num;
	}
	return num;
}

void main()
{
	clrscr();
	double num;
	double p_num;
	char choice;
	while(choice!='0')
	{
		cout << endl << "Number you want to find the Power of : ";
		cin >> num;
		cout << endl << "Power to take it to : ";
		cin >> p_num;
		num = power(num,p_num);
		cout << num << endl << endl << "Do another (Y/N)" << endl;
		choice=getch();
		choice=toupper(choice);
		if(choice=='N') choice='0';
	}

}


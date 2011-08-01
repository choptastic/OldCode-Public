#include <include.h>


void main()
{
	int num=0,num2=0,input;

	while(input!=0)
	{
		cout << "Enter a number" << endl;
		cin >> input;
		num=input+num;
		if(input!=0)num2++;
	}
	cout << "Sum : " << num << endl << "Average of the " << num2 << " numbers : " << num/num2 << endl;
	getch();
}

#include<conio.h>
#include<iostream.h>


int log2(unsigned long v);

void main()
{
	unsigned long v;
	do
	{
		cout << "Enter Value: ";
		cin >> v;
		cout << "Log2: " << log2(v) << endl;
	}while(v!=0);
}

int log2(unsigned long v)
{
	int count=0;
	while(v>>=1)
	{
		count++;
	}
	return count;
}
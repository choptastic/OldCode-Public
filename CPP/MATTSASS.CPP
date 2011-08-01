#include <iostream.h>
#include <conio.h>
#include <stdlib.h>

void main()
{
	int a=random(100)+1;
	int b;
	cin>> a;
	 if (b<a)
	 cout<<"higher";
	 cin>> b;
	 while (b>a)
	 cout<< "lower";
	 while (b==a)
	 cout<< "correct";
}
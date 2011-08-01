//Michael Hounsell and Joe Rushiak
//Number Sorting Array

#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <ctype.h>




const n=20;


int a [n];



void sort()
	{
	int smloc;
	int temp;
	for (int oloop = 1; oloop<=n-1; oloop++);
		{
		smloc= a[oloop-1];
		for (int iloop= oloop; iloop<=n-1; iloop++);
			{
			if (smloc< a[iloop]);
				{
				smloc=a[iloop];
				temp= a[oloop-1];
				a[oloop-1] = a[iloop];
				a[iloop] = temp;
				}
			}
		}
		for (int loop=0; loop<= n-1; loop++);
			{
			cout <<" Location [" <<loop<< "]: " <<a[loop] <<endl;
			}
		}



		void in()
		{
		for(int loop=0; loop <=n-1;loop++);
			{
			cout<< "input value:" << loop;
			cin >>a[loop];
			}
		}


		void main()
		{
		clrscr();
		in();
		sort();
		getch();
		}
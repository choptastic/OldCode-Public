// Jesse Gumm
// Hr. 2
// Binary Search

#include <h:\include.h>
const int size=10;
int array[size];

void load()
{
int loop;
	int input;
	ifstream file;
	file.open("f:\\users\students\\computer\\cpp\\bsearch.txt");
	for(loop=0;loop<size+1;loop++)
	{
		file >> input;
		array[loop]=input;
		if(file.eof()) break;
	}
	file.close();
	cout << endl <<"Values Loaded" << endl;
}

void sort()
{
int loop,looop;
	int temp;
	for(looop=size-1;looop>0;looop--)
	{
		for(loop=size-1;loop>size-looop-1;loop--)
		{
			if(array[loop]<array[loop-1])
			{
				temp = array[loop];
				array[loop]=array[loop-1];
				array[loop-1]=temp;

			}
		}
	}

	cout << "Values Sorted";

}

void search()
{
	int hi=size, lo=0, pos=size/2, input;
	cout << "Enter Value : ";
	cin >> input;
	do
	{
		if(array[pos]<input)
		{
			lo=pos;
			pos=((hi-lo)/2)+lo;
		}
		else if(array[pos]>input)
		{
			hi=pos;
			pos=((hi-lo)/2)+lo;
		}

	}while(input!=array[pos] && (hi-lo)>0);
	if(array[pos]==input) cout << endl << input << " is the " << pos+1 << " Number in the array";
	else cout << "No Match...Between references " << hi << " and " << lo << endl;

}

void display()
{
	for(int loop=0;loop<size;loop++)
	{
		cout << array[loop] << endl;
	}

}


void main()
{
	char choice;
	clrscr();
	do
	{
		cout << endl << "1=Load and sort" << endl << "2=Search" << endl << "3=Display" << endl << "4=quit" << endl;
		choice=getch();
		switch(choice)
		{
			case('1'):
			{
				load();
				sort();
				break;
			}
			case('2'):
			{
				search();
				break;
			}
			case('3'):
			{
				display();
				break;
			}
		}
	}while(choice!='4');
}




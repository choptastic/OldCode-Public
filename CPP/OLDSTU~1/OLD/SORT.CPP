// Jesse Gumm
// Hr. 2
// Load/Display/Sort


#include <h:\include.h>
#include <button.h>

const int size=10;
int array[size];

void load()
{
	int loop;
	int input;
	ifstream file;
	file.open("h:\\num.txt");
	for(loop=0;loop<size+1;loop++)
	{
		file >> input;
		array[loop]=input;
	}
	file.close();
	gotoxy(1,1);
	cout << "Values Loaded";
}

void display()
{
	gotoxy(1,1);
	for(int loop=0;loop<size;loop++)
	{
		cout << array[loop] << endl;
	}



}

void sort()
{
	/*

	//**************First Loop Type**********************
	//This is the old way

	int loop, ovalue, hi, lo, loop1, temp;
	for(loop=0;loop<size;loop++)
	{
		for(loop1=0+loop;loop1<size;loop1++)
		{
			if(array[loop]>array[loop1])
			{
				temp=array[loop1];
				array[loop1]=array[loop];
				array[loop]=temp;


			}

		}
	}
	//********************* End First Loop Type***************
	*/

	//********************* Second Loop Type *****************
	// Note: It's a little different but it werks
	// This puts the lowest number in the front of the array first
	// as opposed to your way by putting the highest at end of array first
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
	//**************** End Second Loop Type *********************

	gotoxy(1,1);
	cout << "Values Sorted";

}


void main()
{
setup();
createbutton(0,500,50,630,100,4,"Load file");
createbutton(1,500,101,630,150,4,"Sort Array");
createbutton(2,500,151,630,200,4,"Display Array");
createbutton(3,500,201,630,250,4,"Quit");
showmouse();
int status=(-1);

do
{
	status=checkbuttons();
	mousemove();
	switch(status)
	{
		case(0):
		{
			cleardevice();
			drawbuttons();
			load();
			break;
		}
		case(1):
		{
			cleardevice();
			drawbuttons();
			sort();
			break;
		}
		case(2):
		{
			cleardevice();
			drawbuttons();
			display();
			break;
		}
	}
}
while(status!=3);



}
#include <include.h>
int thiscolor;

void fillit(int x,int y)
{
	if(x>1 && x<640 && y>1 && y<480)
	{

		putpixel(x,y,1);
		if(getpixel(x-1,y)==thiscolor) fillit(x-1,y);
		if(getpixel(x+1,y)==thiscolor) fillit(x+1,y);
		if(getpixel(x,y-1)==thiscolor) fillit(x,y-1);
		if(getpixel(x,y+1)==thiscolor) fillit(x,y+1);

	}
	else return;
}

void main()
{
	setup();
	setcolor(1);
	rectangle(180,190,220,210);
	getch();
	thiscolor=getpixel(200,200);
	fillit(200,200);
	getch();
}
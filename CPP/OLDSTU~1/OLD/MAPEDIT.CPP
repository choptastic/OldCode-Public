#include<c:\tc\bin\chops\include.h>
#include<c:\warchops\image.h>

const int size=15;
const int ysize=31;
const int xsize=33;


void main()
{
	setup();
	//getch();
	setcolor(15);
	rectangle(140,10,140+(size*xsize),10+(size*ysize));
	new_image hall1;
	new_image hall2;
	new_image mine;
	new_image peon1;
	new_image peon2;
	new_image warr1;
	new_image warr2;
	new_image wizard1;
	new_image wizard2;
	new_image grass1;
	new_image grass2;

	mine.load("c:\\warchops\\mine.wcp");
	hall2.load("c:\\warchops\\hall2.wcp");
	hall1.load("c:\\warchops\\hall1.wcp");
	peon1.load("c:\\warchops\\peon1.wcp");
	peon2.load("c:\\warchops\\peon2.wcp");
	warr1.load("c:\\warchops\\warr1.wcp");
	warr2.load("c:\\warchops\\warr2.wcp");
	wizard1.load("c:\\warchops\\wizard1.wcp");
	wizard2.load("c:\\warchops\\wizard2.wcp");
	//grass1.load("c:\\warchops\\grass1.wcp");
	//grass2.load("c:\\warchops\\grass2.wcp");


	hall1.draw(10,10);
	hall2.draw(25,10);
	peon1.draw(10,25);
	peon2.draw(25,25);
	warr1.draw(10,40);
	warr2.draw(25,40);
	wizard1.draw(10,55);
	wizard2.draw(25,55);
	mine.draw(10,70);
	//grass1.draw(10,85);
	//grass2.draw(25,85);

	getch();
}
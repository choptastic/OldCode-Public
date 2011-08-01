
#include<h:\include.h>
#include<h:\button.h>

//#include<include.h>
//#include<c:\tc\bin\button1.h>

void main()
{
	int status=-1;
	int quit=0;
	setup();
	cleardevice();
	createwindows(0,200,100,550,400,0,4,"Hi, I am Asian");
	createbutton(0,0,350,200,455,300,7,"Change Race");
	createbutton(0,1,350,301,450,350,7,"Do Nothing");

	createlist(0,0,400,150);
	additem(0,0,"option 1");
	additem(0,0,"option 2");
	additem(0,0,"you are gay");
	additem(0,0,"man you are dumb");
	drawlist(0,0);

	/*
	getch();
	windows[0].list[0].status=0;
	drawlist(0,0);
	*/

	/*
	gotoxy(1,1);
	for(int loop=0;loop<maxlist;loop++)
	{
		cout << endl << windows[0].list[0].item[loop];
	}
	*/
	createlabel(0,0,250,125,350,175,13);
	changelabel(0,0,"Window");
	showmouse();
	do
	{
		mousemove();
		status=checkbuttons();
		if(selectedwindow()==0 && status==0)
		{
			deletewindows(1);
			createwindows(1,50,200,300,460,1,2,"Change to What");
			createbutton(1,1,75,350,150,400,3, "Quit");
			createbutton(1,2,151,350,225,400,3,"Blah");
			createbutton(1,0,75,300,255,349,4,"Back");
			createtext(1,0,100,410,250,450);
			changelabel(0,0,"This is bunk");

		}
		else if(selectedwindow()==0 && status==1)
		{
			disablebutton(0,1);
		}
		else if(selectedwindow()==1 && status==1)
		{
			quit=1;
		}
		else if(selectedwindow()==1 && status==2)
		{
			changewindows(0);
			enablebutton(0,1);
			drawwindows(0);
		}
		else if(selectedwindow()==1 && status==0)
		{
			createwindows(2,185,200,500,450,5,6,"Oh so sorry");
			createbutton(2,0,250,250,450,350,6,"Me ruv you wong time");
		}
		else if(selectedwindow()==2 && status==0)
		{
			deletebutton(2,0);
			createwindows(2,185,200,500,450,5,6,"doobeedoobeedoo");
		}

	}while(quit!=1);
}


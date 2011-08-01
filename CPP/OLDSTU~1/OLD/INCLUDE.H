#include<BIOS.H>
#include<CONIO.H>
#include<CTYPE.H>
#include<DOS.H>
#include<GRAPHICS.H>
#include<IOSTREAM.H>
#include<PROCESS.H>
#include<STDIO.H>
#include<STDLIB.H>
#include<fstream.h>
#include<mouse.h>


void setup()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
}


int title(int graph,int num,char *sel, char *menuname, char *msg1,char *msg2, char *msg3, char *msg4, char *msg5,char *msg6,char *msg7)
{
	int osel;
	char choice;
	int selected=1;
	if(graph==0)
	{
		clrscr();
		gotoxy(30,23);
		cout << menuname;
		gotoxy(30,24);
		cout << "Chops's Menu Thingy version b.l.a.h";
		gotoxy(1,1);
		cout << "Press <Space> to select";
		gotoxy(29,5);
		cout << "  " << msg1;
		gotoxy(29,7);
		cout << "  " << msg2;
		gotoxy(29,9);
		cout << "  " << msg3;
		gotoxy(29,11);
		cout << "  " << msg4;
		gotoxy(29,13);
		cout << "  " << msg5;
		gotoxy(29,15);
		cout << "  " << msg6;
		gotoxy (29,17);
		cout << "  " << msg7;
	}
	else
	{
		cleardevice();
		setcolor(1);
		outtextxy(1,1,"Press <Space> to select");
		setcolor(15);
		outtextxy(350,100,msg1);
		outtextxy(350,125,msg2);
		outtextxy(350,150,msg3);
		outtextxy(350,175,msg4);
		outtextxy(350,200,msg5);
		outtextxy(350,225,msg6);
		outtextxy(350,250,msg7);
		outtextxy(350,430,menuname);
		outtextxy(350,470,"Chops's Menu version b.l.a.h");
	}

	while(choice!=' ')
	{
	if(graph==0)
	{
		if(osel==1)
		{
			gotoxy(29,5);
			cout << "  ";
		}
		else if(osel==2)
		{
			gotoxy(29,7);
			cout << "  ";
		}
		else if	(osel==3)
		{
			gotoxy(29,9);
			cout << "  ";
		}
		else if(osel==4)
		{
			gotoxy(29,11);
			cout << "  ";
		}
		else if(osel==5)
		{
			gotoxy(29,13);
			cout << "  ";
		}
		else if(osel==6)
		{
			gotoxy(29,15);
			cout << "  ";
		}
		else if(osel==7)
		{
			gotoxy (29,17);
			cout << "  ";
		}

		if(selected==1)
		{
			gotoxy(29,5);
			cout << sel;
		}
		else if(selected==2)
		{
			gotoxy(29,7);
			cout << sel;
		}
		else if(selected==3)
		{
			gotoxy(29,9);
			cout << sel;
		}
		else if(selected==4)
		{
			gotoxy(29,11);
			cout << sel;
		}
		else if(selected==5)
		{
			gotoxy(29,13);
			cout << sel;
		}
		else if(selected==6)
		{
			gotoxy(29,15);
			cout << sel;
		}
		else if(selected==7)
		{
			gotoxy(29,17);
			cout << sel;
		}
		gotoxy(80,25);
	}
	else
	{
		setcolor(0);
		if(osel==1) outtextxy(305,100,sel);
		else if(osel==2) outtextxy(305,125,sel);
		else if(osel==3) outtextxy(305,150,sel);
		else if(osel==4) outtextxy(305,175,sel);
		else if(osel==5) outtextxy(305,200,sel);
		else if(osel==6) outtextxy(305,225,sel);
		else if(osel==7) outtextxy(305,250,sel);

		setcolor(15);
		if(selected==1) outtextxy(305,100,sel);
		else if(selected==2) outtextxy(305,125,sel);
		else if(selected==3) outtextxy(305,150,sel);
		else if(selected==4) outtextxy(305,175,sel);
		else if(selected==5) outtextxy(305,200,sel);
		else if(selected==6) outtextxy(305,225,sel);
		else if(selected==7) outtextxy(305,250,sel);
	}
	choice=toupper(getch());


	osel=selected;
	switch(choice)
	{
		case('H'):
		{
			selected--;
			break;
		}
		case('P'):
		{
			selected++;
			break;
		}

	}
	if(selected==num+1) selected=1;
	if(selected==0) selected=num;
	}
	return selected;
}

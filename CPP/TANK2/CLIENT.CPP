#include<h:\include\include.h>
#include<dir.h>
#include<h:\tank2\image.h>
const unsigned char north=0;
const unsigned char south=1;
const unsigned char west=2;
const unsigned char east=3;
const unsigned char alive=1;
const unsigned char dead=0;
const unsigned char res=5;
const unsigned int stop=6;
const unsigned int quit=7;
const unsigned int join=8;

const int fire=4;
const int maxbullets=20;
int player;
char *game;
int page;
int message[10];
int command[7];

small_image bulletp;
small_image tank;
small_image explode;

class unit_t
{
	public:
	int x,y,dir;
	int status;
	char *name;
	int exist;
	int kills;
}unit[7];


class bullet_t
{
	public:
	int x,y,dir;
	int exist;
}bullet[maxbullets];

void loadpics();
void getinfo();
void putinfo(int command);
void drawscreen();
void namestuff();
void textxy(int x, int y, int num);

void setup1()
{
   int gdriver = EGA, gmode = EGAHI, errorcode;
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

void main()
{
	setup1();
	cleardevice();
	namestuff();
	loadpics();
	cleardevice();
	char choice;
	int command=join;
	do
	{
		do
		{
			getinfo();
			putinfo(command);
			if(command==fire) command=unit[player].dir;
			else if(command==join) command=stop;
			drawscreen();
			delay(50);

		}while(bioskey(1)==0);
		choice=toupper(getch());
		switch(choice)
		{
			case('8'):
			{
				command=north;
				break;
			}
			case('6'):
			{
				command=east;
				break;
			}
			case('5'):
			{
				command=south;
				break;
			}
			case('4'):
			{
				command=west;
				break;
			}
			case('F'):
			{
				command=fire;
				break;
			}
			case('R'):
			{
				if(unit[player].status==dead) command=res;
				break;
			}


		}
	}while(choice!='Q');
	command=quit;
	putinfo(command);
}


void namestuff()
{
	cout << "Enter player number" << endl;
	cin >> player;
	cout << "Enter Player " << player << " name :";
	cin.ignore(maxbullets,'\n');
	cin.get(unit[player].name,40);
}


void drawscreen()
{
	if(page==0) page=1;
	else page=0;
	setactivepage(page);

	cleardevice();
	for(int loop=0;loop<7;loop++)
	{
		if(unit[loop].exist==1 && unit[loop].status==alive) tank.draw(unit[loop].x,unit[loop].y,unit[loop].dir,loop+1);
		else if(unit[loop].exist==1 && unit[loop].status==dead) explode.draw(unit[loop].x,unit[loop].y,0,0);
		setcolor(loop+1);
		if(unit[loop].exist==1) textxy(loop*100,340,unit[loop].kills);
	}
	for(loop=0;loop<maxbullets;loop++)
	{
		if(bullet[loop].exist==1) bulletp.draw(bullet[loop].x,bullet[loop].y,bullet[loop].dir,0);
	}
	setvisualpage(page);
}

void loadpics()
{
	bulletp.load("h:\\tank2\\bullet.pic");
	tank.load("h:\\tank2\\tank.pic");
	explode.load("h:\\tank2\\explode.pic");
}


void getinfo()
{
	ifstream file;
	file.open("h:\\host");
	for(int loop=0;loop<7;loop++)
	{
		file >> unit[loop].x;
		file >> unit[loop].y;
		file >> unit[loop].dir;
		file >> unit[loop].status;
		file >> unit[loop].exist;
		file >> unit[loop].kills;
	}
	for(loop=0;loop<maxbullets;loop++)
	{
		file >> bullet[loop].x;
		file >> bullet[loop].y;
		file >> bullet[loop].dir;
		file >> bullet[loop].exist;
	}
	file.close();

}

void putinfo(int command)
{
	ofstream file;
	if(player==0) file.open("h:\\player0");
	else if(player==1) file.open("h:\\player1");
	else if(player==2) file.open("h:\\player2");
	else if(player==3) file.open("h:\\player3");
	else if(player==4) file.open("h:\\player4");
	else if(player==5) file.open("h:\\player5");
	else if(player==6) file.open("h:\\player6");

	if(unit[player].status==dead && command!=res) command=stop;
	file << command;
	//else file << stop;
	file.close();
}

void textxy(int x, int y, int num)
{
	char string[20];
	ltoa(num,string,10);
	outtextxy(x,y,string);

}




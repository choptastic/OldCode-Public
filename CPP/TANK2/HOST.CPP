#include<h:\include\include.h>
#include<dir.h>
#include<h:\tank2\image.h>

const unsigned char north=0;
const unsigned char south=1;
const unsigned char west=2;
const unsigned char east=3;
const unsigned char alive=1;
const unsigned char dead=0;
const int fire=4;
const int maxbullets=20;
const unsigned int res=5;
const unsigned int stop=6;
const unsigned int quit=7;
const unsigned int join=8;

char *game;
int page;
int message[10];
int command[10];
int numbullets;
int maxx=640;
int maxy=350;


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
	int x,y,dir,owner;
	int exist;
}bullet[maxbullets];

void getinfo();
void putinfo();
void start();
void calculate();
void display();
void makeunit(int index);


void main()
{
	start();
	gotoxy(1,1);
	numbullets=0;
	gotoxy(1,1);
	cout << "Player,x,y,dir,exist,kills,command" << endl;
	gotoxy(20,20);
	cout << "Tank2 by Chops....Host program" << endl;
	do
	{
		getinfo();
		calculate();
		putinfo();
		delay(50);
	}while(bioskey(1)==0);
}

void start()
{
	for(int loop=0;loop<7;loop++)
	{
		unit[loop].exist=0;
		unit[loop].kills=0;
	}
	for(loop=0;loop<maxbullets;loop++)
	{
		bullet[loop].x=0;
		bullet[loop].y=0;
		bullet[loop].exist=0;
		bullet[loop].dir=0;
	}
	ofstream file;
	file.open("h:\\player0");
	file << 7;
	file.close();
	file.open("h:\\player1");
	file << 7;
	file.close();
	file.open("h:\\player2");
	file << 7;
	file.close();
	file.open("h:\\player3");
	file << 7;
	file.close();
	file.open("h:\\player4");
	file << 7;
	file.close();
	file.open("h:\\player5");
	file << 7;
	file.close();
	file.open("h:\\player6");
	file << 7;
	file.close();
}

void getinfo()
{
	ifstream file;
	file.open("h:\\player0");
	file >> command[0];
	file.close();
	file.open("h:\\player1");
	file >> command[1];
	file.close();
	file.open("h:\\player2");
	file >> command[2];
	file.close();
	file.open("h:\\player3");
	file >> command[3];
	file.close();
	file.open("h:\\player4");
	file >> command[4];
	file.close();
	file.open("h:\\player5");
	file >> command[5];
	file.close();
	file.open("h:\\player6");
	file >> command[6];
	file.close();

}

void makeunit(int index)
{
	unit[index].x=random(maxx);
	unit[index].y=random(maxy);
	unit[index].dir=random(4);
	unit[index].exist=1;
	unit[index].status=alive;

}

void putinfo()
{
	ofstream file;
	gotoxy(1,2);
	file.open("h:\\host");
	for(int loop=0;loop<7;loop++)
	{
		file << unit[loop].x << endl;
		file << unit[loop].y << endl;
		file << unit[loop].dir << endl;
		file << unit[loop].status << endl;
		file << unit[loop].exist << endl;
		file << unit[loop].kills << endl;
		cout << loop  << "," << unit[loop].x << "," << unit[loop].y << "," << unit[loop].dir << "," << unit[loop].exist << "," << unit[loop].kills << "," << command[loop] << "               " << endl;

	}
	gotoxy(1,10);
	for(loop=0;loop<maxbullets;loop++)
	{
		file << bullet[loop].x << endl;
		file << bullet[loop].y << endl;
		file << bullet[loop].dir << endl;
		file << bullet[loop].exist << endl;
		cout << bullet[loop].exist;
	}
	file.close();
}

void addbullet(int dir, int owner)
{
	bullet[numbullets].owner=owner;
	bullet[numbullets].dir=dir;
	bullet[numbullets].exist=1;
	bullet[numbullets].x=unit[owner].x;
	bullet[numbullets].y=unit[owner].y;
	if(dir==north) bullet[numbullets].y-=15;
	else if(dir==south) bullet[numbullets].y+=15;
	else if(dir==east) bullet[numbullets].x+=15;
	else if(dir==west) bullet[numbullets].x-=15;
	numbullets++;
	if(numbullets>maxbullets) numbullets=0;
}


void calculate()
{
	for(int loop=0;loop<7;loop++)
	{
		if(unit[loop].status==alive)
		{
			if(command[loop]==north) unit[loop].y-=10;
			else if(command[loop]==south) unit[loop].y+=10;
			else if(command[loop]==east) unit[loop].x+=10;
			else if(command[loop]==west) unit[loop].x-=10;
			else if(command[loop]==fire) addbullet(unit[loop].dir,loop);
		}
		if(command[loop]!=fire) unit[loop].dir=command[loop];
		if(command[loop]==res && unit[loop].status==dead) makeunit(loop);
		else if(command[loop]==quit)
		{
			unit[loop].exist=0;
			unit[loop].status=dead;
			unit[loop].x=0;
			unit[loop].y=0;
		}
		else if(command[loop]==join && unit[loop].exist==0)
		{
			unit[loop].exist=1;
			unit[loop].status=dead;
			unit[loop].kills=0;
			unit[loop].x=random(maxx);
			unit[loop].y=random(maxy);
			unit[loop].dir=random(4);
		}


		if(unit[loop].x>maxx) unit[loop].x=1;
		else if(unit[loop].x<0) unit[loop].x=maxx;
		else if(unit[loop].y>maxy) unit[loop].y=1;
		else if(unit[loop].y<0) unit[loop].y=maxy;
	}
	for(loop=0;loop<maxbullets;loop++)
	{
		if(bullet[loop].exist==1)
		{
			if(bullet[loop].dir==north) bullet[loop].y-=25;
			else if(bullet[loop].dir==south) bullet[loop].y+=25;
			else if(bullet[loop].dir==west) bullet[loop].x-=25;
			else if(bullet[loop].dir==east) bullet[loop].x+=25;

			if(bullet[loop].x>maxx || bullet[loop].x<0 || bullet[loop].y>maxy || bullet[loop].y<0) bullet[loop].exist=0;
			for(int loop1=0;loop1<7;loop1++)
			{
				if(bullet[loop].x-15<unit[loop1].x &&
				bullet[loop].x+15>unit[loop1].x &&
				bullet[loop].y-15<unit[loop1].y &&
				bullet[loop].y+15>unit[loop1].y &&
				unit[loop1].status==alive)
				{
					unit[loop1].status=dead;
					unit[bullet[loop].owner].kills++;
				}
			}
		}
	}


}








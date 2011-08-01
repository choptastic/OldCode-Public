#include <include.h>

/////////////////////////////
/////////////////////////////
/////////////////////////////
const int normal=0;      //C/
const int ball3=1;       //O/
const int portal=2;      //N/
const int bgpnt=3;       //S/
const int slow=4;        //T/
const int big=5;         //A/
			 //N/
			 //T/
const int true=1;        //S/
const int false=0;       ////
			 ////
const int ballradius=5;  ////
			 ////
const int pad_length=30; ////
const int pad_width=15;  ////
const int def_lives=5;   ////
const int maxblocks=200; ////
const int d_cols=10;	 ////
const int d_rows=7;       ////
const int bot_blocks=200;////
const int maxballs=3; 	 ////
const int d_t_length=20; ////
			 ////
const int life=0;        ////
const int point=1;       ////
const int c_level=3;	 ////
			 ////
const int die=10;        ////
const int wallbounce=11; ////
const int blockbounce=12;////
const int paddlebounce=14;///
const int lose=13;       ////
const int laserfire=10;  ////
const int explode=6;     ////
const int inv=7;	 ////
const int barrier=8;	 ////
const int sticky=9;	 ////
/////////////////////////////
/////////////////////////////
/////////////////////////////
/////////////////////////////
struct block_type        ////
{                        //T/
	int posx;        //Y/
	int posy;        //P/
	int type;        //E/
	int exist;       //S/
	int str;         ////
}                        //O/
block[maxblocks];        //F/
			 ////
struct ball_type         //T/
{                        //H/
	int posx;        //I/
	int posy;        //N/
	int xspeed;      //G/
	int yspeed;      //S/
	int blocks_hit;  ////
	int exist;       ////
	int inv;         ////
	int stuck;	 ////
			 ////
}                        ////
ball[3];                 ////
			 ////
struct paddle_type       ////
{                        ////
	int posx;        ////
	int size;        ////
	int sticky;	 ////
}      			 ////
paddle;                  ////
			 ////
struct tail_type         ////
{                        ////
	int posx;        ////
	int posy;        ////
}                        ////
			 ////
tail[250];	         ////
			 ////
/////////////////////////////
/////////////////////////////
/////////////////////////////

int lives;
int points;
int level;
int blocks;
int portal1,portal2;
int autoplay=false;
int barr_exist=false;
int sticky_exist=false;
int t_length=d_t_length;
int cols=d_cols;
int rows=d_rows;
int block_wid=bot_blocks/rows;
int block_len=640/cols;


//**********************************************************************
//*******************  ACTUAL PROGRAM  *********************************
//**********************************************************************


////////////////////////////////////////////////////////////////////////
////////////////// Default all variables ///////////////////////////////
////////////////////////////////////////////////////////////////////////
void clear()
{
	int loop;


	for(loop=0;loop<=t_length;loop++)
	{
		tail[loop].posx=0;
		tail[loop].posy=0;
	}

	for(loop=0;loop<=2;loop++)
	{
		ball[loop].posy=0;
		ball[loop].posx=0;
		ball[loop].xspeed=-1;
		ball[loop].yspeed=-2;
		ball[loop].exist=false;
		ball[loop].blocks_hit=0;
		ball[loop].inv=false;
	}
	ball[0].exist=true;
	level=1;
	ball[0].stuck=true;

	for(loop=0;loop<=maxblocks;loop++)
	{
		block[loop].posx=0;
		block[loop].posy=0;
		block[loop].str=1;
		block[loop].exist=false;
		block[loop].type=normal;

	}
	paddle.posx=320;
	paddle.size=pad_length;
	lives=def_lives;
	barr_exist=false;

}

void makesound(int type)
{
	int loop;
	switch(type)
	{
		case(die):
		{
			for(loop=1;loop<=500;loop++)
			{
				sound(random(500)+500);
				delay(3);
			}
			nosound();
			break;
		}
		case(portal):
		{
			for(loop=250;loop<=750;loop++)
			{
				delay(2);
				sound(loop);
			}
			for(loop=500;loop<=1000;loop++)
			{
				delay(2);
				sound(loop);
			}
			for(loop=750;loop<=1250;loop++)
			{
				delay(2);
				sound(loop);
			}
			delay(20);
			break;
		}
		case(lose):
		{
			for(loop=1500;loop>=500;loop--)
			{
				delay(2);
				sound(loop);
			}
			nosound();
			break;
		}
		case(big):
		{
			for(loop=250;loop<=750;loop+=2)
			{
				sound(loop);
				delay(1);
			}
			break;
		}
		case(bgpnt):
		{
			sound(1500);
			delay(20);
			break;
		}
		case(wallbounce):
		{
			sound(1000);
			delay(5);
			break;
		}
		case(blockbounce):
		{
			sound(750);
			delay(5);
			break;
		}
		case(paddlebounce):
		{
			sound(500);
			delay(5);
			break;
		}
		case(ball3):
		{
			for(loop=500;loop<=750;loop+=2)
			{
				sound(loop);
				delay(1);
			}
			nosound();
			delay(20);
			for(loop=500;loop<=750;loop+=2)
			{
				sound(loop);
				delay(1);
			}
			nosound();
			delay(20);
			for(loop=500;loop<=750;loop+=2)
			{
				sound(loop);
				delay(1);
			}
			break;
		}
		case(inv):
		{
			for(loop=700;loop>=250;loop-=2)
			{
				sound(loop);
				delay(1);
			}
			break;

		}

		case(barrier):
		{
			for(loop=1000;loop<=1250;loop++)
			{
				sound(loop);
				delay(1);
			}
			break;
		}
	}
}


//////////////////////////////////////////////////////////////////////
///////////////////////// Updating info in the bar at bottom /////////
//////////////////////////////////////////////////////////////////////
void update(int type)
{
	switch(type)
	{
		case(point):
		{
			char string[25];
			itoa(points,string,10);
			setfillstyle(1,0);
			bar(195,465,250,480);
			setcolor(12);
			outtextxy(140,470,"Points:");
			outtextxy(200,470,string);
			break;
		}
		case(life):
		{

			char string[25];
			itoa(lives,string,10);
			setfillstyle(1,0);
			bar(55,465,150,480);
			setcolor(12);
			outtextxy(10,470,"Lives:");
			outtextxy(60,470,string);
			break;
		}
		case(c_level):
		{
			char string[25];
			itoa(level,string,10);
			setfillstyle(1,0);
			bar(265,465,330,480);
			setcolor(12);
			outtextxy(270,470,"Level:");
			outtextxy(320,470,string);
		}
	}
	setcolor(0);
}

/////////////////////////////////////////////////////////////////////////
/////////////////// Setting the Level Variables /////////////////////////
/////////////////////////////////////////////////////////////////////////
void makelevel()
{
	int loop;
	int loopx;
	int loopy;
	int rnd;
	for(loopx=1;loopx<=cols;loopx++)
	{
		for(loopy=2;loopy<=rows+1;loopy++)
		{
			loop=loopx*rows-rows+loopy;
			block[loop].exist=true;
			block[loop].posx=loopx;
			block[loop].posy=loopy;					block[loop].str=1;
			block[loop].type=normal;
			block[loop].str=random(level)+1;
			if(block[loop].str<=0) block[loop].str=1;
			if(block[loop].str>3) block[loop].str=3;
		}
	}
	for(loop=1;loop<=2;loop++)
	{
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=ball3;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=big;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=bgpnt;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=bgpnt;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=inv;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=barrier;
		rnd=random(rows*cols-cols)+cols;
		if(block[rnd].type==normal) block[rnd].type=sticky;
	}

	rnd=random(rows*cols-cols)+cols;
	block[rnd].type=portal;
	portal1=rnd;
	rnd=random(rows*cols-cols)+cols;
	if(block[rnd].type==portal)
	{
		block[rnd+1].type=portal;
		portal2=rnd+1;
	}
	else
	{
		block[rnd].type=portal;
		portal2=rnd;
	}
	blocks=rows*cols;
}


/////////////////////////////////////////////////////////////////
///////////////// Draw block ////////////////////////////////////
/////////////////////////////////////////////////////////////////
void drawblock(int blocknum)
{
	int x1,x2,y1,y2;
	x1=block_len*block[blocknum].posx-block_len+2;
	x2=block_len*block[blocknum].posx;
	y1=block_wid*block[blocknum].posy-block_wid+2;
	y2=block_wid*block[blocknum].posy;
	setlinestyle(DOTTED_LINE,1,1);
	/*
	if(block[blocknum].str==explode)
	{
		setfillstyle(1,14);
		bar(x1,y1,x2,y2);
	}
	else*/
	setfillstyle(1,block[blocknum].posy-1);
	if(block[blocknum].str==1)
	{
		bar(x1,y1,x2,y2);
		setcolor(0);
		line(x1,y1,x2,y2);
		line(x1,y2,x2,y1);
		line((x1+x2)/2,y1,(x1+x2)/2,y2);
		line(x1,(y1+y2)/2,x2,(y1+y2)/2);

	}
	else if(block[blocknum].str==2)
	{
		bar(x1,y1,x2,y2);
		setcolor(0);
		line((x1+x2)/2,y1,(x1+x2)/2,y2);
		line(x1,(y1+y2)/2,x2,(y1+y2)/2);
	}
	else if(block[blocknum].str==3)
	{
		bar(x1,y1,x2,y2);
	}


	if(block[blocknum].type==ball3)
	{

		setfillstyle(1,0);
		fillellipse(x1+(block_len/4),y2-block_wid/2,5,5);
		fillellipse(x1+(block_len/2),y2-block_wid/2,5,5);
		fillellipse(x1+(block_len/4)+(block_len/2),y2-block_wid/2,5,5);
		setfillstyle(1,15);
		fillellipse(x1+(block_len/4)+2,y2-block_wid/2+2,5,5);
		fillellipse(x1+(block_len/2)+2,y2-block_wid/2+2,5,5);
		fillellipse(x1+(block_len/4)+(block_len/2)+2,y2-block_wid/2,5,5);

	}
	else if(block[blocknum].type==bgpnt)
	{
		setcolor(0);
		outtextxy(x1+(block_len/2)-5,y2-block_wid/2,"PTS");
		setcolor(15);
		outtextxy(x1+(block_len/2)-3,y2-(block_wid/2)-2,"PTS");
		setcolor(0);
	}
	else if(block[blocknum].type==portal)
	{
		setfillstyle(2,14);
		bar(x1,y1,x2,y2);
	}
	else if(block[blocknum].type==big)
	{
		setfillstyle(1,0);
		bar(x1+15,y1+7,x2-15,y2-7);
		setfillstyle(1,15);
		bar(x1+13,y1+7,x2-17,y2-9);
	}
	else if(block[blocknum].type==inv)
	{
		setfillstyle(1,15);
		fillellipse(x1+(block_len/2),y2-block_wid/2-2,5,5);
		setfillstyle(1,14);
		fillellipse(x1+(block_len/2),y2-block_wid/2-2,4,4);
		setfillstyle(1,13);
		fillellipse(x1+(block_len/2),y2-block_wid/2-2,3,3);
		setfillstyle(1,12);
		fillellipse(x1+(block_len/2),y2-block_wid/2-2,2,2);
	}
	else if(block[blocknum].type==barrier)
	{
		setcolor(15);
		setfillstyle(1,15);
		fillellipse(x1+(block_len/4),y2-block_wid/2,5,5);
		setlinestyle(SOLID_LINE,1,1);
		line(x1+5,y2-5,x2-5,y2-5);
		setcolor(0);
	}
	else if(block[blocknum].type==sticky)
	{
		setcolor(0);
		outtextxy(x1+(block_len/2),y2-block_wid/2,"S");
		setcolor(15);
		outtextxy(x1+(block_len/2),y2-(block_wid/2)-2,"S");
		setcolor(0);
	}

	setlinestyle(SOLID_LINE,1,1);

}

//////////////////////////////////////////////////////////////
/////////////////// Drawing the Level ////////////////////////
//////////////////////////////////////////////////////////////
void drawlevel()
{
	int loop;
	for(loop=0;loop<=maxblocks;loop++)
	{
		drawblock(loop);
		delay(10);
	}
}

///////////////////////////////////////////////////////////////////
////////////////////// Drawing Empty Block ////////////////////////
///////////////////////////////////////////////////////////////////
void drawemptyblock(int x, int y)
{
	int x1,x2,y1,y2;
	setfillstyle(1,0);
	x1=block_len*x-block_len+2;
	x2=block_len*x;
	y1=block_wid*y-block_wid+2;
	y2=block_wid*y;
	bar(x1,y1,x2,y2);
}


void nextlevel()
{
	nosound();
	cleardevice();
	level++;

	initmouse();
	for(int loop=0;loop<=2;loop++)
	{
		ball[loop].exist=false;
		ball[loop].blocks_hit=0;
		ball[loop].xspeed=-1;
		ball[loop].yspeed=-2;
		ball[loop].posx=0;
		ball[loop].posy=0;
	}
	for(loop=0;loop<t_length;loop++)
	{
		tail[loop].posx=0;
		tail[loop].posy=0;
	}
	ball[0].exist=true;
	ball[0].stuck=true;
	ball[0].posy=0;
	ball[0].xspeed=0;
	ball[0].yspeed=2;
	makelevel();
	drawlevel();

	paddle.size=pad_length;
	points+=level*20;
	update(life);
	update(point);
	update(c_level);
	setfillstyle(1,13);
	bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
	barr_exist=false;
	sticky_exist=false;
}


////////////////////////////////////////////////////////////////////
//////////////////// If Ball hit's Block ///////////////////////////
////////////////////////////////////////////////////////////////////
void blockhit(int hit,int ballused)
{
	block[hit].str--;
	if(block[hit].str==0)
	{
		block[hit].exist=false;
		drawemptyblock(block[hit].posx,block[hit].posy);
		blocks--;
		switch(block[hit].type)
		{
			case(ball3):
			{
				fillellipse(ball[0].posx,ball[0].posy,ballradius,ballradius);
				fillellipse(ball[1].posx,ball[1].posy,ballradius,ballradius);
				fillellipse(ball[2].posx,ball[2].posy,ballradius,ballradius);
				for(int loop=0;loop<=maxballs;loop++)
				{
					if(ball[loop].exist==false)
					{
						ball[loop].exist=true;
						ball[loop].posx=ball[ballused].posx;
						ball[loop].posy=ball[ballused].posy;
						if(loop%2==1) ball[loop].xspeed=ball[ballused].xspeed*(-1);
						else
						{
							if(ball[ballused].xspeed>=1) ball[loop].xspeed=ball[ballused].xspeed-1;
							else ball[loop].xspeed=ball[ballused].xspeed+1;
						}
						ball[loop].yspeed=ball[ballused].yspeed*(-1);
						ball[loop].blocks_hit=0;
					}
				}
				makesound(ball3);
				break;
			}
			case(bgpnt):
			{
				points+=ball[ballused].blocks_hit*20;
				makesound(bgpnt);
				break;
			}
			case(big):
			{
				paddle.size+=30;
				makesound(big);
				break;
			}
			case(portal):
			{
				if(portal1==hit)
				{
					ball[ballused].posx=block[portal2].posx*block_len-(block_len/2);
					ball[ballused].posy=block[portal2].posy*block_wid-(block_wid/2);
					block[portal2].exist=false;
					makesound(portal);
					drawemptyblock(block[portal2].posx,block[portal2].posy);
				}
				else
				{
					ball[ballused].posx=block[portal1].posx*block_len-(block_len/2);
					ball[ballused].posy=block[portal1].posy*block_wid-(block_wid/2);
					block[portal1].exist=false;
					makesound(portal);
					drawemptyblock(block[portal1].posx,block[portal1].posy);

				}
				blocks--;
				break;
			}
			case(normal):
			{
				makesound(blockbounce);
				break;
			}
			case(inv):
			{
				makesound(inv);
				ball[ballused].inv=true;
				break;
			}
			case(barrier):
			{
				makesound(barrier);
				setcolor(15);
				line(1,460,640,460);
				setcolor(0);
				barr_exist=true;
				break;
			}

			case(sticky):
			{
				makesound(normal);
				paddle.sticky=true;
				break;
			}


		}
		if(blocks<=0) nextlevel();

	}
	else
	{
		drawblock(hit);
		makesound(blockbounce);
	}


	ball[ballused].blocks_hit++;
	points+=ball[ballused].blocks_hit;
	update(point);
}


//////////////////////////////////////////////////////////////////////
///////////////// Checking for a Block to get hit ////////////////////
//////////////////////////////////////////////////////////////////////
void blockcheck()
{
	int loopball;
	int loopblock;
	int x1,x2,y1,y2;
	for(loopball=0;loopball<=2;loopball++)
	{
		if(ball[loopball].exist==true)
		{
			for(loopblock=0;loopblock<=maxblocks;loopblock++)
			{
				if(block[loopblock].exist==true)
				{
					x1=block_len*block[loopblock].posx-block_len+1;
					x2=block_len*block[loopblock].posx;
					y1=block_wid*block[loopblock].posy-block_wid+1;
					y2=block_wid*block[loopblock].posy;
					if(x1-ballradius<=ball[loopball].posx && ball[loopball].posx<=x2+ballradius)
					{
						if(y2-ballradius<=ball[loopball].posy && ball[loopball].posy<=y2+ballradius && ball[loopball].yspeed<0)
						{
							if(block[loopblock].type!=inv)
							{
								if(ball[loopball].inv==false && block[loopblock].type!=inv) ball[loopball].yspeed*=(-1);
								ball[loopball].posy=y2+ballradius+2;
							}
								blockhit(loopblock,loopball);
						}
						else if(y1-ballradius<=ball[loopball].posy && ball[loopball].posy<=y1+ballradius && ball[loopball].yspeed>0)
						{
							if(block[loopblock].type!=inv)
							{
								if(ball[loopball].inv==false) ball[loopball].yspeed*=(-1);
								ball[loopball].posy=y1-ballradius-2;
							}
							blockhit(loopblock,loopball);
						}
					}
					if(y1-ballradius<=ball[loopball].posy && ball[loopball].posy<=y2+ballradius)
					{
						if(x2-ballradius<=ball[loopball].posx && ball[loopball].posx<=x2+ballradius && ball[loopball].xspeed<0)
						{
							if(block[loopblock].type!=inv)
							{
								if(ball[loopball].inv==false && block[loopblock].type!=inv)
								ball[loopball].xspeed*=(-1);
								ball[loopball].posx=x2+ballradius+2;
							}
							blockhit(loopblock,loopball);
						}
						else if(x1-ballradius<=ball[loopball].posx && ball[loopball].posx<=x1+ballradius && ball[loopball].xspeed>0)
						{
							if(block[loopblock].type!=inv)
							{
								if(ball[loopball].inv==false && block[loopblock].type!=inv)
								ball[loopball].xspeed*=(-1);
								ball[loopball].posx=x1-ballradius-2;
							}
							blockhit(loopblock,loopball);
						}
					}
				}
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////
///////////////////////// Checking if ball hits paddle //////////////////
/////////////////////////////////////////////////////////////////////////
void paddlecheck()
{
	int loop;
	int hit=false;
	int x1,x2,y1=430,y2=430+pad_width;
	int placehit;
	for(loop=0;loop<=2;loop++)
	{
		x1=paddle.posx-paddle.size;
		x2=paddle.posx+paddle.size;
		if(ball[loop].exist==true)
		{


			if(x1-ballradius-1<=ball[loop].posx && ball[loop].posx<=x2+ballradius+1)
			{
				if(y1-ballradius-(ballradius/2)-1<=ball[loop].posy && ball[loop].posy<=y1+ballradius+1)
				{
					if(ball[loop].yspeed>0) ball[loop].yspeed*=(-1);
					ball[loop].posy=430-ballradius*2-1;
					hit=true;
				}
			}

			if(y1-ballradius-1<=ball[loop].posy && ball[loop].posy<=y2+ballradius+1)
			{
				if(x2-ballradius-1<=ball[loop].posx && ball[loop].posx<=x2+ballradius+1)
				{
					if(ball[loop].xspeed<0) ball[loop].xspeed*=(-1);
					ball[loop].posx=paddle.posx+ballradius+paddle.size+1;
					hit=true;
				}
				else if(x1-ballradius-1<=ball[loop].posx && ball[loop].posx<=x1+ballradius+1)
				{
					if(ball[loop].xspeed>0)ball[loop].xspeed*=(-1);
					ball[loop].posx=paddle.posx-ballradius-paddle.size-1;
					hit=true;
				}
			}


			if(hit==true && ball[loop].stuck!=true)
			{
				hit=false;
				ball[loop].inv=false;
				if(paddle.sticky==true)
				{
					ball[loop].stuck=true;
					paddle.sticky=false;
				}

				makesound(blockbounce);
				ball[loop].blocks_hit=0;
				placehit=paddle.posx-ball[loop].posx;

				if(placehit>0) ball[loop].xspeed--;
				else ball[loop].xspeed++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
///////////////// Deleting Ball and Checking if all balls are dead ////
///////////////////////////////////////////////////////////////////////
void deleteball(int todelete)
{
	ball[todelete].exist=false;
	setfillstyle(1,0);
	fillellipse(ball[todelete].posx,ball[todelete].posy,ballradius,ballradius);
	if(ball[0].exist==false && ball[1].exist==false && ball[2].exist==false)
	{
		lives--;
		if(lives>0)
		{
			update(life);
			for(int loop=0;loop<=2;loop++)
			{
				ball[loop].posy=0;
				ball[loop].xspeed=-1;
				ball[loop].yspeed=-2;
				ball[loop].exist=false;
				ball[loop].blocks_hit=0;
			}
			ball[0].posy=250;
			ball[0].posx=250;
			ball[0].exist=true;
			setcolor(12);
			outtextxy(150,bot_blocks+100,"You lose one life, Press any key to continue");
			makesound(die);
			getch();
			setfillstyle(1,0);
			bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
			paddle.size=pad_length;
			setfillstyle(1,13);
			bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
			setcolor(0);
			ball[0].stuck=true;
			outtextxy(150,bot_blocks+100,"You lose one life, Press any key to continue");
		}
		else
		{
			setcolor(12);
			outtextxy(185,bot_blocks+100,"Man you're dumb. you lose fool");
			makesound(lose);
			getch();
			setcolor(0);
			outtextxy(185,bot_blocks+100,"Man you're dumb. you lose fool");

		}

	}
}

///////////////////////////////////////////////////////////////////////
////////////////// Checking if the Borders were hit ///////////////////
///////////////////////////////////////////////////////////////////////
void limitcheck()
{
	int loop;
	for(loop=0;loop<=2;loop++)
	{
		if(ball[loop].xspeed<0 && ball[loop].posx-ballradius<=1)
		{
			ball[loop].xspeed*=(-1);
			makesound(wallbounce);
		}
		else if(ball[loop].xspeed>0 && ball[loop].posx+ballradius>=640)
		{
			ball[loop].xspeed*=(-1);
			makesound(wallbounce);
		}
		else if(ball[loop].yspeed<0 && ball[loop].posy-ballradius<=1)
		{
			ball[loop].yspeed*=(-1);
			makesound(wallbounce);
		}
		//else if(ball[loop].yspeed>0 && ball[loop].posy+ballradius>=460) ball[loop].yspeed*=(-1);
		else if(ball[loop].yspeed>0 && ball[loop].posy>=460)
		{
			if(barr_exist==false) deleteball(loop);
			else
			{
				makesound(wallbounce);
				barr_exist=false;
				setcolor(0);
				line(1,460,640,460);
				ball[loop].yspeed*=(-1);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
/////////////// Draw and Move the Ball ///////////////////////////////
//////////////////////////////////////////////////////////////////////
void drawmoveball()
{
	int loop;
	int loop1;
	for(loop=0;loop<=2;loop++)
	{
		if(ball[loop].exist!=false)
		{
			setfillstyle(1,0);
			setcolor(0);
			fillellipse(ball[loop].posx,ball[loop].posy,ballradius+1,ballradius+1);


			setfillstyle(1,0);
			setcolor(0);
			fillellipse(tail[t_length-1].posx,tail[t_length-1].posy,ballradius,ballradius);
			for(loop1=t_length-1;loop1>0;loop1--)
			{
				tail[loop1].posx=tail[loop1-1].posx;
				tail[loop1].posy=tail[loop1-1].posy;
			}
			tail[0].posx=ball[loop].posx;
			tail[0].posy=ball[loop].posy;
			setfillstyle(1,7);
			setcolor(7);
			fillellipse(tail[0].posx,tail[0].posy,ballradius,ballradius);
			setcolor(0);



			if(ball[loop].stuck==true)
			{
				ball[loop].posx=paddle.posx;
				ball[loop].posy=430-ballradius-3;
			}
			else
			{
				ball[loop].posx+=ball[loop].xspeed*((level+1)/2);
				ball[loop].posy+=ball[loop].yspeed*((level+1)/2);
			}

			paddlecheck();
			limitcheck();
			blockcheck();

			if(ball[loop].inv==false)
			{
				setfillstyle(1,15);
				fillellipse(ball[loop].posx,ball[loop].posy,ballradius,ballradius);
			}
			else
			{
				setfillstyle(1,14);
				fillellipse(ball[loop].posx,ball[loop].posy,ballradius,ballradius);
				setfillstyle(1,4);
				fillellipse(ball[loop].posx,ball[loop].posy,ballradius-2,ballradius-2);
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////
////////////////////////// Move and Draw the paddle //////////////////
//////////////////////////////////////////////////////////////////////
void paddlemove()
{

	if(autoplay==true)
	{
		setfillstyle(1,0);
		bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
		paddle.posx=ball[0].posx;
		setfillstyle(1,13);
		bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
	}
	else
	{
		if(mousemoved()==1)
		{
			setfillstyle(1,0);
			bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
			paddle.posx=readmousex();
			if(paddle.posx+paddle.size>=640) paddle.posx=639-paddle.size;
			else if(paddle.posx-paddle.size<=1) paddle.posx=2+paddle.size;
			setfillstyle(1,13);
			bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);


		}
	}
	if(mousereleased(1)==1)
	{
		makesound(normal);
		delay(20);
	}



}

//////////////////////////////////////////////////////////////////////
//////////////////// Start the Game //////////////////////////////////
//////////////////////////////////////////////////////////////////////
void start()
{
	setcolor(0);
	clear();
	cleardevice();
	makelevel();
	drawlevel();
	update(life);
	update(c_level);
	update(point);
	initmouse();
	setfillstyle(1,13);
	bar(paddle.posx+paddle.size,430,paddle.posx-paddle.size,430+pad_width);
	barr_exist=false;
	ball[0].stuck=true;
	points=0;
}
//////////////////////////////////////////////////////////////////////
////////////////////// Instructions on playing ///////////////////////
//////////////////////////////////////////////////////////////////////
void instr()
{

	int select=0;
	int select1=0;
	while(select!=6)
	{
	select=title(1,6,"->","Chops's Breakout Game : Help and Options","See controls","See Cheats","See meaning of Special Blocks","About","Change Options","Leave Help","");
	cleardevice();
	switch(select)
	{
		case(1):
		{
			outtextxy(100,100,"Press Mouse 1 to Release a stuck Ball");
			outtextxy(100,150,"Press Q to quit at any time");
			outtextxy(100,200,"Press P to pause the game");
			break;
		}
		case(2):
		{
			outtextxy(100,100,"Press S to enabled Sticky paddle once");
			outtextxy(100,150,"Press N to skip to next level");
			break;
		}
		case(3):
		{
			outtextxy(100,100,"PTS means 10X points normally issued to that one block");
			outtextxy(100,150,"S enables sticky Paddle once");
			outtextxy(100,200,"Blocks with stripes in them are portals");
			outtextxy(100,250,"The funny looking ball means Super Ball(block with break through blocks)");
			outtextxy(100,300,"The line with the ball over it means a barrier will form");
			outtextxy(100,350,"The 3 balls means triple Ball");
			outtextxy(100,400,"The white bar means paddle elongation");
			break;
		}
		case(4):
		{
			outtextxy(100,100,"Chops' Break out by Chops");
			outtextxy(100,150,"Mouse Unit by Von Gong");
			outtextxy(100,200,"Chops' Menu By Chops");
			outtextxy(100,250,"I'm gonna get a  A on this");
		break;
		}
		case(5):
		{
			while(select1!=4)
			{
				closegraph();
				select1=title(0,4,"->","Chops's Breakout : Options","Change Columns","Change Rows","Change Tail Length","Leave Options","","","");
				clrscr();
				switch(select1)
				{
					case(1):
					{
						cout << "Current Columns : " << rows;
						cout << endl << "New Columns : ";
						cin >> cols;
						break;
					}
					case(2):
					{
						cout << "Current Columns : " << rows;
						cout << endl << "New Columns : ";
						cin >> rows;
						break;
					}
					case(3):
					{
						cout << "Current Tail Length : " << t_length;
						cout << endl << "New Tail Length : ";
						cin >> t_length;
						break;
					}
				}
			}
			block_wid=bot_blocks/rows;
			block_len=640/cols;
			setup();
			break;
		}




	}

	if(select!=6)
	{
		setcolor(1);
		outtextxy(100,450,"Press any key to return");
		getch();
	}

	}

}






void main()
{
	setup();
	randomize();
	char choice=0;
	char quit=0;
	int select=0;
	int loop;
	int exists;
	while(quit!='Y')
	{
	quit=0;
	select=title(1,3,"->","Chops's Breakout Game: Main Menu","Play Breakout","Help and Options","Quit","","","","");
	switch(select)
	{
		case(1):
		{

			start();
			choice=0;
			break;
		}
		case(2):
		{
			instr();
			choice='Q';

			break;
		}
		case(3):
		{
			choice='Q';
			break;
		}
	}
	while(choice!='Q')
	{
		do
		{
			exists=0;
			for(loop=0;loop<3;loop++)
			{
				if(ball[loop].exist==true) exists++;
			}
			delay(6-exists);
			paddlemove();
			drawmoveball();

			if(mousereleased(0)==1)
			{
				for(loop=0;loop<=2;loop++)
				{
					if(ball[loop].stuck==true)
					{
						ball[loop].stuck=false;
						ball[loop].xspeed=0;
						ball[loop].yspeed=-2;
					}
				}
			}
			nosound();
			for(loop=0;loop<=2;loop++)
			{
				if(ball[loop].xspeed>3) ball[loop].xspeed=3;
				else if(ball[loop].xspeed<-3) ball[loop].xspeed=-3;
				if(ball[loop].yspeed>3) ball[loop].yspeed=3;
				else if(ball[loop].yspeed<-3) ball[loop].yspeed=-3;
			}
			if(lives==0)
			{
				choice='Q';
				break;
			}

		}
		while(!bioskey(1));
		if(choice!='Q') choice=toupper(getch());

		switch(choice)
		{
			case('N'):
			{
				nextlevel();
				break;
			}
			case('A'):
			{
				if(autoplay==false) autoplay=true;
				else autoplay=false;
				break;
			}
			case('P'):
			{
				setcolor(15);
				outtextxy(250,300,"Paused, press any key to resume");
				getch();
				setcolor(0);
				outtextxy(250,300,"Paused, press any key to resume");
				break;
			}

			case('S'):
			{
				paddle.sticky=true;
				break;
			}

		}

	}

	if(select!=2)
	{
		cleardevice();
		setcolor(15);
		outtextxy(200,100,"Do you want to Quit? (Y=quit : N=Main Menu)");
		setcolor(0);
		quit=toupper(getch());
	}
	}
	closegraph();
}











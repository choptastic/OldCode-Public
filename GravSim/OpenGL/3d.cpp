

#include "3d.hpp"

const double DEGTORAD=3.14159265/180;


void pov::turnright(float amt)
{
	horiz_rot-=amt;
}

void pov::turnup(float amt)
{
	vert_rot-=amt;
}

void pov::changespeed(int val)
{
	_speed+=val;
	if(_speed<1)
		_speed=1;
	cout << "Speed : " << _speed << endl;
}

void pov::moveforeward()
{
	//calcspeed(FOREWARD);
	float dirx, dirz;
	dirx=(float)sin(-horiz_rot*DEGTORAD);
	dirz=(float)cos(-horiz_rot*DEGTORAD);
	locx+=_speed*dirx;
	locz+=_speed*dirz;
}

void pov::movebackward()
{
	//calcspeed(BACKWARD);
	float dirx, dirz;
	dirx=(float)sin(-horiz_rot*DEGTORAD);
	dirz=(float)cos(-horiz_rot*DEGTORAD);
	locx-=_speed*dirx;
	locz-=_speed*dirz;
}

void pov::moveup()
{
	locy-=_speed;
}

void pov::movedown()
{
	locy+=_speed;
}


void pov::moveleft()
{
	//calcspeed(LEFT);
	float dirx, dirz;
	dirx=(float)cos(horiz_rot*DEGTORAD);
	dirz=(float)sin(horiz_rot*DEGTORAD);
	locx+=_speed*dirx;
	locz+=_speed*dirz;
}

void pov::moveright()
{
	//calcspeed(RIGHT);
	float dirx, dirz;
	dirx=(float)cos(horiz_rot*DEGTORAD);
	dirz=(float)sin(horiz_rot*DEGTORAD);
	locx-=_speed*dirx;
	locz-=_speed*dirz;
}


void pov::moveabsolute(float x, float y, float z) 
{
	locx=x;
	locy=y;
	locz=z;
}

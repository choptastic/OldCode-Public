#ifndef B3D_H

#define B3D_H

#include "vector3d.cpp"
#include <graph.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <dir.h>
#include <math.h>


const int distance_constant=256;
const int diam_constant=distance_constant/4;
vector_3d view(0,0,1);
float OX=0,OY=0,OZ=0;

struct point_3d
{
	float x,y,z;
	point_3d(float,float,float);
	point_3d();
};
point_3d::point_3d(float xx, float yy, float zz):x(xx),y(yy),z(zz) {}
point_3d::point_3d():x(0),y(0),z(0) {}





void calc_3d_p(int&,int&,float, float, float);
void calc_3d_p(int&,int&,point_3d);

void dr_point_p(float,float,float,const image&);
void dr_point_p(float,float,float);
//void dr_line_p(int, int, int, int, int, int, int);
vector_3d crossproduct(vector_3d,vector_3d);
float dotproduct(vector_3d,vector_3d);
float dist_point_line(vector_3d,float, float, float,
							float, float, float);
float dist_point_line_nosqr(vector_3d,
							float, float, float,
							float, float, float);
double sq(float);



double sq(float x)
{return (double(x)*double(x));}


void calc_3d_p(int &posx,int &posy,
		  float px, float py, float pz)
{
	float hdist,zdist,xoffset,yoffset, ox=OX,oy=OY,oz=OZ;
	px-=ox;
	py-=oy;
	pz-=oz;
	ox=oy=oz=0;
	if(sq(px-view.x)+sq(py-view.y)+sq(pz-view.z)>sq(px+view.x)+sq(py+view.y)+sq(pz+view.z))
		return;
	vector_3d v=view;
	hdist=sq(px)+sq(pz);
	if(sq(v.x-px)+sq(v.z-pz)>hdist) return;
	v*=sqrt(hdist);
	float dist=dist_point_line(v,ox,0,oz,px,0,pz);
	xoffset=dist;
	if(dist>dist_point_line(v.turnxz(.00001),ox,0,oz,px,0,pz))
		xoffset*=-1;
	float zdist_nosqr=hdist-sq(xoffset);
	if(zdist_nosqr<0) return;
	zdist=sqrt(zdist_nosqr);
	yoffset=py;
	float dcdivzdist=distance_constant/zdist;
	posx=half_X+(xoffset)*(dcdivzdist);
	posy=half_Y-(yoffset)*(dcdivzdist);
}

void calc_3d_p(int &posx,int &posy,point_3d p)
{
	calc_3d_p(posx, posy, p.x, p.y, p.z);
}

void dr_point_p(float px, float py, float pz,const image &pic)
{
	int posx,posy;

	float scale;
	calc_3d_p(posx,posy,px,py,pz);
	if(posx+scale*pic.sizex()<MAXX && posy+scale*pic.sizey()<MAXY && posx>=0 && posy>=0)
	{
		scale=diam_constant/sqrt(sq(px-OX)+sq(pz-OZ));
		pic.drawscale(posx-(scale*(pic.sizex()>>1)),posy-scale*(pic.sizey()>>1),scale);
	}
}

void dr_point_p(float px, float py, float pz)
{
	int posx,posy;

	float scale;
	calc_3d_p(posx,posy,px,py,pz);
	if(posx<MAXX && posy<MAXY && posx>=0 && posy>=0)
	{
		pset(posx,posy,15);
		//pic.drawscale(posx-(scale*(pic.sizex()>>1)),posy-scale*(pic.sizey()>>1),scale);
	}
}

/*
must be changed for new graphics commands
void dr_line_p(int x1, int y1, int z1, int x2, int y2, int z2, int color)
{
	int px1, px2, py1, py2;
	calc_3d_p(px1,py1,x1,y1,z1);
	calc_3d_p(px2,py2,x2,y2,z2);
	setcolor(color);
	line(px1,py1,px2,py2);
}
*/

vector_3d crossproduct(vector_3d a, vector_3d b)
{
	return vector_3d(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

float dotproduct(vector_3d a, vector_3d b)
{
	return a.x*b.x+a.y*b.y+a.z+b.z;
}


float dist_point_line(vector_3d v1,
							float x, float y, float z,
							float px, float py, float pz)
{
	register float v1_mag_nosqr=v1.mag_nosqr();
	if(v1_mag_nosqr<=0) return 100000.0;
	vector_3d v2(px-x,py-y,pz-z);
	return sqrt(crossproduct(v1,v2).mag_nosqr()/v1_mag_nosqr);
}

float dist_point_line_nosqr(vector_3d v1,
							float x, float y, float z,
							float px, float py, float pz)
{
	register float v1_mag_nosqr=v1.mag_nosqr();
	if(v1_mag_nosqr<=0) return 100000.0;
	vector_3d v2(px-x,py-y,pz-z);
	return crossproduct(v1,v2).mag_nosqr()/v1_mag_nosqr;
}

#endif




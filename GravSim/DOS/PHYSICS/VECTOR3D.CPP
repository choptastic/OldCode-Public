#ifndef VEC3D_H
#define VEC3D_H


#include <conio.h>
#include <iostream.h>
#include <math.h>

struct vector_3d
{
	float x,y,z;

	vector_3d();
	vector_3d(float,float,float);
	vector_3d(float,float);

	vector_3d setx(float);
	vector_3d sety(float);
	vector_3d setz(float);
	vector_3d setall(float,float,float);

	float getx();
	float gety();
	float getz();
	float getall(float&,float&,float&);

	float magnitude();
	float mag_nosqr();
	vector_3d unit_vector();
	vector_3d turnxz(float);

	vector_3d operator += (vector_3d);
	vector_3d operator *= (float);
	vector_3d operator /= (float);
};

vector_3d operator + (vector_3d,vector_3d);
vector_3d operator * (vector_3d,float);
vector_3d operator / (vector_3d,float);
vector_3d operator * (float,vector_3d);
vector_3d points(float,float,float,float,float,float);
ostream& operator << (ostream&,vector_3d);


// CODE---implementation

vector_3d::vector_3d():x(0),y(0),z(0) {}
vector_3d::vector_3d(float xx, float yy):x(xx),y(yy) {}
vector_3d::vector_3d(float xx, float yy, float zz):x(xx),y(yy),z(zz) {}


vector_3d vector_3d::setx(float xx)
{
	x=xx;
	return *this;
}
vector_3d vector_3d::sety(float yy)
{
	y=yy;
	return *this;
}
vector_3d vector_3d::setz(float zz)
{
	z=zz;
	return *this;
}


float vector_3d::getx()
{return x;}
float vector_3d::gety()
{return y;}
float vector_3d::getz()
{return z;}



// + and +=
vector_3d vector_3d::operator += (vector_3d v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}
vector_3d operator + (vector_3d a, vector_3d b)
{return a+=b;}

// * and *=
vector_3d vector_3d::operator *= (float v)
{
	x*=v;
	y*=v;
	z*=v;
	return *this;
}
vector_3d operator * (vector_3d a, float b)
{return a*=b;}
vector_3d operator * (float a, vector_3d b)
{return b*=a;}

// / and /=
vector_3d vector_3d::operator /= (float v)
{
	x/=v;
	y/=v;
	z/=v;
	return *this;
}
vector_3d operator / (vector_3d a, float b)
{return a/=b;}

ostream& operator << (ostream & out, vector_3d v)
{
	out << "<" << v.x << "," << v.y << "," << v.z << ">";
	return out;
}


float vector_3d::magnitude()
{return sqrt(x*x+y*y+z*z);}

float vector_3d::mag_nosqr()
{return x*x+y*y+z*z;}

vector_3d vector_3d::unit_vector()
{return (*this/magnitude());}



vector_3d points(float x1, float y1, float z1, float x2, float y2, float z2)
{
	x2-=x1;
	y2-=y1;
	z2-=z1;
	return vector_3d(x2,y2,z2);
}

vector_3d vector_3d::turnxz(float turn_val)
{
	float angle;
	if(x==0) x=.0001;
	angle=atan(z/x);
	if(x<0) angle+=M_PI;
	angle+=turn_val;
	x=cos(angle);
	z=sin(angle);
	return *this;
}








#endif
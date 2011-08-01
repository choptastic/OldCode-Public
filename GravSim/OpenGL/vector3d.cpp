

#include "vector3d.hpp"


vector3d vector3d::setx(float xx)
{
	x=xx;
	return *this;
}
vector3d vector3d::sety(float yy)
{
	y=yy;
	return *this;
}
vector3d vector3d::setz(float zz)
{
	z=zz;
	return *this;
}


float vector3d::getx() const
{return x;}
float vector3d::gety() const
{return y;}
float vector3d::getz() const
{return z;}



vector3d vector3d::operator += (vector3d v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}
vector3d operator + (vector3d a, vector3d b)
{return a+=b;}



vector3d vector3d::operator *= (float v)
{
	x*=v;
	y*=v;
	z*=v;
	return *this;
}
vector3d operator * (vector3d a, float b)
{return a*=b;}
vector3d operator * (float a, vector3d b)
{return b*=a;}




vector3d vector3d::operator /= (float v)
{
	x/=v;
	y/=v;
	z/=v;
	return *this;
}
vector3d operator / (vector3d a, float b)
{return a/=b;}

ostream& operator << (ostream & out, const vector3d &v)
{
	out << "<" << v.getx() << "," << v.gety() << "," << v.getz() << ">";
	return out;
}


vector3d vector3d::opposite() const
{
	return vector3d(-x, -y, -z);
}

float vector3d::mag_nosqr()
{
	if(magnosqr==0)
		magnosqr=x*x+y*y+z*z;
	return magnosqr;
}

float vector3d::magnitude()
{
	if(mag==0)
		mag=(float)sqrt(mag_nosqr());
	return mag;
}

vector3d vector3d::unit_vector()
{return *this/magnitude();}


vector3d points(float x1, float y1, float z1, float x2, float y2, float z2)
{
	x2-=x1;
	y2-=y1;
	z2-=z1;
	return vector3d(x2,y2,z2);
}


float dist_point_line(vector3d &v1,
							const float &x, const float &y, const float &z,
							const float &px, const float &py, const float &pz)
{
	return (float)sqrt(dist_point_line_nosqr(v1,x,y,z,px,py,pz));
}

float dist_point_line_nosqr(vector3d &v1,
							const float &x, const float &y, const float &z,
							const float &px, const float &py, const float &pz)
{
	float v1_mag_nosqr=v1.mag_nosqr();
	if(v1_mag_nosqr<=0) return 100000.0;
	vector3d v2(px-x,py-y,pz-z);
	return crossproduct(v1,v2).mag_nosqr()/v1_mag_nosqr;
}

float sq(const float &x)
{
	return x*x;
}

vector3d crossproduct(const vector3d &a, const vector3d &b)
{
	return vector3d(a.gety()*b.getz() - a.getz()*b.gety(),
					a.getz()*b.getx() - a.getx()*b.getz(),
					a.getx()*b.gety() - a.gety()*b.getx());
}

float dotproduct(const vector3d &a, const vector3d &b)
{
	return a.getx()*b.getx() + a.gety()*b.gety() + a.getz()+b.getz();
}

float dist_two_points_nosqr(const float &x1, const float &y1, const float &z1,
							const float &x2, const float &y2, const float &z2)
{
	return sq(x1-x2) + sq(y1-y2) + sq(z1-z2);

}
float dist_two_points(	const float &x1, const float &y1, const float &z1,
						const float &x2, const float &y2, const float &z2)
{
	return (float)sqrt(dist_two_points_nosqr(x1,y1,z1,x2,y2,z2));
}
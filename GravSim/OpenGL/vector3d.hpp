#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream.h>
#include <math.h>

class vector3d
{
	float x,y,z;
	float mag, magnosqr;
public:
	inline vector3d():x(0),y(0),z(0) {mag=magnosqr=0;}
	inline vector3d(float xx, float yy):x(xx),y(yy) {mag=magnosqr=0;}
	inline vector3d(float xx, float yy, float zz):x(xx),y(yy),z(zz) {mag=magnosqr=0;}


	vector3d setx(float);
	vector3d sety(float);
	vector3d setz(float);
	vector3d setall(float,float,float);

	float getx() const;
	float gety() const;
	float getz() const;
	float getall(float&,float&,float&) const;

	float magnitude();
	float mag_nosqr();
	vector3d unit_vector();
	vector3d turnxz(float);
	vector3d opposite() const;

	vector3d operator += (vector3d);
	vector3d operator *= (float);
	vector3d operator /= (float);
};

vector3d operator + (vector3d,vector3d);
vector3d operator * (vector3d,float);
vector3d operator / (vector3d,float);
vector3d operator * (float,vector3d);
vector3d points(float,float,float,float,float,float);
ostream & operator << (ostream&, const vector3d&);

float sq(const float &x);

float dist_point_line(vector3d &v1,
						const float &x, const float &y, const float &z,
						const float &px, const float &py, const float &pz);

float dist_point_line_nosqr(vector3d &v1,
							const float &x, const float &y, const float &z,
							const float &px, const float &py, const float &pz);

float dist_two_points_nosqr(const float &x1, const float &y1, const float &z1,
							const float &x2, const float &y2, const float &z2);

float dist_two_points(	const float &x1, const float &y1, const float &z1,
						const float &x2, const float &y2, const float &z2);

vector3d crossproduct(const vector3d &a, const vector3d &b);
float dotproduct(const vector3d &a, const vector3d &b);


#endif
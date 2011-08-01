#ifndef MATTER_H
#define MATTER_H

#include "vector3d.hpp"
#include <list>
using namespace std;

int log2(unsigned long v);  	// not really a log function
								// this is returns an int as you can see
								// and does not error for v<=0
class matter
{
	float _x, _y, _z, _mass, _radius;
	vector3d _velocity;
public:
	inline matter(){_x=_y=_z=_mass=0;_velocity=vector3d(0,0,0);}
	matter(float x, float y, float z, float mass, vector3d v);
	matter(float x, float y, float z, float mass);
	inline float x() const {return _x;}
	inline float y() const {return _y;}
	inline float z() const {return _z;}
	inline float mass() const {return _mass;}
	inline float radius() const{return _radius;}
	inline vector3d velocity() const {return _velocity;}
	
	bool values(float &posx, float &posy, float &posz, float &mass);
	
	inline float x(float v){ return _x=v;}
	inline float y(float v){ return _y=v;}
	inline float z(float v){ return _z=v;}
	inline float mass(float v){_radius=pow(v,0.333);return _mass=v;}
	inline vector3d velocity(vector3d v){return _velocity=v;}
	inline void	move(float xx, float yy, float zz){x(xx);y(yy);z(zz);}
	
	void move();
	void apply_force(const vector3d &f,float time);
	bool static gravityattract(matter *m1, matter *m2);
};

#endif
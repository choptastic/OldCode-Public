
#include "matter.hpp"

void matter::apply_force(const vector3d &force, float time)
{
	if(_mass)
		_velocity+=force*(time/_mass);
}

matter::matter(float x, float y, float z, float mass)
{
	_x=x;
	_y=y;
	_z=z;
	_mass=mass;
	_velocity=vector3d(0,0,0);
	_radius = pow(_mass,0.333);
}

matter::matter(float x, float y, float z, float mass, vector3d v)
{
	_x=x;
	_y=y;
	_z=z;
	_mass=mass;
	_velocity=v;
	_radius = pow(_mass,0.333);
}

bool matter::values(float &posx, float &posy, float &posz, float &mass)
{
	posx=_x;
	posy=_y;
	posz=_z;
	mass=_mass;
	return true;
}

int log2(unsigned long v)
{
	int count=0;
	while(v>>=1)
		++count;
	return count;
}

bool matter::gravityattract(matter *m1, matter *m2)
{
	float d,f;
	vector3d F;
	vector3d dir(m1->x() - m2->x(), m1->y() - m2->y(), m1->z() - m2->z());
	d=dir.mag_nosqr();
	f = m1->mass() * m2->mass() / d;
	F=dir.unit_vector()*f;
	if(dir.magnitude()<m1->radius() + m2->radius())  // if too close
		return true;								// tell universe to collide the two
	m2->apply_force(F,0.05f);
	m1->apply_force(F.opposite(),0.05f);
	return false;
}

void matter::move()
{
	_x+=_velocity.getx();
	_y+=_velocity.gety();
	_z+=_velocity.getz();
}
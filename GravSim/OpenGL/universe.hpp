//universe.h
#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <list>
#include "matter.hpp"

using namespace std;

struct universemetrics
{
	float mass,largest, maxx, maxy, maxz, minx, miny, minz;
	list<matter>::iterator _largest;
};

class explosionparticle
{
	float _x,_y,_z, _timeleft;
	vector3d dir;
public:
	inline explosionparticle(){_x=_y=_z=_timeleft=0;}
	void move();
	inline float x(){return _x;}
	inline float y(){return _y;}
	inline float z(){return _z;}
	//inline float timeleft(){return _timeleft;}
	inline vector3d direction(){return dir;}
	inline void x(float v){_x=v;}
	inline void y(float v){_y=v;}
	inline void z(float v){_z=v;}
	inline void timeleft(float v){_timeleft=v;}
	inline void direction(vector3d newdir){dir=newdir;}
	inline bool dead(){return(_timeleft<=0);}
};

class universe
{
	list<matter>::iterator i,j,k;
	list<explosionparticle>::iterator e;
	
	struct universemetrics building, done;
	list <matter> _matter;
	list <explosionparticle> exp;
	bool attracting, explosions;
	bool paused;
	long int iterations;
public:

	inline universe(){_matter.clear();i=j=k=done._largest=_matter.begin();attracting=true;explosions=false;paused=0;iterations=0;}
	universe(long seed, unsigned long size);
	void addparticle(float posx, float posy, float posz, float mass,vector3d v);
	void addparticle(float posx, float posy, float posz, float mass);	
	void pausetoggle();
	inline list<matter>::iterator getfirst(){return _matter.begin();}
	inline list<matter>::iterator getlast(){return _matter.end();}

	inline list<explosionparticle>::iterator getexplodelast(){return exp.end();}
	inline list<explosionparticle>::iterator getexplodefirst(){return exp.begin();}
	
	inline float getmass(){return done.mass;}
	inline float getlargest(){return done.largest;}
	inline float getsizex(){return done.maxx - done.minx;}
	inline float getsizey(){return done.maxy - done.miny;}
	inline float getsizez(){return done.maxz - done.minz;}
	inline float getdensity(){return (getmass()/(getsizex()*getsizey()*getsizez()));};
	inline long int getiterations(){return iterations;}
	inline float getnum(){return _matter.size();}
	inline list<matter>::iterator getlargestmatter(){return done._largest;}

	void createexplosion(float x, float y, float z,int magnitude);
	
	void universe::setdonemetrics();
	void collide();  //collides i and j

	bool processnext();
	bool movenext();
	void attractnext();

};


float max(const float &a, const float &b);
float min(const float &a, const float &b);


#endif
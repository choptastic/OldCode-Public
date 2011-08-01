#ifndef THREED_H
#define THREED_H

#define FOREWARD	1
#define BACKWARD	2
#define LEFT		3
#define RIGHT		4

#include "vector3d.hpp"

class pov
{
	float locx,locy,locz;
	float horiz_rot, vert_rot;
	int lastdir;
	float _speed;
public:
	inline pov(){reset();}
	void moveforeward();
	void movebackward();
	void moveleft();
	void moveright();
	void moveup();
	void movedown();

	float horiz(){return horiz_rot;}
	float vert(){return vert_rot;}
	
	void turnleft(float);
	void turnright(float);
	void turnup(float);
	void turndown(float);

	void changespeed(int val);

	inline float speed(){return _speed;}
	inline float x(){return locx;}
	inline float y(){return locy;}
	inline float z(){return locz;}
	inline void reset(){locx=locy=locz=0;_speed=5;}
	
	//void lookpoints(float &px, float &py, float &pz);
	//inline vector3d dir(){return vector3d(dirx, diry, dirz);}
	//inline vector3d up(){return vector3d(upx, upy, upz);}

	void lookabsolute(float, float, float);
	void moveabsolute(float, float, float);

};

#endif
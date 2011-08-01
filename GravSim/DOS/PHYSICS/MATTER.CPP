#ifndef MATTER_H
#define MATTER_H



#include "3d.cpp"
#include "vector3d.cpp"
#include <graph.h>

const int NUMPICS=11;
image pic[NUMPICS];

const float G=.1;
//int collisions=0;
//int collision_distance=;

const int XLOC=0;
const int YLOC=1;
const int ZLOC=2;
const int MLOC=3;
const int VXLOC=4;
const int VYLOC=5;
const int VZLOC=6;

const int OFF=0;
const int SCRN=1;
const int ALL=2;

int log2(unsigned long v);  	// not really a log function
										// this is returns an int as you can see
										// and does not error for v<=0


class matter
{
	long amount;
	long index[2];
	XMS data;
	float singledata[14];
	int handle;
	int recordmode;


	char whichpic();

	public:

	matter(long amt);
	matter(long amt, int rmode, char* file);

	void setsingle(int i,float x, float y, float z, float mass, vector_3d velocity);
	float x(int w);
	float y(int w);
	float z(int w);
	float mass(int w);
	vector_3d velocity(int w);
	inline long amt(){return amount;}

	float setx(int w, float v);
	float sety(int w, float v);
	float setz(int w, float v);
	float setmass(int w, float v);
	vector_3d setvelocity(int w, vector_3d v);

	void prepare(int w, long i);
	void store(int w);

	void apply_force(vector_3d f,float time, int w);
	void gravity_attract();

	void destroy(int w);
	void collide();

	void move_and_draw();
};


char matter::whichpic()
{
	return log2(singledata[MLOC]) >> 1;
}

matter::matter(long amt)
{
	if(28*amt>XMS::largest())
	{
		cout << "\nError: not enough memory\n";
		exit(1);
	}
	else
	{
		amount=amt;
		data.resize(28*amt);
	}
}

matter::matter(long amt, int rmode, char* file)
{
	matter(amt);
	recordmode=rmode;
	handle=open(file,O_CREAT|O_TRUNC|O_BINARY);
}

void matter::setsingle(int i, float x, float y, float z, float mass, vector_3d velocity)
{
	index[0]=i;
	singledata[XLOC]=x;
	singledata[YLOC]=y;
	singledata[ZLOC]=z;
	singledata[MLOC]=mass;
	singledata[VXLOC]=velocity.x;
	singledata[VYLOC]=velocity.y;
	singledata[VZLOC]=velocity.z;
	store(0);
}

float matter::x(int w)
{return singledata[(w*7)+XLOC];}

float matter::y(int w)
{return singledata[(w*7)+YLOC];}

float matter::z(int w)
{return singledata[(w*7)+ZLOC];}

float matter::mass(int w)
{return singledata[(w*7)+MLOC];}


vector_3d matter::velocity(int w)
{
	int i=w*7+VXLOC;
	return vector_3d(singledata[i],singledata[i+1],singledata[i+2]);
}


float matter::setx(int w, float v)
{return singledata[(w*7)+XLOC]=v;}

float matter::sety(int w, float v)
{return singledata[(w*7)+YLOC]=v;}

float matter::setz(int w, float v)
{return singledata[(w*7)+ZLOC]=v;}

float matter::setmass(int w, float v)
{return singledata[(w*7)+MLOC]=v;}


vector_3d matter::setvelocity(int w, vector_3d v)
{
	int i=w*7+VXLOC;
	singledata[i]=v.x;
	singledata[i+1]=v.y;
	singledata[i+2]=v.z;
	i+=VXLOC;
	return vector_3d(singledata[i],singledata[i+1],singledata[i+2]);
}



void matter::prepare(int w, long i)
{
	index[w]=i;
	XMS::copy(&singledata[7*w],data[i*28],28);
}

void matter::store(int w)
{
	XMS::copy(data[index[w]*28],&singledata[7*w],28);
}


void matter::apply_force(vector_3d force, float time, int w)
{
	if(mass(w)<=0) return;
	setvelocity(w,velocity(w)+force*(time/mass(w)));
}


void matter::gravity_attract()
{
	if(mass(0)<=0 || mass(1)<=0) return;
	int collision_distance=1000;//long(mass(0)+mass(1))>>6;
	//if(collision_distance<=100) collision_distance=100;

	vector_3d force=points(x(0),y(0),z(0),x(1),y(1),z(1));
	float dist=force.mag_nosqr();

	if(dist<=collision_distance)
	{
		collide();
		return;
	}

	else if(	dist<(velocity(0)).mag_nosqr() &&
				dist_point_line_nosqr(velocity(0),x(0),y(0),z(0),x(1),y(1),z(1))<=collision_distance)
	{
		collide();
		return;
	}

	force/=sqrt(dist);  // instead of using unit_vector() saves time
	float strength=(G*mass(0)*mass(1))/(dist);
	force*=strength;
	apply_force(force,1,0);
	force*=-1;
	apply_force(force,1,1);
}


void matter::destroy(int w)
{
	amount--;
	if(index[w]<(amount))
		XMS::copy(data[28*index[w]],data[28*(amount)],28);
	setsingle(amount,0,0,0,0,vector_3d(0,0,0));

}


void matter::collide()
{
	float totalmass=mass(0)+mass(1);
	if(mass(0)>mass(1))
	{
		setvelocity(0,(mass(0)*velocity(0)+mass(1)*velocity(1))/totalmass);
		setmass(0,totalmass);
		store(0);
		destroy(1);
	}
	else
	{
		setvelocity(1,(mass(0)*velocity(0)+mass(1)*velocity(1))/totalmass);
		setmass(1,totalmass);
		store(1);
		destroy(0);
	}
}



void matter::move_and_draw()
{
	//char picnum=0;

	for(long loop=0;loop<amount;loop++)
	{
		prepare(0,(loop));
		vector_3d v=velocity(0);
		setx(0,x(0)+v.x);
		sety(0,y(0)+v.y);
		setz(0,z(0)+v.z);
		//picnum=whichpic();
		//if(picnum>=NUMPICS) picnum=NUMPICS-1;
		dr_point_p(x(0),y(0),z(0)/*,pic[picnum]*/);
		store(0);
	}
}


int log2(unsigned long v)
{
	int count=0;
	while(v>>=1)
		count++;
	return count;
}


#endif
// universe class


#include "universe.hpp"

	
void explosionparticle::move()
{
	_x += dir.getx();
	_y += dir.gety();
	_z += dir.getz();
	_timeleft--;
}


void universe::createexplosion(float x, float y, float z, int magnitude)
{
	if(magnitude<=0)
		magnitude=16;
	int numparticles=(int)sqrt(magnitude);
	int maxtimeleft=(int)sqrt(sqrt(magnitude));
	numparticles=max(numparticles,25);
	maxtimeleft=max(maxtimeleft, 10);
	float maxvelocity = sqrt(sqrt(magnitude));
	explosionparticle temp;
	vector3d v;
	temp.x(x);
	temp.y(y);
	temp.z(z);
	for(int i=0;i<numparticles;++i)
	{
		temp.timeleft(rand()%maxtimeleft);
		v.setx(((rand()%((int)maxvelocity*1000))/1000.0)-(maxvelocity/2));
		v.sety(((rand()%((int)maxvelocity*1000))/1000.0)-(maxvelocity/2));
		v.setz(((rand()%((int)maxvelocity*1000))/1000.0)-(maxvelocity/2));
		temp.direction(v);
		exp.push_back(temp);
	}
}


void universe::addparticle(float posx, float posy, float posz, float mass)
{
	_matter.push_back(matter(posx,posy,posz,mass));
}

void universe::addparticle(float posx, float posy, float posz, float mass, vector3d v)
{
	_matter.push_back(matter(posx,posy,posz,mass,v));
	//cout << "(" << posx << "," << posy << "," << posz << ")" << endl;
}

void universe::pausetoggle()
{
	paused=!paused;
	cout << "Pause : " << paused << endl;
}

void universe::attractnext()
{
	if(i==_matter.end())
	{
		if(++j==_matter.end())
		{
			attracting=false;
			j=_matter.begin();
		}
		i=j;
	}
	++i;
	if(matter::gravityattract(&(*i),&(*j)))
		collide();
	
}

void universe::setdonemetrics()
{
	done.maxx = building.maxx;
	done.minx = building.minx;
	done.maxy = building.maxy;
	done.miny = building.miny;
	done.maxz = building.maxz;
	done.minz = building.minz;
	done.mass = building.mass;
	done.largest = building.largest;
	done._largest = building._largest;
	
	building.maxx = 0;
	building.minx = 0;
	building.maxy = 0;
	building.miny = 0;
	building.maxz = 0;
	building.minz = 0;
	building.mass = 0;
	building._largest = _matter.begin();
	building.largest = 0;
}

bool universe::movenext()
{
	if(explosions)
	{
		if(exp.size()>0)
		{
			if(e==exp.end())
			{
				explosions=false;
				attracting=true;
				return true;
			}
			e->move();
			++e;
			if(e!=exp.end())
				if(e->dead())
					e=exp.erase(e);
		}
		else
		{
			explosions=false;
			attracting=true;
			exp.begin();
			return true;
		}
	}
	else
	{
	
		if(k==_matter.end())
		{	
			k=_matter.begin();
			e=exp.begin();
			explosions=true;
			iterations++;
			setdonemetrics();
			//attracting=true; //enable if NOT using explosions
			//return true; //enable if NOT using explosions
			return false; //enable if using explosions
		}
		
		k->move();
		building.maxx = max(building.maxx, k->x());
		building.minx = min(building.minx, k->x());
		building.maxy = max(building.maxy, k->y());
		building.miny = min(building.miny, k->y());
		building.maxz = max(building.maxz, k->z());
		building.minz = min(building.minz, k->z());
		building.mass += k->mass();
		if(k->mass()>building.largest)
		{
			building._largest = k;
			building.largest = k->mass();
		}
		//building.largest = max(building.largest,k->mass());

		++k;
	
	}
	return false;
}

bool universe::processnext()
{
	if(paused)
		return true;

	if(attracting)
	{
		attractnext();
		return false;
	}
	else
	{
		return movenext();
	}
}
	

void universe::collide()
{
	vector3d p1, p2;
	p1=i->velocity()*i->mass();
	p2=j->velocity()*j->mass();
	int collisionmag=(int)min(p1.magnitude(),p2.magnitude());
	float newmass;
	vector3d newvector;
	newmass = i->mass()+j->mass();
	newvector = (p1 + p2)/newmass;
	j->mass(newmass);
	j->velocity(newvector);
	i=_matter.erase(i);
	//cout << "Collision\n";
	createexplosion(i->x(),i->y(),i->z(),collisionmag);
}



float max(const float &a, const float &b)
{
	if(a>b)	return a;
	else	return b;
}

float min(const float &a, const float &b)
{
	if(a<b)	return a;
	else	return b;
}

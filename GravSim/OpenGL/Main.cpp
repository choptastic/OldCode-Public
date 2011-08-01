
//#include<windows.h>
#include <gl\glut.h>

#include "universe.hpp"
#include "3d.hpp"

#include <iostream.h>
#include <stdlib.h>

using namespace std;

universe u;

float locx=0, locy=0, locz=-250.0f;
int rightmousestatus=GLUT_UP;
float ox, oy;
pov eye;
bool pointsonly=0;

struct point
{
	float x, y, z;
};

float randomcoord(long size)
{
	long random = rand()*rand();
	long temp;
	temp = (random)%size;
	temp-= (size/2);
	float start=(float)temp;
	float denom= (float)(rand()%1000)/1000.0;
	//cout << start+denom << endl;
	return start + denom;
}

void MassColor(float mass, float &r, float &g, float &b)
{
	unsigned long lmass;
	if(mass>(0xFFFFFFFF))
		lmass=32;
	else
		lmass=log2((unsigned long)mass);
	
	switch(lmass)
	{
		case 1:	r=0.1;break;
		case 2:	r=0.2;break;
		case 3:	r=0.3;break;
		case 4:	r=0.4;break;
		case 5: r=0.5;break;
		case 6: r=0.6;break;
		case 7: r=0.7;break;
		case 8: r=0.8;break;
		case 9: r=0.9;break;
		case 10:r=1.0;break;		//Kilo
		case 11:r=1.0;g=0.1;break;
		case 12:r=1.0;g=0.2;break;
		case 13:r=1.0;g=0.3;break;
		case 14:r=1.0;g=0.4;break;
		case 15:r=1.0;g=0.5;break;
		case 16:r=1.0;g=0.6;break;
		case 17:r=1.0;g=0.7;break;
		case 18:r=1.0;g=0.8;break;
		case 19:r=1.0;g=0.9;break;
		case 20:r=1.0;g=1.0;break;	//mega
		case 21:r=1.0;g=1.0;b=0.1;break;	
		case 22:r=1.0;g=1.0;b=0.2;break;
		case 23:r=1.0;g=1.0;b=0.3;break;
		case 24:r=1.0;g=1.0;b=0.4;break;
		case 25:r=1.0;g=1.0;b=0.5;break;
		case 26:r=1.0;g=1.0;b=0.6;break;
		case 27:r=1.0;g=1.0;b=0.7;break;
		case 28:r=1.0;g=1.0;b=0.8;break;
		case 29:r=1.0;g=1.0;b=0.9;break;
		case 30:
		case 31:
		case 32:r=1.0;g=1.0;b=1.0;break;
	}	
	//r=g=b=1;
}

void help()
{
	cout << "GravSim Key Maps\n";
	cout	<< "-=Movement=-\n"
			<< "Up Arrow = Foreward\n"
			<< "Down Arrow = Backward\n"
			<< "Left Arrow = Move Left\n"
			<< "Right Arrow = Move Right\n"
			<< "Right Mouse Button = Looking Direction\n"
			<< "G = Go to Coordinates\n"
			<< "B = Go to Largest Object\n\n"
			<< "-=Other Commands=-\n"
			<< "U = Universe Information (Mass, Size, Density, etc...)\n"
			<< "F1 = Go to Origin\n"
			<< "H = This Help\n"
			<< "P = Pause/UnPause Gravity and Movement\n"
			<< "I = Toggle Polygons\n" << endl;
}

	
void calculateeye()
{
	glLoadIdentity();
	glRotatef(eye.vert(),1,0,0);
	glRotatef(eye.horiz(), 0,1,0);
	glTranslatef(eye.x(), eye.y(), eye.z());	
}

void DrawParticle(float x, float y, float z, float mass)
{
	float r,g,b;
	
	struct point top, bot, p1, p2, p3, p4;
	float factor;

	MassColor(mass,r,b,g);
	factor = pow(mass,0.333);
	glColor3f(r,b,g);

	top.x=x;
	top.y=y+(factor+factor);
	top.z=z;
	
	bot.x=x;
	bot.y=y-(factor+factor);
	bot.z=z;

	p1.x=x+factor;
	p1.y=y;
	p1.z=z+factor;

	p2.x=x-factor;
	p2.y=y;
	p2.z=z+factor;

	p3.x=x-factor;
	p3.y=y;
	p3.z=z-factor;

	p4.x=x+factor;
	p4.y=y;
	p4.z=z-factor;

	glVertex3f(top.x, top.y, top.z);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);

	glVertex3f(top.x, top.y, top.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);

	glVertex3f(top.x, top.y, top.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);

	glVertex3f(top.x, top.y, top.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p1.x, p1.y, p1.z);


	glVertex3f(bot.x, bot.y, bot.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glVertex3f(p3.x, p3.y, p3.z);

	glVertex3f(bot.x, bot.y, bot.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p2.x, p2.y, p2.z);

	glVertex3f(bot.x, bot.y, bot.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p1.x, p1.y, p1.z);

	glVertex3f(bot.x, bot.y, bot.z);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p4.x, p4.y, p4.z);

	//glVertex3f(x,y,z);
}

void DrawPoint(float x, float y, float z, float mass)
{
	float r,g,b;
	MassColor(mass,r,b,g);
	glColor3f(r,b,g);
	glVertex3f(x,y,z);
}

void DrawExplosionParticle(float x, float y, float z)
{
	glVertex3f(x,y,z);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	list<matter>::iterator m,l;
	list<explosionparticle>::iterator em, el;

	calculateeye();
	
	l=u.getlast();
	if(!pointsonly)
	{
		m=u.getfirst();
		glBegin(GL_TRIANGLES);
		while(m != l)
		{
			DrawParticle(m->x(),m->y(),m->z(),m->mass());
			++m;
		}
		glEnd();
	}

	m=u.getfirst();
	glBegin(GL_POINTS);
	while(m != l)
	{
		DrawPoint(m->x(),m->y(),m->z(),m->mass());
		++m;
	}
	glColor3f(1.0,1.0,1.0);
	el=u.getexplodelast();
	em=u.getexplodefirst();
	while(em != el)
	{
		DrawExplosionParticle(em->x(), em->y(), em->z());
		++em;
	}
	glEnd();
	glutSwapBuffers();
}


void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);		

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	
}

void SpecialKeys(int key, int x, int y)
{
	switch(key)
	{
		case(GLUT_KEY_UP):		eye.moveforeward();break;
		case(GLUT_KEY_DOWN):	eye.movebackward();break;
		case(GLUT_KEY_LEFT):	eye.moveleft();break;
		case(GLUT_KEY_RIGHT):	eye.moveright();break;
		case(GLUT_KEY_PAGE_UP):	eye.changespeed(+1);break;
		case(GLUT_KEY_PAGE_DOWN):eye.changespeed(-1);break;
	}
	glutPostRedisplay();
}


void ChangeSize(int w, int h)
	{
	GLfloat fAspect;

	if(h == 0)
		h = 1;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    fAspect = (float)w/(float)h;
    gluPerspective(45.0, fAspect, 1.0, 1000000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Motion(int x, int y) 
{
	if(rightmousestatus == GLUT_DOWN)
	{
		eye.turnright(ox-x);
		ox=x;
		eye.turnup(oy-y);
		oy=y;
		glutPostRedisplay();
	}
}

void Mouse(int button, int state, int x, int y)
{
	if(button==GLUT_RIGHT_BUTTON)
	{
		rightmousestatus = state;
		ox=x;
		oy=y;
	}
}



void UniverseInfo()
{
	cout	<< "Universe Info After " << u.getiterations() << " iterations : \n"
			<< "Number of Objects   : " << u.getnum() << endl
			<< "Mass                : " << u.getmass() << endl
			<< "Density             : " << u.getdensity() << endl
			<< "Largest Object Mass : " << u.getlargest() << endl
			<< "Size X              : " << u.getsizex() << endl
			<< "Size Y              : " << u.getsizey() << endl
			<< "Size Z              : " << u.getsizez() << endl;
}

	

void IdleFunction()
{
	if(u.processnext())
		RenderScene();
}

void getnewcoords()
{
	char inval[20];
	float x,y,z;
	cout << "-=Go To New Location=-" << endl;

	cout << "Enter New X Coordinate : ";
	cin >> inval;
	x=atof(inval);
	cout << "Using " << x << endl;
	cout << "Enter New Y Cooordinate : ";
	cin >> inval;
	y=atof(inval);
	cout << "Using " << y << endl;
	cout << " Enter New Z Coordinate : ";
	cin >> inval;
	z=atof(inval);
	cout << "Using " << z << endl;
	eye.moveabsolute(x,y,z);
}

void gotobiggest()
{
	list<matter>::iterator big=u.getlargestmatter();
	eye.moveabsolute(big->x(),-big->y(),big->z());
	cout << "New Position : (" << big->x() << "," << big->y() << "," << big->z() << ")" << endl;
}


void KeyFunc(unsigned char key, int x, int y)
{
	switch(toupper(key))
	{
		case('U'):UniverseInfo();break;
		case('H'):help();break;
		case('O'):eye.reset();break;
		case('P'):u.pausetoggle();break;
		case('I'):cout << "Points Only : " << (pointsonly=!pointsonly) << endl;break;
		case('G'):getnewcoords();break;
		case('C'):u.createexplosion(0,0,0,10000);break;
		case('B'):gotobiggest();break;
		case('A'):eye.moveup();break;
		case('Z'):eye.movedown();break;
	}	
	glutPostRedisplay();
}

int getinput(const char *prompt, bool zerook)
{
	int val=0;
	char inputval[255];
	do
	{
		cout << prompt;
		cin >> inputval;
		val=atoi(inputval);
		if(val<=0 && !zerook)
			cout << "Must be a number greater than 0" << endl;
		else
			cout << "Using " << val << endl;
	}while(val<=0 && !zerook);
	return val;
}

int main(int argc, char* argv[])
{
	long size=0, mass=0, vel=0, num=0, seed=0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GravSim v0.2");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyFunc);
	glutMotionFunc(Motion);
	glutIdleFunc(IdleFunction);
	SetupRC();
	

	cout << "-=GravSim v0.2 by Jesse Gumm=-\n";
	cout << "Press the [H] Key during the demo for help on controls\n";
	
	num=	getinput("Number of Particles   : ",false);
	size=	getinput("Size of Universe      : ",false);
	mass=	getinput("Max Mass              : ",false);
	vel=	getinput("Max Starting Velocity : ",true);
	seed=	getinput("Enter Random Seed     : ",true);
	srand(seed);

	for(int i=0;i<num;i++)
		if(vel>0)
			u.addparticle	(	randomcoord(size),
								randomcoord(size),
								randomcoord(size),
								(rand()*rand())%mass,
								vector3d(	rand()%vel-(vel/2),
											rand()%vel-(vel/2),
											rand()%vel-(vel/2)
										)
							);
		else
			u.addparticle	(	randomcoord(size),
								randomcoord(size),
								randomcoord(size),
								(rand()*rand())%mass
							);

	glutMainLoop();
	return 0;
}

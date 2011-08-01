//#include <iostream.h>
#include <ctype.h>
#include <conio.h>
#include "3d.cpp"
#include "vector3d.cpp"
#include "matter.cpp"
#include <bios.h>
#include <dos.h>
#include <stdlib.h>
#include <graph.h>
#include <dir.h>


const float version=0.2;

void message(char* msg)
{
	gotoxy(1,1);
	cout << msg;
	delay(1000);
	//getch();
}


void help()
{
	cout << "Help";

}


int unsigned speed=8;
int recordmode;
int rhandle;


void main()
{
	chdir("c:\\cpp\\physics");
	// set up pictures declared in matter.cpp
	pic[0].load("sr.pcx");
	pic[1].load("mr.pcx");
	pic[2].load("br.pcx");
	pic[3].load("sa.pcx");
	pic[4].load("ma.pcx");
	pic[5].load("ba.pcx");
	pic[6].load("vsp.pcx");
	pic[7].load("sp.pcx");
	pic[8].load("mp.pcx");
	pic[9].load("bp.pcx");
	pic[10].load("ss.pcx");
	// prepare pictures for display
	for(int loadloop=0;loadloop<NUMPICS;loadloop++)
		pic[loadloop].prepare();

	long xrange,yrange,zrange,mrange,MAX;
	char recordfile[50];
	long i,loop;
	char key; // i and loop are loops...key is keypressed

	//getting values
	cout << "Number of particles: ";
	cin >> MAX;
	cout << "X range: ";
	cin >> xrange;
	cout << "Y range: ";
	cin >> yrange;
	cout << "Z range: ";
	cin >> zrange;
	cout << "Mass Range: ";
	cin >> mrange;
	/*
	cout << "Record filename (nothing to cancel record mode): ";
	cin >> recordfile;
	if(recordfile=="") recordmode=0;
	else
	{
		recordmode=1;
		rhandle=open(recordfile,O_CREAT|_BINARY|O_TRUNC,S_IREAD|S_IWRITE);
	}
	*/



	randomize();  		  	// randomize for locations
	matter dots(MAX);  	// allocate space in XMS for all the particles

	// this creates all the particles in XMS
	for(i=0;i<dots.amt();i++)
	{
		// set up a single particle
		dots.setsingle(i,random(xrange),random(yrange),random(zrange),
							random(mrange)+1,vector_3d(0,0,0));
	}



	initgraph();      // initialize graphics mode 13h
	pic[0].load_pal();// set pallette... all palletes
							// for all images are same
	set_virt();       // setup for virtual screen

	i=0; 					// start loop at 0
	while(key!=27) 	// while ESC is not pressed
	{
		while(!bioskey(1)) // while no key is pressed
		{
			dots.prepare(0,i);  // prepare matter '0' for comaprison
			if(dots.mass(0) <=0) dots.destroy(0); // if mass=0, remove from
										// memory otherwise continue with loop
										// please not that although the
										// function gravity_attract() has
										// a mass check in it, this saves
										// time because then the loop
										// below is not run
			else
			{
				// this loop starts at i+1 so that i
				// is never comapred to itself, speeding
				// up the process but is even more important
				// because if an element is compared to itself
				// it would destroy itself
				for(loop=i+1;loop<dots.amt();loop++)
				{
					dots.prepare(1,loop); 	// prepare matter '1' or comaprison
					dots.gravity_attract(); // attract particle '1' to '0'
					dots.store(1);          // store particle '1' into XMS
				}
				dots.store(0);             // storeparticle '0' into XMS
			}
													// clear screen
			setback(0);                   // draw all particles
			dots.move_and_draw();         // copy virtual screen to VGA memory
			draw_virt();
			gotoxy(1,1);
			cout << dots.amt();

			if(i<dots.amt()-1) i++;       // loop
			else
				i=0;

		}
		while(bioskey(1))
		{
			key=toupper(getch());         // get keypress and uppercase it
		}
			// get orthagonal vector to the view vector
			vector_3d orth=crossproduct(view,vector_3d(0,1,0));
			float max_found;
			int s;
			switch(key)
			{
				case('8'): 	OZ+=view.z*speed;  // foreward
								OX+=view.x*speed;
								OY+=view.y*speed;
								break;
				case('5'):	OZ-=view.z*speed;  // backward
								OX-=view.x*speed;
								OY-=view.y*speed;
								break;
				case('4'):	view.turnxz(.05);  // left
								break;
				case('6'):	view.turnxz(-.05); // right
								break;

				case('1'):  OX+=orth.x*speed;  // strafe left
								OY+=orth.y*speed;
								OZ+=orth.z*speed;
								break;
				case('3'):  OX-=orth.x*speed;  // strafe right
								OY-=orth.y*speed;
								OZ-=orth.z*speed;
								break;
				case('A'):	OY+=speed;         // up
								break;
				case('Z'):	OY-=speed;         // down
								break;
				case('B'):  max_found=3.4*pow10(38);  // find largest particle

				case('C'):  int found;         // find next largest particle
								float mass_found=0;
								for(int find=0;find<MAX;find++)
								{
									dots.prepare(0,find);

									if(dots.mass(0)>mass_found && dots.mass(0)<max_found)
									{
										found=find;
										mass_found=dots.mass(0);
									}
								}
								dots.prepare(0,found);
								max_found=mass_found;
								view.x=dots.velocity(0).x;
								view.z=dots.velocity(0).z;
								view.unit_vector();
								OX=dots.x(0)-view.x*25;
								OY=dots.y(0)-view.y*25;
								OZ=dots.z(0)-view.z*25;

								break;
				case('_'):
				case('-'):	if(speed>1)speed>>1;
								break;
				case('+'):
				case('='):	if(speed<(65535/2)) speed<<1;
								break;
				case('?'):
				case('H'):	help();

			}

		}
		endgraph();    // end graphics mode 13h
}


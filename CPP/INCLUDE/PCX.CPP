#ifndef _PCX
#define _PCX


#include<conio.h>
#include<iostream.h>

#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <alloc.h>
#include <xms\xms.h>


XMS pixels;
int psize=0;

void swap(int &x, int &y);
int binaryread_int(int handle, int location);
byte binaryread_byte(int handle, int location);
int decode(byte b, int& times);



class image
{
	int xsize,ysize;
	long XMSloc;
	byte *loc;
	byte prepared;
	byte* filename;


	public:

	void load_pal();
	image();
	image(char *fn);
	~image();
	void load(char* fn);
	void draw(int x, int y) const;
	void drawscale(int x, int y, float scale) const;
	void prepare();
	void unprepare();
	int sizey() const;
	int sizex() const ;
	//inline long xmsloc(){return XMSloc;}
	//byte* far copy_to(int x1, int y1, int x2, int y2, byte far *rlocation);

};

image::image():prepared(0) {filename=(char*)malloc(50);}

/*
byte far *image::copy_to(int x1, int y1, int x2, int y2, byte far *rlocation)
{
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
	int 	sizex=x2-x1+1,sizey=y2-y1+1,loop;
	byte *imgloc=loc+4+(y1*xsize)+x1;

	delete rlocation;
	rlocation=(byte far*)malloc((sizex)*(sizey));
	byte *location=rlocation;
	memcpy(location,&sizex,2);
	memcpy(location+2,&sizey,2);
	location+=4;
	if(prepared==1)
	{
		for(loop=y1;loop<=y2;loop++)
		{
			memcpy(location,imgloc,sizex);
			imgloc+=xsize;  //xsize of picture from which we are copying
			location+=sizex; // sizex of picture we are copying to
		}
	}
	return rlocation;
}
*/



void image::load_pal()
{
	int handle=_open(filename,O_RDONLY);
	lseek(handle,-769,SEEK_END);
	byte rgb[3];
	byte is;
	_read(handle,&is,1);
	if(is==12)
	{
		for(int loop=0;loop<256;loop++)
		{
			_read(handle,rgb,3);
			setpal(loop,(rgb[0]/4),(rgb[1]/4),(rgb[2]/4));
		}
	}
	_close(handle);
}


image::~image()
{
	free(loc);
}

void image::prepare()
{
	if(prepared==0)
	{
		loc=(byte*)malloc(xsize*ysize);
		XMS::copy(loc,pixels[XMSloc],xsize*ysize);
		prepared=1;
	}
}



void image::unprepare()
{
	if(prepared==1)
	{
		delete loc;
		prepared=0;
	}
}


int image::sizex() const
{return xsize;}

int image::sizey() const
{return ysize;}

void image::draw(int x, int y) const
{

	if(prepared==1)
	{
		byte* vgaline=VGA+x+(y<<6)+(y<<8);
		byte* tloc=(byte*)loc;            // tloc=temporrary location
		for(int loopy=0;loopy<ysize;loopy++)
		{
			memcpy(vgaline,tloc,xsize);
			tloc+=xsize;
			vgaline+=320;
		}
	}
}

void image::drawscale(int x, int y, float scale) const
{
	if(scale<=0) return;
	scale=1/scale;
	if(prepared==1)
	{
		float fx,fy;
		int ycoord=0;
		int loopxsize=xsize;
		int loopysize=ysize;
		if((xsize/scale)+x>=MAXX) loopxsize=(MAXX-x);
		if((ysize/scale)+y>=MAXY) loopysize=(MAXY-y);
		int vga_offs=x+(y<<6)+(y<<8);


		for(fy=0;fy<loopysize;fy+=scale)
		{
			int xcount=0;
			ycoord=xsize*int(fy);

			for(fx=0;fx<loopxsize;fx+=scale)
			{
				if(loc[fx+ycoord]!=255)
					VGA[vga_offs+xcount]=loc[fx+ycoord];
				xcount++;
			}
			vga_offs+=320;
		}

	}
}


image::image(char* fn)
{
	filename=(char*)malloc(50);
	load(fn);
}



void image::load(char *fn)
{
	prepared=0;
	filename=fn;

	int 	handle,xmin,xmax,ymin,ymax,
			nplanes,bytesperline,totalbytes,
			bytesused=0,position=128,x,y,result,yline;
	int n;
	byte c;
	byte* line;
	handle=_open(filename,O_RDONLY);
	if(handle!=-1)
	{
		c=binaryread_byte(handle,3);
		if(c==8)
		{

			xmin=binaryread_int(handle,4);
			ymin=binaryread_int(handle,6);
			xmax=binaryread_int(handle,8);
			ymax=binaryread_int(handle,10);
			nplanes=binaryread_byte(handle,65);
			bytesperline=binaryread_int(handle,66);

			xsize=xmax-xmin+1;
			ysize=ymax-ymin+1;
			totalbytes=nplanes*bytesperline;

			line=(byte*)malloc(totalbytes);

			XMSloc=psize;
			pixels.resize(psize+=xsize*ysize);

			yline=0;
			for(y=0;y<ysize;y++)
			{
				bytesused=0;
				x=0;
				while(bytesused<totalbytes)
				{
					c=binaryread_byte(handle,position++);
					result=decode(c,n);

					if(result==1)
					{
						c=binaryread_byte(handle,position++);
						for(xmax=x+n;x<xmax;x++)
							line[x]=c;
					}
					else
						line[x++]=c;
					bytesused+=n;
				}
				XMS::copy(pixels[XMSloc+yline],line,xsize);
				yline+=xsize;
			}
		}
	}
}



void swap(int &x, int &y)
{
	int temp=x;
	x=y;
	y=temp;
}



int binaryread_int(int handle, int location)
{
	int *input=(int*)malloc(2);
	lseek(handle,location,0);
	_read(handle,input,2);
	int data=*input;
	delete input;
	return data;
}

byte binaryread_byte(int handle, int location)
{
	byte *input=(byte*)malloc(1);
	lseek(handle,location,0);
	_read(handle,input,1);
	byte data=*input;
	delete input;
	return data;
}

int decode(byte b, int& times)
{
	if((b&0xc0)==0xc0)
	{
		times=(b&0x3f);
		return 1;
	}
	else
	{
		times=1;
		return 0;
	}
}






/*
void main()
{
	char* file="c:\\image2.pcx";
	char* tfile="c:\\cpp\\physics\\vsp.pcx";
	image war2(file);
	image thing(tfile);
	war2.prepare();
	thing.prepare();
	initgraph();

	thing.load_pal();

	set_virt();

	for(float loop=1;loop>.05;loop-=.05)
	{
		setback(0);
		war2.drawscale(0,0,loop);
		delay(100);
		draw_virt();
	}


	thing.draw(100,100);
	draw_virt();


	getch();
	endgraph();
	gotoxy(1,1);
	cout  << "War2 Size: " << war2.sizex()*war2.sizey()
			<< "\nThing Size: " << thing.sizex()*thing.sizey()
			<< "War2 loc: " << war2.xmsloc(
			)
			<< "Thing loc: " << thing.xmsloc()
			<< "\npsize: " << psize
			<< "\nXMSsize" << pixels.size() << endl << endl;
	getch();
}

*/


#endif
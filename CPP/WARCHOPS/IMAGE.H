//#include <alloc.h>
const int normal=0;
const int flipped=1;
const int inverse=2;
const int both=3;

class small_image
{

	public:
	void draw(int x, int y, int dir);
	void load(char *filename);
	private:
	int maxx,maxy;
	char pixel[16][16];
};

void small_image::draw(int x, int y, int dir)
{
	int loopx=0,loopy=0;
	int color;
	if(dir==normal)
	{
		for(loopx=0;loopx<maxx;loopx++)
		{
			for(loopy=0;loopy<maxy;loopy++)
			{
				if(pixel[loopx][loopy]!=16)
				{
					color=pixel[loopx][loopy];
					putpixel(loopx+x,loopy+y,color);
				}
			}
		}
	}
	else if(dir==flipped)
	{
		for(loopx=0;loopx<maxx;loopx++)
		{
			for(loopy=0;loopy<maxy;loopy++)
			{
				if(pixel[loopx][loopy]!=16)
				{
					color=pixel[loopx][loopy];
					putpixel(loopx+x,14-loopy+y,color);
				}
			}
		}
	}
	else if(dir==inverse)
	{
		for(loopx=0;loopx<maxx;loopx++)
		{
			for(loopy=0;loopy<maxy;loopy++)
			{
				if(pixel[loopx][loopy]!=16)
				{
					color=pixel[loopx][loopy];
					putpixel(loopy+x,loopx+y,color);
				}
			}
		}
	}
	else if(dir==both)
	{
		for(loopx=0;loopx<maxx;loopx++)
		{
			for(loopy=0;loopy<maxy;loopy++)
			{
				if(pixel[loopx][loopy]!=16)
				{
					color=pixel[loopx][loopy];
					putpixel(14-loopy+x,loopx+y,color);
				}
			}
		}
	}
}
void small_image::load(char *filename)
{

	char temp;
	int maxxx, maxxy;
	int blah;
	ifstream file;
	file.open(filename);

	file >> temp;
	maxx=temp;
	file >> temp;
	maxy=temp;


	for(int loopx=0;loopx<maxx;loopx++)
	{
			for(int loopy=0;loopy<maxy;loopy++)
			{
				if(loopy<maxy && loopx<maxx)
				{
					file >> temp;
					pixel[loopx][loopy]=temp;
				}
				else file >> blah;
			}
	}
	file.close();

}





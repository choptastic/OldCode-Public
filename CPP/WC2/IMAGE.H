const int normal=0;
const int flipped=1;
const int inverse=2;
const int both=3;

class small_image
{

	public:
	void draw(int x, int y, int dir,int player);
	void load(char *filename);
	private:
	int maxx,maxy;
	char pixel[31][31];
};

void small_image::draw(int x, int y, int dir, int player)
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
					if(color==12) color=player;
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
					if(color==12) color=player;
					putpixel(loopx+x,30-loopy+y,color);
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
					if(color==12) color=player;
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
					if(color==12) color=player;
					putpixel(30-loopy+x,loopx+y,color);
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
					pixel[loopx][loopy]=temp-50;
				}
				else file >> blah;
			}
	}
	file.close();

}





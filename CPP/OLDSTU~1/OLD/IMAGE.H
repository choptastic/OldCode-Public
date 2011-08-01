class new_image
{

	public:
	void draw(int x, int y);
	void load(char *filename);
	private:
	int maxx, maxy;
	char pixel[100][100];
};

void new_image::draw(int x, int y)
{
	int loopx=0,loopy=0;
	int color;
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
void new_image::load(char *filename)
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





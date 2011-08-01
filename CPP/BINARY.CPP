#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<io.h>


class binary_file
{
	char *filename;
	long size;
	long start;
	public:

	binary_file(char*);
	long getsize();
	void out(char*,long);
	void out(long,long);
	void out(double,long);
	void in(char*&,long,long);
	void in(long&,long,long);
	void in(double&,long,long);
}

binary_file::binary_file(char* name)
{
	filename=name;
	long handle=

}

long binary_file::getsize()
{
	return size;
}




void main()
{
	clrscr();
	binary_file in("c:\\cpp\\include\\mode13h\\tester.exe");
	cout << in.getsize();
	getch();


}
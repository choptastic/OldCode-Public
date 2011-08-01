#include<iostream.h>
#include<dos.h>
#include<io.h>
#include<fcntl.h>
#include<iostream.h>
#include<sys\stat.h>

const char* FIX="c:\date.fix";



void main()
{
	cout << endl << "Restoring date . . .";
	date restore;
	int handle=open(FIX,O_RDONLY | O_BINARY,S_IREAD),y,m,d;
	lseek(handle,0,SEEK_SET);


	read(handle,&y,2);
	read(handle,&m,2);
	read(handle,&d,2);

	close(handle);

	restore.da_year=y;
	restore.da_mon=m;
	restore.da_day=d;



	cout  << endl << "Date is now : "
			<< y << "/"
			<< m << "/"
			<< d;

	setdate(&restore);

}
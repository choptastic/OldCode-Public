#include <stdlib.h>
#include <process.h>
#include <dos.h>
#include <conio.h>
#include <iostream.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

const char* FIX="c:\date.fix";
char* RESTORE_LOC="c:\\batch\\restore.exe";


void main(int argsused, char *args[])
{
	if(argsused==5)
	{
		date now,change;
		getdate(&now);
		int y,m,d,handle,year,month,day;

		change.da_year=atoi(args[2]);
		change.da_mon=atoi(args[3]);
		change.da_day=atoi(args[4]);




		cout 	<< endl << "Current date is (Y/M/D): "
				<< now.da_year << "/"
				<< int(now.da_mon) << "/"
				<< int(now.da_day);

		handle=open(FIX,O_CREAT | O_BINARY | O_TRUNC,S_IREAD | S_IWRITE);
		lseek(handle,0,SEEK_SET);

		y=now.da_year;
		m=now.da_mon;
		d=now.da_day;


		write(handle,&y,2);
		write(handle,&m,2);
		write(handle,&d,2);

		close(handle);

		cout 	<< endl << "Changing date to (Y/M/D):"
				<< change.da_year << "/"
				<< int(change.da_mon) << "/"
				<< int(change.da_day);

		setdate(&change);

		cout << endl << "Executing program:        " << args[1];
		execl(args[1],"");

		execl(RESTORE_LOC,"");

	}
	else cout << endl << "Not enough Parameters";
}








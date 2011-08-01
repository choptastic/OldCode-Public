#include <process.h>
#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include <malloc.h>


int length(char* c)
{
	for(int loop=0;c[loop]!=0;loop++);
	return loop;
}


void main()
{
	clrscr();
	cout << "Step 1 of 2...Prepare Startup Diskette\n\n";
	int numlines=2;
	char drive;
	char* dir=(char*)malloc(100);
	char* autofile[150];
	cout << "Loading information . . . ";
	ifstream in("a:\\autoexec.nfo");
	in >> dir;
	in >> drive;
	in.close();
	dir[0]=drive;
	cout << "DONE\n\n";


	cout << "Deleting data file from A: . . . ";
	system("del a:\\autoexec.nfo");
	cout << "DONE\n\n";


	cout << "Loading Autoexec.bat from C: . . . ";
	in.open("c:\\autoexec.bat");
	while(!in.eof())
	{
		autofile[numlines]=(char*)malloc(150);
		in.getline(autofile[numlines],150);
		numlines++;
	}
	in.close();

	// getting rid of empty lines at end of autoexec.bat

	for(int loop=numlines-1;loop>0;loop--)
	{
		if(length(autofile[loop])==0)
			numlines--;
	}

	cout << "DONE\n\n";
	cout << "Writing modified Autoexec.bat on A: . . . ";


	autofile[0]="c:";
	autofile[1]="cd\\";

	ofstream out("a:\\autoexec.bat");
	for(loop=0;loop<numlines-2;loop++)
		out << autofile[loop] << endl;
	out << drive << ":" << endl;
	out << "cd " << dir << endl;
	out << "vendtest" << endl;
	out.close();

	cout << "DONE\n\n";

	numlines=0;

	cout << "Loading config.sys from C: . . . ";
	in.open("c:\\config.sys");
	while(!in.eof())
	{
		autofile[numlines]=(char*)malloc(150);
		in.getline(autofile[numlines],150);
		numlines++;
	}
	in.close();
	cout << "DONE\n\n";

	autofile[numlines++]="DEVICE=C:\\DOS\\HIMEM.SYS /TESTMEM:OFF";
	autofile[numlines++]="DEVICE=C:\\DOS\\EMM386.EXE NOEMS";

	cout << "Writing modified config.sys to A: . . . ";

	out.open("a:\\config.sys");

	for(loop=0;loop<numlines;loop++)
		out << autofile[loop] << endl;
	out.close();
	cout << "DONE\n\n";



	cout << "To proceed to step 2, restart the computer" << endl
			<< "Remember to keep the disk in the drive";
	getch();

}
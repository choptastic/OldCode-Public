// Jesse Gumm
// This Reads the contents and prints them in reverse.
// The lines are assumed to be shorter than 1024 bytes long.



#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <mem.h>

const char filename[]="file.txt";

void printback(FILE *stream);


void main()
{

	puts("Press any key to print file backwards");
	getch();
	FILE *stream;
	stream = fopen(filename,"r");
	printback(stream);
	fclose(stream);
	getch();
}

void printback(FILE *stream)
{
	char* string=(char*)malloc(1023);
	if(fgets(string,1024,stream)==0)
		return;
	//puts(string);
	printback(stream);
	puts(string);
}



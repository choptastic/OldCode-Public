
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


//#include <stdio.h>

char menu(char * filename)
{
	char choice=0;
	do
	{

		puts("1 > Select File\n");
		puts("2 > Display File Content\n");
		puts("3 > Display File Information\n");
		puts("4 > Toggle File Read Permissions\n");
		puts("5 > List Current Directory Content\n");
		puts("6 > Change directory\n");
		puts("7 > Quit\n\n");
		puts("Current Working File:");
		puts("filename\n\n");
		puts("Enter Your Choice:");
		choice=getchar();
		if(choice<'1' || choice > '7')
			puts("Invalid Choice");
	}while(choice<'1' || choice>'7');
	return choice;
}


int main()
{

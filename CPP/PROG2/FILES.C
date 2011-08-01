
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


const int PGSIZE=20;


char menu(char* filename);
void selectfile(char* filename);
void changedirectory(DIR* dir,char* filename);
void copystr(char* dest, char* src);
void content(char* filename);
void fileinfo(char* filename);
void listdir(DIR* dir);

int main()
{

	char choice;
	char *filename="                ";
	DIR *dir;
	filename[0]=0;

	//setbuf(stdin,2);
	do
	{
		choice=menu(filename);
		switch(choice)
		{
			// Select File
			case('1'):
				selectfile(filename);
				break;
			case('2'):
				content(filename);
				break;
			case('3'):
				fileinfo(filename);
				break;
			case('5'):
				listdir(dir);
				break;
			case('6'):
				changedirectory(dir,filename);
				break;

		}
		//flushall();
	}while(choice!='7');
	return 0;

}


//#include <stdio.h>
void selectfile(char* filename)
{
	char *temp="                             ";
	FILE* test;
	printf("Enter Filename:");
	gets(temp);
	test=fopen(temp,"r");
	if(test==0)
		printf("File Not Found; File not changed");
	else
		copystr(filename,temp);
	fclose(test);
}


//#include <stdio.h>
char menu(char * filename)
{
	char *choice=(char*)malloc(100);
	char r;
	do
	{

		printf("1 > Select File\n");
		printf("2 > Display File Content\n");
		printf("3 > Display File Information\n");
		printf("4 > Toggle File Read Permissions\n");
		printf("5 > List Current Directory Content\n");
		printf("6 > Change directory\n");
		printf("7 > Quit\n\n");
		printf("Current Working File:");
		printf(filename);
		printf("\n\nEnter Your Choice:");
		gets(choice);
		free(choice);

		r=choice[0];
		if(r<'1' || r>'7')
			printf("\nInvalid Choice\n\n");
	}while(r<'1' || r>'7');
	return r;
}

//#include <dirent.h>
//#include <sys/tupes.h>
//#include <unistd.h>

#include <dir.h>

void changedirectory(DIR * dir,char* filename)
{
	DIR* test;
	char *temp=(char*)malloc(100);
	printf("\nChange to Directory:");
	gets(temp);
	test=opendir(temp);
	if(test==0)
	{
		printf("Directory not found; Directory not changed\n\n");
		closedir(test);
	}
	else
	{
		closedir(dir);
		dir=test;
		chdir(temp);
		filename[0]=0;
	}
	free(temp);
}


#include <stdio.h>
void content(char* filename)
{
	FILE *file;
	int count=0;
	char* line=(char*)malloc(101);
	if(filename[0]!=0)
	{
		file=fopen(filename,"r");
		while(fgets(line,100,file)!=0)
		{

			printf(line);
			count++;
			if(count>PGSIZE)
			{
				printf("<more>");
				gets(line);
				count=0;
			}
		}
		fclose(file);
		free(line);
	}
	else
		printf("No Working File\n\n");
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void fileinfo(char* filename)
{
	struct stat s;
	char* duh="      ";

	stat(filename,&s);

	printf("Filename: %s\r\n",filename);
	printf("File Size(bytes): %i\r\n",s.st_size);
	printf("Permissions: %i\r\n",s.st_mode);
	printf("Inode: %i\r\n",s.st_ino);

	printf("Link Count: %i\r\n",s.st_nlink);
	printf("Last Access Time: %s\r\n",ctime(&s.st_atime));
	printf("Last Modification Time: %s\r\n",ctime(&s.st_mtime));
	printf("Last I-Node Change: %s\r\n",ctime(&s.st_ctime));
	puts("Press Enter To Return to menu");
	gets(duh);
}

//#include <dirent.h>
//#include <stdio.h>
//#include <sys/types.h>

//void listdir(DIR *dir)
//{



void copystr(char* dest, char* src)
{
	int i=0;
	for(i=0;src[i]!=0;i++)
		dest[i]=src[i];
	dest[i]=0;
}

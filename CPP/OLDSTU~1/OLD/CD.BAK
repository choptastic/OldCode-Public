//#include<gumm is gay.h>
//#include<gumm likes men.h>
#include<include.h>
const int maxlength=20;
const int maxcds=30;


struct cd_type
{
	char title[maxlength+1];
	char artist[maxlength+1];
	char type[maxlength+1];
	int tracks;
	int exist;
}cd[maxcds];


int count(const char a[])
{
	int num=0;
	while(a[num]!='\0')
	{
		num++;
	}
	return num;
}


void display(int index)
{
	cout << "CD index : " << index << endl;
	cout << "CD Title : " << cd[index].title << endl;
	cout << "CD Artist : " << cd[index].artist << endl;
	cout << "CD Description : " << cd[index].type << endl;

}


void load()
{
	ifstream infile;
	infile.open("h:\\cd.dat");
	for(int loop1=0;loop1<maxcds;loop1++)
	{
		for(int loop=0;loop<maxlength;loop++)
		{
			infile >> cd[loop1].title[loop];
			infile >> cd[loop1].artist[loop];
			infile >> cd[loop1].type[loop];
		}
		infile >> cd[loop1].tracks;
		infile >> cd[loop1].exist;
	}


}

void save()
{

	ofstream outfile;
	outfile.open("h:\\cd.dat");
	for(int loop1=0;loop1<maxcds;loop1++)
	{
		for(int loop=0;loop<maxlength;loop++)
		{
			outfile << cd[loop1].title[loop] << endl;
			outfile << cd[loop1].artist[loop] << endl;
			outfile << cd[loop1].type[loop] << endl;
		}
		outfile << cd[loop1].tracks << endl;
		outfile << cd[loop1].exist << endl;
	}
	outfile.close();


}

void addcd()
{
	int index;

	cout << "Index of CD : ";
	cin >> index;
	cin.ignore(100,'\n');

	cout << "Title of CD " << index << " : ";
	cin.get(cd[index].title,maxlength);
	cin.ignore(100,'\n');

	cout << "Artist of CD " << index << " : ";
	cin.get(cd[index].artist,maxlength);
	cin.ignore(100,'\n');

	cout << "Brief Description of CD " << index << " : ";
	cin.get(cd[index].type,maxlength);
	cin.ignore(100,'\n');

	cout << "Number of Tracks of CD " << index << " : ";
	cin >> cd[index].tracks;

	cd[index].exist=1;

}

void remcd()
{
	int index;
	cout << "Delete CD of which index? : ";
	cin >> index;

	for(int loop=0;loop<maxlength;loop++)
	{
		cd[index].title[loop]=0;
		cd[index].artist[loop]=0;
		cd[index].type[loop]=0;
	}
	cd[index].tracks=0;
	cd[index].exist=0;

}

void listtitle()
{
	int loop,loop1,num;
	for(loop1=50;loop1<255;loop1++)
	{
		num=0;
		for(loop=0;loop<maxcds;loop++)
		{
			if(cd[loop].title[0]==loop1)
			{
				display(loop);
				num++;
				getch();
			}
		}
	}
}

void listartist()
{

	int loop,loop1,num;
	for(loop1=50;loop1<255;loop1++)
	{
		num=0;
		for(loop=0;loop<maxcds;loop++)
		{
			if(cd[loop].artist[0]==loop1)
			{
				display(loop);
				num++;
				getch();
			}
		}
	}

}

/*
void and_or(const char a[])
{
	if(little[0]=='A' && little[1]=='N' && little[2]=='D' && little[3]=='\0') return 1;
	else if(little[0]=='O' && little[1]=='R' && little[2]=='\0') return -1;
	else return 0;
}



void searchtitle()
{

	int top=0, bottom=-2;
	int loop, loop1, loop2=0;
	int length;
	int andor=0;
	int possible[maxcds];
	char whole[20];
	char little[20];
	cin.get(whole,18);
	length=count(whole);
	for(loop1=0;loop1<maxcds;loop1++)
	{
		if(cd[loop1].exist==1)
		{
			for(loop=0;loop<maxlength;loop++)
			{
				if(cd[loop1].title[loop]==' ')
				{
					bottom=top+2;
					top=loop-1;
					for(loop2=0;loop2<=top-bottom;loop2++)
					{
						little[loop2]=cd[loop1].title[loop2+bottom];
						little[loop2]=toupper(little[loop2]);
					}

					little[loop2+1]='\0';
					andor=and_or(little);




}


void searchwords()
{

}
*/

void search()
{
	char string[maxlength];
	int s_length;
	int right=0;
	//char temp[maxlength];
	int loop,loop2,loop3;
	cin.ignore(100,'\n');
	cout << "Enter String to look for : ";
	cin.get(string,29);
	//cin.ignore(100,'\n');
	s_length=count(string);
	for(loop=0;loop<maxcds;loop++)
	{
		if(cd[loop].exist==1)
		{
			for(loop2=0;loop2<maxlength-1;loop2++)
			{
				for(loop3=0;loop3<s_length;loop3++)
				{
					if(string[loop3]==cd[loop].title[loop3+loop2]) right=1;
					else right=0;
					if(right!=1) break;
					//cout << endl << string[loop3] << cd[loop].title[loop3+loop2] << "..." << right;
				}
				if(right!=1)
				{
					for(loop3=0;loop3<s_length;loop3++)
					{
						if(string[loop3]==cd[loop].artist[loop3+loop2]) right=1;
						else right=0;
						if(right!=1) break;
						//cout << endl << string[loop3] << cd[loop].artist[loop3+loop2] << "..." << right;
					}
				}
				if(right!=1)
				{
					for(loop3=0;loop3<s_length;loop3++)
					{
						if(string[loop3]==cd[loop].type[loop3+loop2]) right=1;
						else right=0;
						if(right!=1) break;
						//cout << endl << string[loop3] << cd[loop].artist[loop3+loop2] << "..." << right;
					}

				}
				if(right==1)
				{
					display(loop);
					cout << endl;
				}

				//getch();
			}
		}
	}
}


void menu()
{
	clrscr();
	cout << "1=Add/Edit CD" << endl;
	cout << "2=Delete CD" << endl;
	cout << "3=Display Alpha. by Title" << endl;
	cout << "4=Display Alpha. by Atrist" << endl;
	cout << "5=Save" << endl;
	cout << "6=Load" << endl;
	cout << "7=Search" << endl;
	//cout << "7=Search Titles with and & or" << endl;
	//cout << "8=Search All with and & or" << endl;
	cout << "9=quit" << endl;
}


void main()
{
	char choice;
	do
	{
		menu();
		choice=toupper(getch());
		switch(choice)
		{
			case('1'):
			{
				addcd();
				getch();
				break;
			}
			case('2'):
			{
				remcd();
				getch();
				break;
			}
			case('3'):
			{
				listtitle();
				getch();
				break;
			}
			case('4'):
			{
				listartist();
				getch();
				break;
			}
			case('5'):
			{
				save();
				cout << endl << "Saved";
				getch();
				break;
			}
			case('6'):
			{
				load();
				cout << endl << "Loaded";
				getch();
				break;
			}
			case('7'):
			{
				search();
				getch();
				break;
			}
			case('8'):
			{
				//searchwords();
				getch();
				break;
			}
		}
	}while(choice!='9');
}






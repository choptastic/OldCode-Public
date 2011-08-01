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
	infile.open("cd.dat");
	for(int loop1=0;loop1<maxcds;loop++)
	{
		for(int loop=0;loop<maxlength;loop++)
		{
			infile >> cd[loop1].title[loop];
			infile >> cd[loop1].artist[loop];
			infile >> cd[loop1].type[loop];
		}
		infile >> cd[loop1].tracks;
	}


}

void save()
{

	ofstream outfile;
	outfile.open("cd.dat");
	for(int loop1=0;loop1<maxcds;loop++)
	{
		for(int loop=0;loop<maxlength;loop++)
		{
			outfile << cd[loop1].title[loop];
			outfile << cd[loop1].artist[loop];
			outfile << cd[loop1].type[loop];
		}
		outfile << cd[loop1].tracks;
	}
	outfile.close();


}

void addcd()
{
	int index;

	cout << "Index of CD : ";
	cin >> index;

	cout << "Title of CD " << index << " : ";
	cin.get(cd[index].title,maxlength);
	cin.ignore(100,'\n');

	cout << "Artist of CD " << index << " : ";
	cin.get(cd[index].title,maxlength);
	cin.ignore(100,'\n');

	cout << "Brief Description of CD " << index << " : ";
	cin.get(cd[index].title,maxlength);
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
	cd_type temp[maxcds];
	int loop,loop1;





}

void listartist()
{


}

void searchartist()
{

}

void searchwords()
{

}


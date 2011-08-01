#include<iostream.h>
#include<conio.h>


const int null=0,rl=1,rw=2,ftb=3,btf=4;

char array[40];
int pro[30];
int con[30];

int count()
{
	int num=0;
	while(array[num]!='\0')
	{
		num++;
	}
	return num;
}


void back_to_front()
{

	int max=count()-1;
	int loop=0;
	int loop1;
	char temp;

	while(array[max]!=' ')
	{

		loop++;
		temp=array[max];

		for(loop1=max;loop1>0;loop1--)
		{
			array[loop1]=array[loop1-1];
		}
		array[0]=temp;

	}

	for(loop1=max;loop1>loop;loop1--)
	{
		array[loop1]=array[loop1-1];
	}
	array[loop]=' ';



}

void front_to_back()
{
	int max=count()-1;
	int loop=max;
	int loop1;
	char temp;

	while(array[0]!=' ')
	{

		loop--;
		temp=array[0];

		for(loop1=0;loop1<max;loop1++)
		{
			array[loop1]=array[loop1+1];
		}
		array[max]=temp;

	}

	for(loop1=0;loop1<loop;loop1++)
	{
		array[loop1]=array[loop1+1];
	}
	array[loop]=' ';



}


void rev_letters()
{
	int loop,loop1;
	int max=count();
	int top=0;
	int letters=0,bottom=0;
	char temp;


	for(loop=0;loop<max+1;loop++)
	{
		letters++;
		if(array[loop]==' ' || array[loop]=='\0')
		{
			top=loop-1;
			bottom=top-letters+2;

			for(loop1=0;loop1<letters/2;loop1++)
			{
				temp=array[loop1+bottom];
				array[loop1+bottom]=array[top-loop1];
				array[top-loop1]=temp;

			}

			letters=0;

		}
	}


}

void flip()
{
	int loop;
	int temp;
	int max=count();
	for(loop=0;loop<max/2;loop++)
	{
		temp=array[loop];
		array[loop]=array[max-loop-1];
		array[max-loop-1]=temp;

	}


}

void rev_words()
{

	flip();
	rev_letters();

}

void undo()
{
	for(int loop=29;loop>0;loop--)
	{
		con[loop]=con[loop-1];
	}

	if(pro[0]==rw) rev_words();
	else if(pro[0]==rl) rev_letters();
	else if(pro[0]==ftb) back_to_front();
	else if(pro[0]==btf) front_to_back();
	con[0]=pro[0];
	for(loop=0;loop<29;loop++)
	{
		pro[loop]=pro[loop+1];
	}
	array[29]=null;
}

void redo()
{
	for(int loop=29;loop>0;loop--)
	{
		pro[loop]=pro[loop-1];
	}

	if(con[0]==rw) rev_words();
	else if(con[0]==rl) rev_letters();
	else if(con[0]==ftb) back_to_front();
	else if(con[0]==btf) front_to_back();
	pro[0]=con[0];
	for(loop=0;loop<29;loop++)
	{
		con[loop]=con[loop+1];
	}
}


void main()
{
	clrscr();
	char choice;
	int loop;
	cout << "Sentence : ";
	cin.get(array,39);
	cin.ignore(100,'\n');
	do
	{
		clrscr();
		cout << endl << "The Sentence is : " << endl << array << endl;
		cout 	<< "1=Reverse Words" << endl
			<< "2=Reverse Letters in Words" << endl
			<< "3=Back word to Front" << endl
			<< "4=Front Word to Back" << endl;
		if(pro[0]!=null) cout << "5=Undo" << endl;
		if(con[0]!=null) cout << "6=Redo" << endl;
		cout << "7=Quit" << endl;
		choice=getch();
		if(choice=='1')
		{
			rev_words();
			con[0]=null;
			for(loop=29;loop>0;loop--)
			{
				pro[loop]=pro[loop-1];
			}
			pro[0]=rw;
		}
		else if(choice=='2')
		{
			rev_letters();
			con[0]=null;
			for(loop=29;loop>0;loop--)
			{
				pro[loop]=pro[loop-1];
			}
			pro[0]=rl;
		}
		else if(choice=='3')
		{
			back_to_front();
			con[0]=null;
			for(loop=29;loop>0;loop--)
			{
				pro[loop]=pro[loop-1];
			}
			pro[0]=btf;
		}
		else if(choice=='4')
		{
			front_to_back();
			con[0]=null;
			for(loop=29;loop>0;loop--)
			{
				pro[loop]=pro[loop-1];
			}
			pro[0]=ftb;

		}
		else if(choice=='5' && pro[0]!=null) undo();
		else if(choice=='6' && con[0]!=null) redo();

	}while(choice!='7');
}



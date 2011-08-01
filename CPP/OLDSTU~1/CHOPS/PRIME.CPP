#include<include.h>


int prime(int num)
{
	for(int loop=2;loop<num;loop++)
	{
		if(num%loop==0) return 0;
		//cout << endl << num << " % " << loop << " = " << num%loop;
		//getch();
	}
	return 1;
}

void main()
{

	int num;
	int loop;
	int lines=0;

	do
	{
		cout << endl << "Enter a number (0 to quit): ";
		cin >> num;
		if(num!=0)
		{
			for(loop=2;loop<num;loop++)
			{
				if(prime(loop)==1)
				{
					lines++;
					cout << endl << loop;
					if(lines>23)
					{
						cout << endl << "<Press a Key to Continue Viewing>";
						getch();
						lines=0;
					}
				}
			}
			getch();
		}
	}while(num!=0);

}
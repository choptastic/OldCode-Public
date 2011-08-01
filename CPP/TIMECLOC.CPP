#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<time.h>

const int dpm[13]={29,31,28,31,30,31,30,31,31,30,31,30,31};

class shift
{
	time_t *tin,*tout;
	date_t *din,*dout;
	public:
	void punch_in();
	void punch_out();
	int hours();
};

void shift::punch_in()
{
	gettime(tin);
	getdate(din);
	cout << din << " " << tin << endl;
}

void shift::punch_out()
{
	gettime(tout);
	getdate(dout);
	cout << dout << " " << tout << endl;
}

int shift::hours()
{
	int h=(dout->da_day-din->da_day)*24;
	h+=tout->ti_sec-tin->ti_sec;
	cout << h;
	return h;
}




int days_per_month(int month, int year)
{
	if(month<1 || month>12) return -1;
	if(month==2 && year%4==0) return dpm[0];
	return dpm[month];
}




void main(int argc, char * argv[])
{
	shift swell;
	if(argc!=3 || (argv[1]!="in" && argv[1]!="out"))
	{
		cerr << "usage: argument [in/out] [timedelay minutes]";
		//exit(1);
	}
	if(argv[1]=="in") swell.punch_in();
	else swell.punch_out();
}






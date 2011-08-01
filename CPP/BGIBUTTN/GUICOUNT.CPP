#include "gui.cpp"
#include <fstream.h>

const int SIZEITEMCELL=100;
const int TABLETOP=0;
const int BSIZE=43;


const int DELETE=10;
const int CASE=11;
const int SLEEVE=12;
const int STACK=13;
const int INDIV=14;
const int SC_UP=15;
const int SC_DN=16;
const int SC_LT=17;
const int SC_RT=18;

char leftarrow[2]={char(17),0};
char rightarrow[2]={char(16),0};


int total(table &t, int r)
{
	unsigned int tot=0;
	for(int loop=0;loop<t.numcols();loop++)
		tot+=t.getvalue(loop,r);
	return tot;
}


void killchar(char* string,char c)
{
	int loop=0;
	while(string[loop]!=0)
	{
		if(string[loop]==c)
		{
			int pos;
			for(pos=loop;string[pos]!=0;pos++)
				string[pos]=string[pos+1];
		}
		loop++;
	}
}


int numitems(char* filename)
{
	char *v=(char*)malloc(20);
	ifstream in(filename);
	for(int loop=0;!in.eof();loop++)
		in.getline(v,19);
	in.close();
	free(v);
	return loop+1;

}

void loaditems(table &t)
{
	ifstream in("items.lst");
	char* v=(char*)malloc(19);
	for(int loop=0;!in.eof();loop++)
	{
		in.getline(v,19);
		killchar(v,'"');
		t.setvalue(0,loop,v);
	}
	free(v);
}

void loadfields(table &t)
{
	ifstream in("fields.cts");
	char* v=(char*)malloc(19);
	for(int loop=0;!in.eof();loop++)
	{
		in.getline(v,19);
		t.setvalue(loop,0,v);
	}
	free(v);
}

void main()
{
	//chdir("c:\\cpp\\bgibuttn");
	setupgraphics();
	initmouse();
	if(SHOWMOUSE) showmouse();
	int fieldcount=numitems("fields.cts");
	int itemcount=numitems("items.lst");

	table items(tdepth,(tdepth+2)*2+rowwidth,1,itemcount,1,28,SIZEITEMCELL,15,LEFT_TEXT);
	table fields(SIZEITEMCELL+12,tdepth,fieldcount,1,6,1,50,6,LEFT_TEXT);
	table values(SIZEITEMCELL+12,(tdepth+2)*2+rowwidth,fieldcount,itemcount,6,28,50,6,RIGHT_TEXT);
	table totals(420,(tdepth+2)*2+rowwidth,1,itemcount,1,28,60,6,RIGHT_TEXT);
	table totallabel(420,tdepth,1,1,1,1,60,8,LEFT_TEXT);
	table calcvalue(500+tdepth-1,tdepth+10,1,1,1,1,75,6,RIGHT_TEXT);

	button calc7(7,500,BSIZE+2,BSIZE,BSIZE,"7");
	button calc8(8,545,BSIZE+2,BSIZE,BSIZE,"8");
	button calc9(9,590,BSIZE+2,BSIZE,BSIZE,"9");
	button calc4(4,500,BSIZE+47,BSIZE,BSIZE,"4");
	button calc5(5,545,BSIZE+47,BSIZE,BSIZE,"5");
	button calc6(6,590,BSIZE+47,BSIZE,BSIZE,"6");
	button calc1(1,500,BSIZE+92,BSIZE,BSIZE,"1");
	button calc2(2,545,BSIZE+92,BSIZE,BSIZE,"2");
	button calc3(3,590,BSIZE+92,BSIZE,BSIZE,"3");
	button calc0(0,545,BSIZE+137,BSIZE,BSIZE,"0");

	button box(CASE,500,230,(BSIZE*3)/2,BSIZE-15,"Case");
	button sleeve(SLEEVE,500+(BSIZE*3)/2+3,230,(BSIZE*3)/2+2,BSIZE-15,"Sleeve");
	button stack(STACK,500,217+BSIZE,(BSIZE*3)/2,BSIZE-15,"Stack");
	button indiv(INDIV,500+(BSIZE*3)/2+3,217+BSIZE,(BSIZE*3)/2+2,BSIZE-15,"Indiv");
	button del(DELETE,590,0,BSIZE,BSIZE,"<<<");

	button scrollleft(SC_LT,150,455,48,24,leftarrow);
	button scrollright(SC_RT,200,455,48,24,rightarrow);
	button scrollup(SC_UP,300,455,48,24,"");
	button scrolldown(SC_DN,350,455,48,24,"");

	button quit(2000,0,460,70,20,"Quit");



	totallabel.setvalue(0,0,"Totals");
	loaditems(items);
	loadfields(fields);

	unsigned int cvalue;
	int status=-1;
	int r;

	while(status!=2000)
	{

		status=objects.checkall();
		cvalue=calcvalue.getselectedvalue();
		switch(status)
		{
			case(SC_LT):   fields.scrollleft();
								values.scrollleft();
								break;
			case(SC_RT):	fields.scrollright();
								values.scrollright();
								break;
			case(SC_UP):	items.scrollup();
								values.scrollup();
								break;
			case(SC_DN):	items.scrolldown();
								values.scrolldown();
								break;
			case(1):
			case(2):
			case(3):
			case(4):
			case(5):
			case(6):
			case(7):
			case(8):
			case(9):
			case(0):       if(long(cvalue)*long(10)+long(status)<65535)
									calcvalue.setselectedvalue((cvalue*10)+status);
								break;

			case(DELETE):  calcvalue.setselectedvalue(cvalue/10);
								break;

			case(INDIV):   if(cvalue==0)
									values.setselectedvalue("");
								else
									values.setselectedvalue(cvalue);

								calcvalue.setselectedvalue("");
								r=values.getselectedrow();
								totals.setvalue(0,r,total(values,r));

								break;



		}
	}
	closegraph();

}
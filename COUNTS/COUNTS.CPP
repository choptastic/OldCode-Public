#include <ctype.h>
#include "d:\counts\gui.cpp"
#include <fstream.h>

date cur;

char* listloc="items.lst";
char textloc[20]="daily\\";
char *fieldloc="fields.cts";
char *checkloc="temp\\check.cts";
char *saveloc="temp\\backup.cts";
char *wasteloc="temp\\waste.cts";
char *wastelist="wreason.cts";
const char *cssfieldloc="cssfield.cts";
const char *blank="&nbsp;";

const char* version="v2.1";

const int COLWID=6;
const int ITEMLEN=15;

const int CHECKCOUNTS=203;
const int RECOUNTS=204;
const int COUNTSDONE=205;

const int SIZEITEMCELL=100;
const int TABLETOP=0;
const int BSIZE=43;


const int W_X1=50;
const int W_Y1=50;
const int W_X2=590;
const int W_Y2=430;
const int W_WID=W_X2-W_X1;
const int W_HI=W_Y2-W_Y1;

const int DELETE=10;
const int CASE=11;
const int SLEEVE=12;
const int STACK=13;
const int INDIV=14;
const int SC_UP=15;
const int SC_DN=16;
const int SC_LT=17;
const int SC_RT=18;
const int SAVE=19;
const int LOAD=720;
const int WASTE=22;
const int FULLCASE=23;
const int SEND=24;
const int CLEAR=25;

const int VALUES=50;
const int ITEMS=51;
const int FIELDS=52;
const int TOTALS=53;
const int TOTALLABEL=54;
const int CALCVALUE=55;

const int WTOTAL=100;
const int WLIST=101;
const int WREASONS=102;
const int WADD=110;
const int WDEL=111;
const int WDONE=112;
const int WUP=113;
const int WDN=114;

const int endfieldmessage=8467;


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


void tocheckfile(table &t)
{
	ofstream out(checkloc);   // open check file for output
	out << CHECKCOUNTS << endl;   // output the checkcounts code
	for(int loop=0;loop<t.numrows();loop++)
		out << t.getvalue(0,loop) << endl;  // output each total value
	out.close();   // close file
}


void text_drawbottom(ofstream &out,table &fields)
{
	out << '|';
	for(int loop=0;loop<ITEMLEN-2;loop++)
		out << '-';
	for(loop=0;loop<fields.numcols()+1;loop++)
	{
		out << '-';
		for(int loop2=0;loop2<COLWID-1;loop2++)
			out << '-';
	}
	out << '|' << endl;
}

void text_drawtop(ofstream &out,table &fields)
{
	long beginning;
	out << endl;
	beginning=out.tellp();
	out << "Item";
	while(out.tellp()-beginning<ITEMLEN)
		out << ' ';
	for(int loop=0;loop<fields.numcols();loop++)
	{
		beginning=out.tellp();

		out << fields.getcvalue(loop,0);
		while(out.tellp()-beginning<COLWID)
			out << ' ';
	}
	beginning=out.tellp();
	//while(out.tellp()-beginning<COLWID-5)
	//	out << ' ';
	out << "Total" << endl;

	out << '|';
	for(loop=0;loop<ITEMLEN-2;loop++)
		out << '-';
	for(loop=0;loop<fields.numcols()+1;loop++)
	{
		out << '-';
		for(int loop2=0;loop2<COLWID-1;loop2++)
			out << '-';
	}
	out << '|' << endl;
}

void text_drawvalues(ofstream &out, table &items, table &values, table &totals)
{
	long beginning;
	for(int r=0;r<items.numrows();r++)
	{
		beginning=out.tellp();
		out << '|' << items.getcvalue(0,r);
		while(out.tellp()-beginning<ITEMLEN-1)
			out << ' ';
		for(int c=0;c<values.numcols();c++)
		{
			out << '|';
			beginning=out.tellp();
			if(values.getvalue(c,r)==0)
				out << " -- ";
			else
				out << values.getcvalue(c,r);

			while(out.tellp()-beginning<COLWID-1)
				out << ' ';
		}
		out << '|';
		beginning=out.tellp();
		if(totals.getvalue(0,r)==0)
			out << " -- ";
		else
			out << totals.getcvalue(0,r);
		while(out.tellp()-beginning<COLWID-1)
			out << ' ';

		out << '|';
		out << endl;
	}
}

void html_makefile(ofstream &out, table &items, table& fields,  table &values, table &totals)
{
	out 	<< "<title>Counts - End of Day</title>\n"
			<< "<center><font size=5> End of Day Counts : "
			<< int(cur.da_mon) << "/" << int(cur.da_day)
			<< "/" << cur.da_year << endl
			<< "</font></center>\n<table border=1 align=center cellspacing=0><tr><td></td>\n";
	int i,ii;

	//top

	for(i=0;i<fields.numcols();++i)
		out << "<td><b>" << fields.getcvalue(i,0) << "</b></td>\n";
	out << "<td><b>Totals</b></td>\n";
	out << "</tr>\n";


	//values
	for(i=0;i<items.numrows();i++)
	{
		out << "<tr><td><b>" << items.getcvalue(0,i) << "</b></td>\n";
		for(ii=0;ii<values.numcols();++ii)
		{
			out << "<td align=right>";
			if(values.getvalue(ii,i)==0)
				out << blank;
			else
				out << values.getvalue(ii,i);
			out << "</td>";
		}
		out << "<td><b>" << totals.getvalue(0,i) << "</b></td></tr>\n";
	}

	out << "</table>";
}



void totextfile(table &items, table &fields, table &values, table &totals)
{

	ofstream out(textloc);
	html_makefile(out,items,fields,values,totals);
	/*
	out << "Counts -- End of the Day\n";
	out << "For the date of: ";
	out << int(cur.da_mon) << "/" << int(cur.da_day) << "/" << cur.da_year << endl;

	struct time ti;
	gettime(&ti);

	out << "Counts were done at: " << int(ti.ti_hour) << ":";
	if(ti.ti_min<10)
		out << '0';
	out << int(ti.ti_min) << endl;
	text_drawtop(out, fields);
	text_drawvalues(out,items,values,totals);
	text_drawbottom(out,fields);
	out << endl << "Counts Calculator" << version << " by Whoa! Productions";
	*/
	out.close();
}






int strlen(char* v)
{
	for(int loop=0;v[loop]!=0;loop++);
	return loop;
}




int numitems(char* filename)
{
	char *v=(char*)malloc(20);
	ifstream in(filename);
	for(int loop=0;!in.eof();loop++)
	{
		in.getline(v,19);
		if(strlen(v)<=0) loop--;
	}
	in.close();
	free(v);
	return loop;

}

void loaditems(table &t)
{
	ifstream in(listloc);
	char* v=(char*)malloc(19);
	for(int loop=0;!in.eof();loop++)
	{
		in.getline(v,19);
		killchar(v,'"');
		killchar(v,' ');
		if(strlen(v)>0)
			t.setvalue(0,loop,v);
		else
			loop--;

	}
	free(v);
}

void loadfields(table &t)
{
	ifstream in(fieldloc);
	char* v=(char*)malloc(20);
	for(int loop=0;!in.eof();loop++)
	{
		in.getline(v,19);
		killchar(v,'"');
		killchar(v,' ');
		if(strlen(v)>0)
			t.setvalue(loop,0,v);
		else
			loop--;
	}
	free(v);
}

int compare(char *s1, char *s2)
{
		if(strlen(s1)!=strlen(s2))
			return 0;
		for(int loop=0;loop<strlen(s1);loop++)
		{
			if(toupper(s1[loop])!=toupper(s2[loop]))
				return 0;
		}
		return 1;
}

int find_item(table &t, char* s)
{
	for(int loop=0;loop<t.numrows();loop++)
		if(compare(s,t.getcvalue(0,loop))) return loop;
	return -1;
}

int find_field(table &t, char* s)
{
	for(int loop=0;loop<t.numcols();loop++)
		if(compare(s,t.getcvalue(loop,0))) return loop;
	return -1;
}


void loadwreason(table &t)
{
	ifstream in(wastelist);
	char str[40];
	for(int i=0;i<27 && !in.eof();i++)
	{
		in.getline(str,38);
		t.setvalue(0,i,str);
	}
	in.close();
}




void loadcss(int *css,int *field_full, int *app_fields, table &items, table &fields)
{
	int i=0;
	int v=0;
	char *s=(char*)malloc(50);

	ifstream in(cssfieldloc);
	while(v!=endfieldmessage)
	{
		in.getline(s,10);
		v=atoi(s);

		if(v!=endfieldmessage)
		{
			in.getline(s,20);
			killchar(s,'"');
			killchar(s,' ');

			i=find_field(fields,s);
			if(i!=-1)
			{
				if(v==0)
					app_fields[i]=0;
				else
					app_fields[i]=1;
			}
		}
	}
	while(!in.eof())
	{
		memset(s,0,40);
		in.getline(s,40);
		killchar(s,'"');
		i=find_item(items,s);
		if(i==-1)
		{
			memset(s,0,30);
			for(i=0;i<4;i++)
				in.getline(s,10);
		}
		else
		{
			in.getline(s,10);
			css[i*3+0]=atoi(s);
			in.getline(s,10);
			css[i*3+1]=atoi(s);
			in.getline(s,10);
			css[i*3+2]=atoi(s);
			in.getline(s,10);
			field_full[i]=atoi(s);

		}

	}
	in.close();
	free(s);
}


void drawwaste()
{
	setfillstyle(1,7);
	bar(W_X1,W_Y1,W_X2,W_Y2);
	setcolor(15);
	int i;
	for(i=0;i<tdepth+1;i++)
	{
		line(W_X1+i,W_Y1+i,W_X1+i,W_Y2-i);
		line(W_X1+i,W_Y1+i,W_X2-i,W_Y1+i);
	}
	setcolor(8);
	for(i=0;i<tdepth+1;i++)
	{
		line(W_X2-i,W_Y2-i,W_X1+i,W_Y2-i);
		line(W_X2-i,W_Y2-i,W_X2-i,W_Y1+i);
	}
	setcolor(0);
	rectangle(W_X1,W_Y1,W_X2,W_Y2);
	rectangle(W_X1+tdepth,W_Y1+tdepth,W_X2-tdepth,W_Y2-tdepth);
	line(W_X1+tdepth,W_Y1+tdepth,W_X1,W_Y1);
	line(W_X2-tdepth,W_Y1+tdepth,W_X2,W_Y1);
	line(W_X1+tdepth,W_Y2-tdepth,W_X1,W_Y2);
	line(W_X2-tdepth,W_Y2-tdepth,W_X2,W_Y2);

}

void savewastes(table &wastetotal, int wastecount)
{
	int r,loop;
	ofstream out(wasteloc);
	for(r=0;r<wastecount;r++)
		out << wastetotal.getcvalue(0,r) << endl;
	out.close();
}

void savebackup(table &values, table &items)
{
	ofstream out(saveloc);
	for(int r=0;r<items.numrows();r++)
	{
		out << items.getcvalue(0,r) << endl;
		for(int c=0;c<values.numcols();c++)
		{
			out << values.getcvalue(c,r) << endl;
		}
	}
	out.close();
}

void loadbackup(table &values, table &items)
{
	char str[40];
	int c,r;

	ifstream in(saveloc);
	while(!in.eof())
	{
		in.getline(str,20);
		r=find_item(items,str);
		if(r==-1)
			for(c=0;c<values.numcols();c++)
				in.getline(str,20);
		else
			for(c=0;c<values.numcols();c++)
			{
				in.getline(str,20);
				values.setvalue(c,r,str);
			}
	}
	in.close();
}


void waitingforresponse(table &items)
{
	drawwindow(100,220,540,260);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(0);
	outtextxy(320,240,"Waiting for response from office . . .");
	ifstream in;
	int response=0,loop,i;
	int x[3],y[3];
	char xvel[3],yvel[3],opixel[3],color[3];
	x[0]=320;
	y[0]=240;
	x[1]=110;
	y[1]=221;
	x[2]=530;
	y[2]=240;
	color[0]=15;
	color[1]=4;
	color[2]=0;
	memset(xvel,1,3);
	memset(yvel,1,3);
	memset(opixel,7,3);
	while(response!=RECOUNTS && response!=COUNTSDONE)
	{
		for(int loop=0;loop<100;loop++)
		{
			delay(20);
			for(i=0;i<3;i++)
			{
				if(getpixel(x[i]+xvel[i],y[i])!=7)
					xvel[i]*=-1;
				else if(getpixel(x[i],y[i]+yvel[i])!=7)
					yvel[i]*=-1;
				else if(getpixel(x[i]+xvel[i],y[i]+yvel[i])!=7)
				{
					response=random(3);
					if(response==0)
					{
						xvel[i]*=-1;
						yvel[i]*=-1;
					}
					else if(response==1)
						xvel[i]*=-1;
					else
						yvel[i]*=-1;
				}
				putpixel(x[i],y[i],opixel[i]);
				x[i]+=xvel[i];
				y[i]+=yvel[i];
				opixel[i]=getpixel(x[i],y[i]);
				putpixel(x[i],y[i],color[i]);
			}
		}

		in.open(checkloc);
		in >> response;
		in.close();
	}
	switch(response)
	{
		case(RECOUNTS):   for(response=0;response<items.numrows();response++)
									items.munselect(0,response);
								in.open(checkloc);
								in >> response;
								while(!in.eof())
								{
									in >> response;

									items.mselect(0,response);
								}
								in.close();
								break;
		case(COUNTSDONE): drawwindow(100,100,540,380);
								setcolor(0);
								outtextxy(320,120,"Hot dog! Counts are done");
								//outtextxy(320,140,"");
								outtextxy(320,180,"Please remove the startup diskette");
								outtextxy(320,200,"and restart the terminal");
								outtextxy(320,370,"Copyright 2000 by GuLP Software");

								setusercharsize(3,1,2,1);
								settextstyle(TRIPLEX_FONT,0,0);
								for(int loop=100;loop>=0;loop--)
								{
									setcolor(0);
									outtextxy(360-loop,320-loop,"WHOA!");
									delay(50);
									setcolor(loop);
									outtextxy(360-loop,320-loop,"WHOA!");
								}
								settextstyle(0,0,1);

								getch();
								break;
	}
}

void wastestr(char* a, char* b, char* c, char* s)
{
	int loop,len;
	memset(s,' ',35);
	len=strlen(a);
	for(loop=0;loop<5 && loop<len;loop++)
		s[loop]=a[loop];
	s[loop]=',';
	len=strlen(b);
	for(loop=0;loop<10 && loop<len;loop++)
		s[loop+7]=b[loop];
	s[loop+7]=',';
	len=strlen(c);
	for(loop=0;loop<4 && loop<len;loop++)
		s[loop+19]=c[loop];

	/////////////////////////////
	for(loop=0;loop<24;loop++)
		if(s[loop]==0) s[loop]=' ';
	s[24]=0;
}

void settextname()
{


	//preparing text file of counts
	// to be named based on date
	char filename[13];
	filename[13];
	filename[8]='.';
	filename[9]='h';
	filename[10]='t';
	filename[11]='m';
	filename[12]='\0';
	char y[5],d[3],m[3];

	int end;
	for(end=0;textloc[end]!='\0';end++);  // find end of string

	getdate(&cur);
	itoa(cur.da_year,y,10);
	itoa(int(cur.da_mon),m,10);
	itoa(int(cur.da_day),d,10);

	if(d[1]=='\0')
	{
		d[1]=d[0];
		d[0]='0';
	}
	if(m[1]=='\0')
	{
		m[1]=m[0];
		m[0]='0';
	}
	memcpy(&filename[4],m,2);
	memcpy(&filename[6],d,2);
	memcpy(&filename[0],y,4);
	memcpy(&textloc[end],filename,13);



}

void whoa()
{

	settextjustify(CENTER_TEXT,CENTER_TEXT);
	setcolor(4);
	outtextxy(296,462,"Counts Calculator");
	outtextxy(296,473,"GuLP Theatre Software");


}


void main()
{
	SHOWMOUSE=0;
	settextname();
	setupgraphics();
	initmouse();
	int *css,*app_fields,*field_full;
	int wastecount=0,loop;
	char * str=(char*)malloc(35);
	memset(str,0,35);


	int fieldcount=numitems(fieldloc);
	int itemcount=numitems(listloc);
	int wreasoncount=numitems(wastelist);
	css=(int *)malloc(itemcount*3*2);
	app_fields=(int *)malloc(fieldcount*2);
	field_full=(int *)malloc(itemcount*2);
	memset(app_fields,0,fieldcount*2);
	memset(field_full,0,itemcount*2);
	memset(css,0,itemcount*3*2);


	objectlibrary wastescreen;
	objectlibrary recountscreen;
	objectlibrary waitingscreen;
	objectlibrary objects;

	table wastetotal(&wastescreen,WTOTAL,310,40,1,27,1,27,175,37,LEFT_TEXT);
	table itemlist(&wastescreen,WLIST,10,40,1,itemcount,1,27,125,20,LEFT_TEXT);
	table wreasons(&wastescreen,WREASONS,150,40,1,wreasoncount,1,27,150,20,LEFT_TEXT);
	table wcalcvalue(&wastescreen,CALCVALUE,500+tdepth-1,38,1,1,1,1,75,6,RIGHT_TEXT);

	button wscrollup(&wastescreen,SC_UP,18,455,48,24,"");
	button wscrolldown(&wastescreen,SC_DN,68,455,48,24,"");
	button wup(&wastescreen,WUP,590,0,BSIZE,BSIZE,"");
	button wdn(&wastescreen,WDN,590,BSIZE+1,BSIZE,BSIZE,"");
	button wadd(&wastescreen,WADD,500,100,130,BSIZE,"Add");
	button wdel(&wastescreen,WDEL,500,150,130,BSIZE,"Delete");
	button wdone(&wastescreen,WDONE,500,400,130,BSIZE,"Wastes Done");





	table items(&objects,ITEMS,tdepth,(tdepth+2)*2+rowwidth,1,itemcount,1,28,SIZEITEMCELL,15,LEFT_TEXT);
	table fields(&objects,FIELDS,SIZEITEMCELL+12,tdepth,fieldcount,1,6,1,50,6,LEFT_TEXT);
	table values(&objects,VALUES,SIZEITEMCELL+12,(tdepth+2)*2+rowwidth,fieldcount,itemcount,6,28,50,6,RIGHT_TEXT);	table totals(&objects,TOTALS,420,(tdepth+2)*2+rowwidth,1,itemcount,1,28,60,6,RIGHT_TEXT);
	table totallabel(&objects,TOTALLABEL,420,tdepth,1,1,1,1,60,8,LEFT_TEXT);
	table calcvalue(&objects,CALCVALUE,500+tdepth-1,tdepth+10,1,1,1,1,75,6,RIGHT_TEXT);

	button calc7(&objects,7,500,BSIZE+2,BSIZE,BSIZE,"7");
	button calc8(&objects,8,545,BSIZE+2,BSIZE,BSIZE,"8");
	button calc9(&objects,9,590,BSIZE+2,BSIZE,BSIZE,"9");
	button calc4(&objects,4,500,BSIZE+47,BSIZE,BSIZE,"4");
	button calc5(&objects,5,545,BSIZE+47,BSIZE,BSIZE,"5");
	button calc6(&objects,6,590,BSIZE+47,BSIZE,BSIZE,"6");
	button calc1(&objects,1,500,BSIZE+92,BSIZE,BSIZE,"1");
	button calc2(&objects,2,545,BSIZE+92,BSIZE,BSIZE,"2");
	button calc3(&objects,3,590,BSIZE+92,BSIZE,BSIZE,"3");
	button calc0(&objects,0,545,BSIZE+137,BSIZE,BSIZE,"0");

	button box(&objects,CASE,500,230,(BSIZE*3)/2,BSIZE-2,"Case");
	button sleeve(&objects,SLEEVE,500+(BSIZE*3)/2+3,230,(BSIZE*3)/2+2,BSIZE-2,"Sleeve");
	button stack(&objects,STACK,500,230+BSIZE,(BSIZE*3)/2,BSIZE-2,"Stack");
	button indiv(&objects,INDIV,500+(BSIZE*3)/2+3,230+BSIZE,(BSIZE*3)/2+2,BSIZE-2,"Indiv");

	button fullcase(&objects,FULLCASE,0,0,SIZEITEMCELL+2,18,"Full");
	button del(&objects,DELETE,590,0,BSIZE,BSIZE,"<<<");
	button clear(&objects,CLEAR,0,457,SIZEITEMCELL-10,21,"Clear");

	button save(&objects,SAVE,500,350,60,30,"Save");
	button load(&objects,LOAD,573,350,60,30,"Load");

	button wasteb(&objects,WASTE,500,395,133,30,"Waste");
	//button recount(&objects,RECOUNTS,500,387,133,30,"Recounts");
	button send(&objects,SEND,500,435,133,40,"Send To Office");

	button scrollleft(&objects,SC_LT,SIZEITEMCELL+9,455,48,24,leftarrow);
	button scrollright(&objects,SC_RT,SIZEITEMCELL+59,455,48,24,rightarrow);
	button scrollup(&objects,SC_UP,385,455,48,24,"");
	button scrolldown(&objects,SC_DN,435,455,48,24,"");




	totallabel.setvalue(0,0,"Totals");
	loaditems(items);
	loadfields(fields);
	loadcss(css,field_full,app_fields,items,fields);
	loadwreason(wreasons);
	for(loop=0;loop<items.numrows();loop++)
		itemlist.setvalue(0,loop,items.getcvalue(0,loop));
	setfillstyle(1,7);
	bar(0,0,639,479);
	whoa();
	objects.drawall();


	unsigned int cvalue;
	int status=-1;
	int r,c,i,v;
	if(SHOWMOUSE) showmouse();

	while(status!=2000 && !kbhit())
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
								totals.scrollup();
								break;
			case(SC_DN):	items.scrolldown();
								values.scrolldown();
								totals.scrolldown();
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
			case(0):       if(long(cvalue)*long(10)+long(status)<10000)
									calcvalue.setselectedvalue((cvalue*10)+status);
								break;

			case(DELETE):  calcvalue.setselectedvalue(cvalue/10);
								break;

			case(CASE):
			case(SLEEVE):
			case(STACK):
			case(INDIV):   r=values.getselectedrow();
								status-=11;
								if(cvalue==0)
								{
									values.setselectedvalue("");
									values.nextcell();
								}
								else
								{
									if(status>=3)
									{
										values.setselectedvalue(cvalue);
										values.nextcell();
									}

									else
									{
										if(css[r*3+status]!=-1)
										{
											values.setselectedvalue(cvalue*css[r*3+status]);
											values.nextcell();
										}

									}
								}
								calcvalue.setselectedvalue("");
								cvalue=total(values,r);
								if(cvalue==0)
									totals.setvalue(0,r,"");
								else
									totals.setvalue(0,r,cvalue);
								totals.select(0,values.getselectedrow());
								items.select(0,values.getselectedrow());
								fields.select(values.getselectedcol(),0);
								break;

			case(FULLCASE):c=values.getselectedcol();
								if(app_fields[c]!=0)
								{
									for(r=0;r<values.numrows();r++)
									{
										if(field_full[r]>0)
										{
											values.setvalue(c,r,field_full[r]);
											v=total(values,r);
											if(v==0)
												totals.setvalue(0,r,"");
											else
												totals.setvalue(0,r,v);
										}
									}
								}

								break;

			case(CLEAR):   if(msg.raise("Are you sure you want to clear\nall current values?\nThere is no undo.",2))
								{
									values.clear();
									totals.clear();
								}
								break;

			case(VALUES):	totals.select(0,values.getselectedrow());
								items.select(0,values.getselectedrow());
								fields.select(values.getselectedcol(),0);
								break;
			case(TOTALS):	values.select(values.getselectedcol(),totals.getselectedrow());
								items.select(0,totals.getselectedrow());
								break;
			case(FIELDS):	values.select(fields.getselectedcol(),values.getselectedrow());
								break;
			case(ITEMS):	values.select(values.getselectedcol(),items.getselectedrow());
								totals.select(0,items.getselectedrow());
								break;

			case(LOAD):		if(msg.raise("Are you sure you want to load the\npreviously saved chart, overwriting\nthe current onscreen chart?",2)==1)
								{
									loadbackup(values,items);
									for(r=0;r<values.numrows();r++)
									{
										v=total(values,r);
										if(v==0)
											totals.setvalue(0,r,"");
										else
											totals.setvalue(0,r,v);
									}
								}
								break;
			case(SAVE):    if(msg.raise("Are you sure you want to save to\ndisk overwriting the previously\nsaved file?",2)==1)
									savebackup(values,items);
								break;

			case(WASTE):   setfillstyle(1,7);
								bar(0,0,639,479);
								whoa();
								wastescreen.en();
								wastescreen.drawall();
								wcalcvalue.setselectedvalue(1);
								while(status!=WDONE)
								{
									status=wastescreen.checkall();
									switch(status)
									{
										case(WUP):  if(wcalcvalue.getselectedvalue()<99)
															wcalcvalue.setselectedvalue(wcalcvalue.getselectedvalue()+1);
															break;
										case(WDN):	if(wcalcvalue.getselectedvalue()>1)
															wcalcvalue.setselectedvalue(wcalcvalue.getselectedvalue()-1);
														break;
										case(SC_DN):itemlist.scrolldown();
														break;
										case(SC_UP):itemlist.scrollup();
														break;
										case(WADD):	if(wastecount<27)
														{
															wastestr(itemlist.getselectedcvalue(),
																wreasons.getselectedcvalue(),
																wcalcvalue.getselectedcvalue(),str);
															wastetotal.setvalue(0,wastecount,str);
															wastecount++;
															wcalcvalue.setselectedvalue(1);
														}
														break;
										case(WDEL): int wastesel=wastetotal.getselectedrow();
														if(wastecount>0)
														{
															for(int loop=wastesel;loop<wastecount-1;loop++)
															{
																wastetotal.setvalue(0,loop,wastetotal.getcvalue(0,loop+1));
															}
															wastetotal.setvalue(0,wastecount-1,"");
															wastecount--;
														}
														break;


									}
								}
								status=-1;
								setfillstyle(1,7);
								bar(0,0,639,479);
								whoa();
								objects.drawall();
								break;
			case(SEND):    if(msg.raise("Are you sure counts are ready\nto be submitted to the office\nfor checking?",2)==1)
								{
									savewastes(wastetotal, wastecount);
									totextfile(items,fields,values,totals);
									tocheckfile(totals);
									waitingforresponse(items);
								}
								setfillstyle(1,7);
								bar(0,0,639,479);
								whoa();
								objects.drawall();
								break;


		}

	}
	free(css);
	free(app_fields);
	free(field_full);
	closegraph();

}
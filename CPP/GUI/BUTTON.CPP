#include <mouse.h>
#include <graph.h>

const int BUTTONUP=0;
const int BUTTONDOWN=1;
const int BUTTONCLICKED=2;
const int BUTTONRELEASED=3;
const int MAXBUTTONS=100;


int _mouse=BUTTONUP;
int mouse_status();



class _num_buttons
{
	friend button;
	int num;
	int index[MAXBUTTONS];
	int down;
	button *buttons[MAXBUTTONS];
	public:
	_num_buttons():num(0){}
} button_count;





class button
{
	char* msg;

	int x1,x2,y1,y2;
	int status;
	image *up,*down;
	int check(int mx, int my);  // ??? not sure if use
	void draw(int s);
	void set(int s);



	public:
	static int checkall();  // return teh call num
	button(int index,char* message, int x1, int y1, int x2, int y2, image *u, image*d);
};

void button::set(int s)
{
	status=s;
	draw(s);
}






int button::checkall()
{
	int mx=readmousex();
	int my=readmousey();
	int x1,x2,y1,y2;
	int mouse=mouse_status();
	if(mouse==BUTTONCLICKED)
	{
		for(int loop=0;loop<button_count.num;loop++)
		{
			x1=button_count.buttons[loop]->x1;
			x2=button_count.buttons[loop]->x2;
			y1=button_count.buttons[loop]->y1;
			y2=button_count.buttons[loop]->y2;
			if(mx>=x1 && mx<=x2 && my>=y1 && my<=y2)
			{
				button_count.buttons[loop]->set(BUTTONDOWN);
				button_count.down=loop;
			}

		}
	}
	else if(mouse==BUTTONRELEASED)
	{
		if(button_count.down!=-1)
		{
			x1=button_count.buttons[down]->x1;
			x2=button_count.buttons[down]->x2;
			y1=button_count.buttons[down]->y1;
			y2=button_count.buttons[down]->y2;
			if(mx>=x1 && mx<=x2 && my>=y1 && my<=y2)
			{
				button_count.buttons[down]->set(BUTTONUP);
				button_count.down=-1;
			}
		}
	}
	else if(mouse==BUTTONDOWN)
	{
		x1=button_count.buttons[down]->x1;
		x2=button_count.buttons[down]->x2;
		y1=button_count.buttons[down]->y1;
		y2=button_count.buttons[down]->y2;
		if(mx<x1 || mx>x2 || my<y1 || my>y2)
		{
			button_count.buttons[down]->set(BUTTONUP);
			button_count.down=-1;
		}
	}




	return -1;
}

void button::draw(int s)
{
	if(s==BUTTONUP)
		up->draw(x1,y1,x2,y2);
	else if(s==BUTTONDOWN)
		down->draw(x1,y1,x2,y2);
	// put down text
}


int mouse_status()
{
	if(mouseclicked(0))
		_mouse=BUTTONCLICKED;
	else if(mousereleased(0))
		_mouse=BUTTONRELEASED;
	else if(_mouse==BUTTONCLICKED)
		_mouse=BUTTONDOWN;
	else if(_mouse==BUTTONRELEASED)
		_mouse==BUTTONUP;

	return _mouse;
}










void main()
{

	// load list and define buttons
}

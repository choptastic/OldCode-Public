// Jesse Gumm
// Hour 2
// Shapes program, dude
// and Functions program too.
// don't ferget to check out Chops's realm of Chaos at:
// http://chopssdamassa.home.ml.org
// I always gotzta advertise my page, i don't know why.

#include <conio.h>
#include <iostream.h>

const float pi=3.141592654;
const char end_var='5';


float c_area(float c_rad)
{
	float area=pi*c_rad*c_rad;            // Circle Area formula
	return area;
}

float c_diam(float c_rad)
{
	float diam=2*c_rad;
	return diam;
}

float c_curc(float c_rad)
{
	float curc=2*pi*c_rad;
	return curc;
}

float r_area(float r_len, float r_wid)
{
	float area=r_len*r_wid;               // Rectangle Area formula
	return area;
}

float r_peri(float r_len, float r_wid)
{
	float peri=2*r_len+2*r_wid;
	return peri;
}

float t_area(float t_hig, float t_bas)
{
	float area=t_hig*0.5*t_bas;          // Triangle Area Formula
	return area;
}

void wuss()
{

	float r_len, r_wid, t_bas, t_hig, c_rad;
	clrscr();
	cout  << "This is how the rest of the class does it cuz they're all dumb" << endl
	<< "This part was added so that I at least have the stuff Soik wants to see" << endl;
	cout << endl << "Enter a radius : ";
	cin >> c_rad;
	cout << "Area : " << c_area(c_rad) << endl;
	cout << "Diameter : " << c_diam(c_rad) << endl;
	cout << "Circumference : " << c_curc(c_rad) << endl << endl;
	getch();
	cout << "Enter a Length : ";
	cin >> r_len;
	cout << endl << "Enter a Width : ";
	cin >> r_wid;
	cout << "Area : " << r_area(r_len,r_wid) << endl;
	cout << "Perimiter : " << r_peri(r_len,r_wid) << endl;
	getch();
	cout << "Enter a base length : ";
	cin >> t_bas;
	cout << endl <<"Enter a height : ";
	cin >> t_hig;
	cout << "Area : " << t_area(t_bas,t_hig);
	getch();
	clrscr();
	cout << "That's where everyone's program stops and mine just begins";
	getch();
	return;
}

int end_prog()
{
	char choice;				      //This decided whether or not
						      // to Quit the program
						      //returns the end_var variable
						      //if wish to quit
						      //and will not end unless user
						      //uses one of the choices
	while(choice!=end_var && choice!='1')
	{
		cout << endl << endl << "Do another calculation? . . .1 for yes, 2 for no: ";
		choice=getch();
		if(choice=='2') choice=end_var;
	}
	return choice;
}

void main()
{
	textcolor(15);
	clrscr();
	char choice;
	float r_len, r_wid, t_bas, t_hig, c_rad;
						     // declaration of variables
						     // Rectangle legth, Rec. Width, Tringle
						     //Base, Tri Height, Circle Radius

// Loop to determine whether or not to quit since Soik doesn't like gotos
while(choice!=end_var)
{
	textcolor(7);
	clrscr();
	cout << "1=Area, Diameter, and Circumferrence of a Circle" << endl << "2=Area and Perimeter of a Rectangle"
	<< endl << "3=Area of a Triangle" << endl << "4=Class Comparison" << endl << "5=Quit" << endl << "What's Yer Choice? : ";
	choice=getch();
	if(choice=='1')
	{
		cout << endl << "Radius of the Circle : ";
		cin >> c_rad;
		cout << endl << "Circle Radius : " << c_rad << endl << "Area: " << c_area(c_rad) << endl
		<< "Diameter : " << c_diam(c_rad) << endl
		<< "Circumference : " << c_curc(c_rad)
		<< endl;     						  // calculate circle stuff
		getch();
		choice=end_prog();
	}
	if(choice=='2')
	{
		cout << endl << "Length : ";
		cin >> r_len;
		cout << endl << "Width : ";
		cin >> r_wid;
		cout << endl << "Rectangle Length : " << r_len << endl << "Rectangle Width : " << r_wid << endl << "Area : " << r_area(r_len,r_wid) << endl << "Perimeter : " << r_peri(r_len,r_wid) << endl; // calculate rec area
		getch();
		choice=end_prog();
	}
	if(choice=='3')
	{
		cout << endl << "Base : ";
		cin >> t_bas;
		cout << "Height : ";
		cin >> t_hig;
		cout << endl << "Triangle Base : " << t_bas << endl << "Triangle Height : " << t_hig << endl << "Area : " << t_area(t_bas,t_hig);  //calculate tri area
		getch();
		choice=end_prog();
	}
	if(choice=='4') wuss();

}
//This is the end of the program
}





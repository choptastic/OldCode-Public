#include<c:\tc\bin\chops\include.h>

const int maxplayers=2;
const int shp=100;
const int smp=20;
const int sgold=10;
const int sblade=5;
const int sarm=2;
const int sma=0;
const int sthieve=2;


struct player_type
{
	int hp;
	int ma;
	int arm;
	int blade;
	int mana;
	int gold;
	int thieve;
	char name[30];
}guy[maxplayers+1];

void observe(int p)
{
	if(p==1) p=2;
	else p=1;
	int v;
	char *name=guy[p].name;

	gotoxy(30,5);
	v=guy[p].hp;
	if(v>=100) cout << name << " has not a scratch on him";
	else if(v>=75) cout <<  name << " has only cuts and bruises";
	else if(v>=50) cout << name << " is quite lashed up";
	else if(v>=25) cout << name << " Is looking pretty ragged";
	else cout << name << " is on he brink of death";

	gotoxy(30,6);
	v=guy[p].mana;
	if(v>=200) cout << name << " seems to pulsate with energy";
	else if(v>=125) cout << name << " has a kinda of glow";
	else if(v>=50) cout << name << " could casta pretty mean spell";
	else cout << name << " couldn't cast a spell if he tried";

	gotoxy(30,7);
	v=guy[p].blade;
	if(v>=125) cout << name << " could chop the head off a dragon";
	else if(v>=80) cout << name << "'s sword is quite shiny and sharp";
	else if(v>=60) cout << name << " could easily decapitate a small dog";
	else cout << name << "'s sword could be replaced with a thin stick";

	gotoxy(30,8);
	v=guy[p].arm;
	if(v>=50) cout << name << " is damn near wearing kevlar";
	else if(v>=37) cout << name << " has a nice mail shirt on";
	else if(v>=20) cout << name << " is wearing a very pretty leather jacket";
	else cout << name << " is wearing a Far Side shirt";

	gotoxy(30,9);
	v=guy[p].gold;
	if(v>=200) cout << name << " is weighted down greatly by his big purse";
	else if(v>=100) cout << name << " is struggling to hold his purse";
	else if(v>=45) cout << name << " is carrying his purse over his shoulder";
	else cout << name << " has a shiny nickel in his pocket";

	gotoxy(30,10);
	v=guy[p].thieve;
	if(v>=30) cout << name << " could steal the pants off a warrior";
	else if(v>=20) cout << name << " is a skilled pickpocket";
	else if(v>=10) cout << name << " could steal candy from a baby";
	else cout << name << " could maybe steal candy from a blind baby";

	gotoxy(30,11);
	v=guy[p].ma;
	if(v>=45) cout << name << " practically has a magical forcefield around him";
	else if(v>=25) cout << name << " has a small forcefield around him";
	else if(v>=10) cout << name << " could defend himself from a minor spell";
	else cout << name << " can be damaged from a cold stare";
}





void getnames()
{
	clrscr();
	cout << "Game by Me v2.0" << endl;
	for(int loop=1;loop<=maxplayers;loop++)
	{
		cout << "Player " << loop << " name : ";
		cin.get(guy[loop].name,29);
		cin.ignore(100,'\n');
		guy[loop].hp=shp;
		guy[loop].mana=smp;
		guy[loop].gold=sgold;
		guy[loop].arm=sarm;
		guy[loop].ma=sma;
		guy[loop].blade=sblade;
		guy[loop].thieve=sthieve;
	}

}


void attack(int p)
{
	int attacker, attackee;
	if(p==1)
	{
		attacker=1;
		attackee=2;
	}
	else
	{
		attacker=2;
		attackee=1;
	}
	int hurt=random(guy[attacker].blade);
	int def=random(guy[attackee].arm);
	if(def>hurt) def=hurt;
	guy[attackee].hp-=hurt-def;
	cout << endl << "Hit for : " << hurt-def;
}

void blade(int p, int amount)
{
	guy[p].blade+=amount;
	cout << endl << "Upgraded Blade : " << amount;
}

void armor(int p, int amount)
{
	guy[p].arm+=amount;
	cout << endl << "Upgraded Armor : " << amount;
}

void ma(int p, int amount)
{
	guy[p].ma+=amount;
	cout << endl << "Upgraded Mana Armor : " << amount;
}


void goldmenu(int p)
{
	cout << "Gold : " << guy[p].gold << endl;
	cout << "(A) Upgrade Blade 13............30 gold" << endl;
	cout << "(B) Upgrade Blade 29............60 gold" << endl;
	cout << "(C) Upgrade Armor 9.............25 gold" << endl;
	cout << "(D) Upgrade Armor 16............57 gold" << endl;
	cout << "(E) Upgrade Mana Armor 4........23 gold" << endl;
	cout << "(F) Upgrade Mana Armor 10.......54 gold" << endl;
	cout << "(G) Train Thievery..............20 gold" << endl;
	cout << "(H) Heal Self...................>1 gold" << endl;
	cout << "(I) Mana Potion.................30 gold" << endl;
	cout << "(Q) Buy Nothing" << endl;
	cout << "Choice? : " << endl;
}

int gold(int p, int type)
{
	if(type==0)
	{
		int toget=random(16)+random(16)+random(16);
		cout << endl << "Found : " << toget;
		guy[p].gold+=toget;
	}
	else
	{
		char choice=0;
		goldmenu(p);
		choice=toupper(getch());

		switch(choice)
		{
			case('A'):
			{
				if(guy[p].gold>=30)
				{
					guy[p].gold-=30;
					blade(p,13);
				}
				else choice='N';
				break;
			}
			case('B'):
			{
				if(guy[p].gold>=60)
				{
					guy[p].gold-=60;
					blade(p,29);
				}
				else choice='N';
				break;
			}
			case('C'):
			{
				if(guy[p].gold>=25)
				{
					guy[p].gold-=25;
					armor(p,9);
				}
				else choice='N';
				break;
			}
			case('D'):
			{
				if(guy[p].gold>=57)
				{
					guy[p].gold-=57;
					armor(p,16);
				}
				else choice='N';
				break;
			}
			case('E'):
			{
				if(guy[p].gold>=23)
				{
					guy[p].gold-=23;
					ma(p,4);
				}
				else choice='N';
				break;
			}
			case('F'):
			{
				if(guy[p].gold>=54)
				{
					guy[p].gold-=54;
					ma(p,10);
				}
				else choice='N';
				break;
			}
			case('G'):
			{
				if(guy[p].gold>=20)
				{
					guy[p].gold-=20;
					guy[p].thieve+=3;
					cout << "Increased Thievery" << endl;
				}
				else choice='N';
				break;
			}
			case('H'):
			{
				int amount;
				cout << endl << "Spend how much gold? (1 hp / 2 gold): " << endl;
				cin >> amount;
				if(guy[p].gold>=amount)
				{
					guy[p].hp+=amount/2;
					guy[p].gold-=amount;
					cout << "Healed : " << amount/2;
				}
				else choice='N';
				break;
			}
			case('I'):
			{
				if(guy[p].gold>=30)
				{
					int num=random(25)+random(25)+random(25);
					guy[p].mana+=num;
					guy[p].gold-=30;
					cout << "Increased Mana : " << num << endl;
				}
				else choice='N';
				break;
			}
			case('N'):
			{
				choice='Q';
				break;
			}
			default:
			{
				choice='Q';
			}
		}
		if(choice=='N')
		{
			cout << "Not Enough" << endl;
			return 0;
		}
		else if(choice=='Q')
		{
			return 0;
		}

	}
	return 1;
}

void thieve(int p)
{
	int attacker, attackee;
	int tosteal;
	if(p==1)
	{
		attacker=1;
		attackee=2;
	}
	else
	{
		attacker=2;
		attackee=1;
	}
	tosteal=(random(guy[attacker].thieve)-random(guy[attackee].thieve))+(random(guy[attacker].thieve)-random(guy[attackee].thieve))+(random(guy[attacker].thieve)-random(guy[attackee].thieve));
	if(tosteal<0) tosteal=0;
	if(guy[attackee].gold-tosteal<0) tosteal=guy[attackee].gold;
	guy[attacker].gold+=tosteal;
	guy[attackee].gold-=tosteal;
	if(guy[attackee].gold<0)
	{
		tosteal+=guy[attackee].gold;
		guy[attackee].gold=0;
	}
	cout << "Stole : " << tosteal;
}

void spellmenu(int p)
{
	cout << "Mana : " << guy[p].mana << endl;
	cout << "(A) Hurt  .....................(1 HP / 2 MP)" << endl;
	cout << "(B) Degrade Enemy Blade .......(1 level / 4 MP)" << endl;
	cout << "(C) Degrade Enemy Armor .......(1 level / 7 MP)" << endl;
	cout << "(D) Degrade Enemy Mana Armor...(1 level / 15 MP)" << endl;
	cout << "(E) Absorb Health..............(1 HP / 4 MP)" << endl;
	cout << "(Q) Don't cast a spell" << endl;
	cout << "Choice : " << endl;
}

void spell(int p)
{
	char choice;
	int amount;
	int attacker, attackee;

	if(p==1)
	{
		attacker=1;
		attackee=2;
	}
	else
	{
		attacker=2;
		attackee=1;
	}
	spellmenu(p);
	int protect;
	choice=toupper(getch());
	switch(choice)
	{
		case('A'):
		{
			cout << "Mana to use : ";
			cin >> amount;
			if(amount<=guy[p].mana)
			{
				guy[attacker].mana-=amount;
				if(random(3)!=1)
				{
					cout << "Spell Successful";
					protect=random(guy[attackee].ma);
					cout <<  endl << "Hurt for : " << amount/2-protect;

					if(protect>amount/2) protect=amount/2;
					guy[attackee].hp-=(amount/2)-protect;
				}
				else choice='U';
			}
			else choice='N';
			break;
		}
		case('B'):
		{
			cout << "Mana to use : ";
			cin >> amount;
			if(amount<=guy[p].mana)
			{
				guy[attacker].mana-=amount;
				if(random(3)!=1)
				{
					cout << "Spell Successful";
					cout << endl << "Blade degraded : " << amount/4;

					guy[attackee].blade-=amount/4;
					if(guy[attackee].blade<=0) guy[attackee].blade=1;
				}
				else choice='U';
			}
			else choice='N';
			break;
		}
		case('C'):
		{
			cout << "Mana to use : ";
			cin >> amount;
			if(amount<=guy[p].mana)
			{
				guy[attacker].mana-=amount;
				if(random(3)!=1)
				{
					cout << "Spell Successful";
					cout << endl << "Armor Degraded : " << amount/7;

					guy[attackee].arm-=amount/7;
					if(guy[attackee].arm<=0) guy[attackee].arm=1;
				}
				else choice='U';
			}
			else choice='N';
			break;
		}
		case('D'):
		{
			cout << "Mana to use : ";
			cin >> amount;
			if(amount<=guy[p].mana)
			{
				guy[attacker].mana-=amount;
				if(random(3)!=1)
				{
					cout << "Spell Successful";
					cout << endl << "Mana Armor Degraded : " << amount/15;

					guy[attackee].ma-=amount/15;
					if(guy[attackee].ma<=0) guy[attackee].ma=1;
				}
				else choice='U';
			}
			else choice='N';
			break;
		}
		case('E'):
		{
			cout << "Mana to use : ";
			cin >> amount;
			if(amount<=guy[p].mana)
			{
				guy[attacker].mana-=amount;
				if(random(3)!=1)
				{
					cout << "Spell Successful";
					protect=random(guy[attackee].ma);
					cout << endl << "Health Absorbed : " << amount/4-protect;

					if(protect>amount/4) protect=amount/4;
					guy[attackee].hp-=amount/4-protect;
					guy[attacker].hp+=amount/4-protect;
				}
				else choice='U';
			}
			else choice='N';
			break;
		}
	}
	if(choice=='N')
	{
		cout << "Not Enough Mana" << endl;
		choice='Q';
	}
	else if(choice=='U')
	{
		cout << "Spell Unsuccessful" << endl;
		choice='Q';
	}

}



void menu(int p)
{
	clrscr();
	observe(p);
	gotoxy(1,1);
	cout << guy[p].name << "'s Move" << endl;
	cout << "Health : " << guy[p].hp << endl;
	cout << "Attack : " << guy[p].blade << endl;
	cout << "Armor : " << guy[p].arm << endl;
	cout << "Mana : " << guy[p].mana << endl;
	cout << "Mana Armor : " << guy[p].ma << endl;
	cout << "Gold : " << guy[p].gold << endl;
	cout << "Thievery Level : " << guy[p].thieve << endl;
	cout << "(A) Attack" << endl;
	cout << "(B) Upgrade Blade" << endl;
	cout << "(C) Upgrade Armor" << endl;
	cout << "(D) Upgrade Mana Armor" << endl;
	cout << "(E) Get Gold" << endl;
	cout << "(F) Spend Gold" << endl;
	cout << "(G) Cast Spell" << endl;
	cout << "(H) Attempt Thievery" << endl;
	cout << "(I) Raise Mana" << endl;
	cout << "(S) Surrender" << endl;
	cout << "Your Move? : " << endl;

}




void main()
{
	textcolor(7);
	clrscr();
	randomize();
	int play=0;
	int player=0;
	char choice=0;
	int dead=0;
	int loop;
	do
	{
	getnames();
	play=random(2);
	player=0;
	choice=0;
	dead=0;

		do
		{
			play++;
			player=play%maxplayers;
			if(player==0) player=2;
			menu(player);
			choice=toupper(getch());
			switch(choice)
			{
				case('A'):
				{
					attack(player);
					break;
				}
				case('B'):
				{
					blade(player,5);
					break;
				}
				case('C'):
				{
					armor(player,2);
					break;
				}
				case('D'):
				{
					ma(player,2);
					break;
				}
				case('E'):
				{
					gold(player,0);
					break;
				}
				case('F'):
				{
					if(gold(player,1)==0) play--;
					break;
				}
				case('G'):
				{
					spell(player);
					play--;
					break;
				}
				case('H'):
				{
					thieve(player);
					break;
				}
				case('I'):
				{
					int num=random(9)+random(9)+random(9);
					cout << "Mana Raised : " << num;
					guy[player].mana+=num;
					break;
				}

				case('S'):
				{
					guy[player].hp=-666;
					break;
				}

				default:
				{
					play--;
					cout << "Invalid Choice" << endl;
				}

			}
			for(loop=1;loop<=maxplayers;loop++)
			{
				if(guy[loop].hp<=0) dead=loop;
			}
			if(dead==0) getch();

		}while(dead==0);
		cout << endl << guy[dead].name << " is dead" << endl;
		cout << "Again Y/N";
		choice=toupper(getch());
		if(choice=='N') choice='Q';
		//cin.ignore(100,'\n');

	}while(choice!='Q');
}

use pias;

drop table if exists lanparty;
drop table if exists rsvp;
drop table if exists contact;
drop table if exists computer;
drop table if exists quote;
drop table if exists lannews;
drop table if exists award;
drop table if exists newsletter;

create table newsletter
(
	newsletterid int unsigned not null auto_increment primary key,
	day date,
	newsletter char(50),
	txt text
);

create table award
(
	awardid int unsigned not null auto_increment primary key,
	award char(50),
	who char(50),
	why text,
	lanpartyid int
);

create table lanparty
(
	lanpartyid int unsigned not null auto_increment primary key,
	lanparty char(50),
	landate date
);

create table rsvp
(
	rsvpid int unsigned not null auto_increment primary key,
	lanpartyid int,
	computers int,
	alias char(50),
	fullname char(50),
	email char(50),
	location char(50)
);

create table contact
(
	contactid int unsigned not null auto_increment primary key,
	contact char(50),
	email char(100),
	howfound char(250)
);

create table computer
(
	computerid int unsigned not null auto_increment primary key,
	lanpartyid int,
	compname char(50),
	cpu int,
	mem int,
	hd int,
	vid int,
	3dmark2001 int,
	3dmark2003 int
);

create table quote
(
	quoteid int unsigned not null auto_increment primary key,
	quote char(250),
	person char(50)
);

create table lannews
(
	newsid int unsigned not null auto_increment primary key,
	subject char(150),
	news text,
	day date
);
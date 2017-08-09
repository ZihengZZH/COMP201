#include "Time.h"

//convert string to integer
int Time::sToInt(string s)
{
	int i;
	stringstream ss;
	ss << s;
	ss >> i;
	return i;
}

//convert a int to a string
string Time::intToSt(int n)
{
	string s;
	stringstream ss;
	ss << n;
	ss >> s;
	return s;
}

//default constuctor
Time::Time()
{
	year = 1899;
	month = 1;
	day = 1;
}  //the initial date will not pass the checkTime function

//normal constructor, initialize time by a string
Time::Time(string s)
{
	year = sToTime(s).year;
	month = sToTime(s).month;
	day = sToTime(s).day;
}

//normal constructor, initialize time by three integer
Time::Time(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}

//put the time in a string format
string Time::display()
{
	string s = intToSt(year)+"/"+ intToSt(month)+"/"+ intToSt(day);
	return s;
}

//define the assign in string
void Time::operator=(Time t)
{
	year = t.year;
	month = t.month;
	day = t.day;
}

//define the - in string
int Time::operator-(Time &t)
{
	int days1, days2, days;
	days = 0;
	days1 = transDays(this->year, this->month, this->day);
	days2 = transDays(t.year, t.month, t.day);
	if (this->year < t.year)
	{
		return 0;  //error! default value (day cannot be minus)
	}
	else if (this->year == t.year) {
		days = days1 - days2;
	}
	else{
		for (int i = t.year; i < this->year; i++)  //calculate the year if needed
		{
			if (IsLeapYear(i) == 1)
				days += 366;
			if (IsLeapYear(i) != 1)
				days += 365;
		}
		int h;
		h= days1 - days2;
		days += h;
	}

	return days;
}

//convert string to time
Time Time::sToTime(string s)
{
	int y, m, d;
	int position, counter = 0, difference;
	string a[3];
	for (int i = 0; i < 3; i++) {
		position = s.find("/", counter);
		difference = position - counter;
		a[i] = s.substr(counter, difference);
		counter = position + 1;
	}  //split the string by \t and store each parts in elements in a array

	y = sToInt(a[0]);
	m = sToInt(a[1]);
	d = sToInt(a[2]);
	return Time(y,m,d);
}

//define the operators for comparison
bool Time::operator>(Time t)
{
	if (year > t.year) {
		return true;
	}
	else if (year == t.year) {
		if (transDays(year, month, day) > transDays(t.year, t.month, t.day)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Time::operator<(Time t)
{
	if (year < t.year) {

		return true;
	}
	else if (year == t.year) {
		if (transDays(year, month, day) < transDays(t.year, t.month, t.day)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Time::operator==(Time t)
{
	if (year == t.year) {
		if (transDays(year, month, day) == transDays(t.year, t.month, t.day)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//check whether the string can be used a time
bool Time::checkTime(string s)
{
	int y, m, d;
	y = sToTime(s).year;
	m = sToTime(s).month;
	d = sToTime(s).day;
	return check(y, m, d);
}

//default destructor
Time::~Time()
{
}

//check the format of the date
bool Time::check(int y,int m,int d)
{
	if (y > 2100 || y < 1900)
		return false;
	if (m > 12 || m < 1)
		return false;
	if(m==1 || m==3 || m==5 ||m==7 ||m==8 ||m==10 ||m==12 )
	{
		if (d < 1 || d>31)
			return false;
	}
	else if(m==4 || m==6 || m==9 ||m==11)
	{
		if (d < 1 || d>30)
			return false;
	}
	else if(m==2)//bissextile
	{
		if ((IsLeapYear(y) == 1))
		{
			if (d > 29 || d < 1)
				return false;
			else
				return true;
		}
		if (d > 28 || d < 1)
			return false;
		else
			return true;
	}
	return true;
}

//check whether it is a leap year
bool Time::IsLeapYear(int year)
{
   		if(year%400==0 || (year%4==0 && year%100!=0))//bissextile
		{
			return  1;//bissextile
		}
		else
		{
			return 0;
		}
}

//get the days of a time(year is not include)
int Time::transDays(int year, int month, int day)
{
	int days;
	days = 0;
	int a, b, c;
	a = year; b = month; c = day;
	int i;
	for (i = 1; i < b; i++)
	{
		int t;
		t = MonthDay(a, i);
		days += t;
	}
	days += day;
	return days;
}

//calculate the days of a given month
int Time::MonthDay(int year, int month)
{
	int curday = 0;
	int leap = IsLeapYear(year);

	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		curday = 31;
		break;
	case 2:
		if (leap == 1)
		{
			curday = 29;
		}
		else
		{
			curday = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
		curday = 30;
		break;
	default:
		break;
	}
	return curday;
}
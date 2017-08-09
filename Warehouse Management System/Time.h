//Time class
//Designed by Ruichen Zheng
//Accomplished and tested by Shifan Zhao
//Time class is a simple and independent class. It defines the basic data of a Time. 
//It also encloses many function to check the whether the time is valid, as well as the operator overloading for Time calculation and comparison.

#ifndef _TIME
#define _TIME

#include<iostream>
#include<string>
using namespace std;
#include<sstream>

class Time
{
private:
	int year;
	int month;
	int day;

	int sToInt(string s);  //convert string to integer
	string intToSt(int n);  //convert integer to string
	int Time::transDays(int year, int month, int day);  //get the days of a time(year is not include)
	int Time::MonthDay(int year, int month);  //return the days of this month
	bool Time::IsLeapYear(int year);  //check it is a leapyear
    bool check(int y,int m,int d);  //check wether the time is valid
public:
	Time();  //default constructor
	Time(string s);  //normal constructor, initial Time by string
	Time(int y, int m, int d);  //normal constructor, initial Time by three integer

	string display();  //display time in a string format

	//define the operator for calculation
	void operator=(Time t);
	int operator-(Time &t);

	//define the the operator for comparison
	bool operator>(Time t);
	bool operator<(Time t);
	bool operator==(Time t);

	Time sToTime(string s); //convert string to time
	bool checkTime(string s);  //check whether the string can be used a time

	~Time();  //default destructor
};

#endif

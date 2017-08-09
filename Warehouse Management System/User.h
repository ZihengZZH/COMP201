//User class
//Designed by Ruichen Zheng
//Accomplished and tested by Zhaozhong Wu
//User class is a base class where the Customer and Keeper will inherent from.

#ifndef _USER
#define _USER

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class User
{
protected:
	int userID;
	string name;
	string password;

	void editInfo(); //this function is to let the user to change the username and the password, which can only be accessed inside the class
	int inputInteger(); //this funtion ask user to input a integer by storing in string and return converted integer
public:
	int getID(); //this function is to return the user id
	virtual void showUserInfo() {}  //for the output of basic information when in choose interface
	virtual void userInterface() {}  //show the function can only be done through the class (private function)
};
#endif



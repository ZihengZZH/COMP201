#include "User.h"

//this funtion ask user to input a integer by storing in string and return converted integer
int User::inputInteger()
{
	string choice;
	int i;
	getline(cin, choice);
	stringstream ss;
	ss << choice;
	ss >> i;
	return i;
}

//this function is to return the user id
int User::getID()
{
	return userID;
}

//this function is to let the user to change the username and the password, which can only be accessed inside the class
void User::editInfo()
{
	int choice;
	string str;
	cout << "  -------------------------------------- \t" << endl;
	cout << " |       Modify account information     |" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	cout << "Please choose personal information you want to modify:" << endl;
	cout << "1. Username\n2. Password" << endl;
	cout << "---------------" << endl;
	choice = inputInteger();
	switch (choice) {
	case 1:
		cout << "----------------------------------" << endl;
		cout << "Current username: " << name << endl;
		cout << "Please input new username: ";
		getline(cin, str);
		name = str;
		cout << "----------------------------------" << endl;
		cout << "Username modified successfully" << endl;
		break;
	case 2:
		cout << "----------------------------------" << endl;
		cout << "Current password: " << password << endl;
		cout << "Please input new password: ";
		getline(cin, str);
		password = str;
		cout << "----------------------------------" << endl;
		cout << "Password modified successfully" << endl;
		break;
	default:
		cout << "#######################" << endl;
		cout << "#    Invalid input!   #" << endl;
		cout << "#######################" << endl;
		break;
	}
}

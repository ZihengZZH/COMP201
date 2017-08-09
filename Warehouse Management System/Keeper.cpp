#include "Keeper.h"

//the default constuctor
Keeper::Keeper()
{
}

//the normal constructor to initalize Keeper by passed arguments
Keeper::Keeper(int u, string p, string n)
{
	userID = u;
	name = n;
	password = p;
}

//show the information when in function choose interface
void Keeper::showUserInfo()
{
	cout << "  ----------------------------------------------- " << endl;
	cout << " |                                               |" << endl;
	cout << " |            Welcome, Keeper: " << name << " !          |" << endl;
	cout << " |                                               |" << endl;
	cout << " |              Nice to see you again !          |" << endl;
	cout << " |                                               |" << endl;
	cout << "  ----------------------------------------------- " << endl;
	cout << endl;
}

//for the user, change account information is the only thing that can be done in its class
//other function needs to be done through database class, there are 2 reasons:
//1. Database cannot be include in this class
//2. Even the keeper itslef has no authority to access all the functions in database. For example, the customers' password.
void Keeper::userInterface()
{
	this->editInfo();
}

//the default destructor
Keeper::~Keeper()
{
}

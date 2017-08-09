//Customer class
//Designed by Ruichen Zheng
//Accomplished and tested by Zhaozhong Wu
//Keeper class is a depend class inherited from User class. It cannot directly have access to Customer¡¯s class, which can put privacy protection under guarantee. 

#ifndef _KEEPER
#define _KEEPER

#include"User.h"
//never try to include Database there. There are 2 reasons:
//1. Keeper have no authority to access goods information
//2. It will cause the file to include itself

class Keeper: public User
{
	friend class DataBase;
public:
	Keeper();  //the default constructor
	Keeper(int u, string p, string n);  //the normal constructor to initial Keeper with past arguments
	
	void showUserInfo();  //show the user information in the function choose interface
	void userInterface();  //the function that better done inside the class

	~Keeper();  //the default destructor
};

#endif

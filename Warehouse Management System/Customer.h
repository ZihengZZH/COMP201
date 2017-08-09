//Customer class
//Designed by Ruichen Zheng
//Accomplished and tested by Zhaozhong Wu
//Customer class is a depend class inherited from User class, which also includes the Goods class.

#ifndef _CUSTOMER
#define _CUSTOMER

#include"User.h"
#include"Goods.h"

class Customer: public User
{
	friend class DataBase;
private:
	vector<Goods*> goods;

	void setGoods(vector<Goods> &g);  //set the goods vector in this class with the pointers of the goods with same userid of this object
	
	void displayGoods();  //the function to display all the goods belonging to this customer
	float getFee();  //the function to return total fee
	void deleteGoods();  //the function to delete certain goods with id
	void changeGoodsInfo();  //the function to change the goods information
	void emptyCustomer();  //empty the whole customer, only be called by keeper
public:
	Customer();  //default constructor
	Customer(int u, string p, string n);  //normal constructor

	void showUserInfo();  //for the output of basic information when in choose interface
	void userInterface();  //the function that better done inside the class

	~Customer();  //default destructor
};

#endif
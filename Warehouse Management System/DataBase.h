//Database class
//Designed by Ruichen Zheng
//Accomplished and tested by Chongyun Wang
//Database class is the most complicated and critical class in the program. 
//It not only directly or indirectly include all the other classes, but also is the friend class of all other class except for Time class. 
//This class control the data read, manipulation and write. This class also defines some specific functions to achieve functionalities for Keeper and Customer. 


#ifndef _DATABASE
#define _DATABASE

#include <iomanip>
#include"Customer.h"
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include"Keeper.h"
//some head file has been included in keeper.h

class DataBase
{
private:
	vector<Customer> cUser;  //store all the customers read from file
	vector<Goods> goodsList;  //store all the goods read from file
	vector<Container> containerlist;  //store all the containers read from file
	Keeper adminstrator;  //store the Keeper's information
	Time systemTime;  //store the system time

	int sToInt(string s);
	void readInfo();  //this function aims to read the three txt file
	bool saveBig(int gid, int size);  //this is the funtion to save goods in the two large warehouse
	bool saveSmall(int gid, int size);  //this is the funtion to save goods in the four small warehouse
	int emptyContainer(int WHnum);  //this function is to check the empty containers of particular warehouse
	int inputInteger();  //this function ask user to input a integer by storing in string and return converted integer

public:
	DataBase();  //the constructor firstly read the file and ask the user to input a system time
	void saveData();  //this function is used to save the data in the file

	int userExist(string s);  //this the funtion to check whether the user exist by its username
	bool isPWCorrect(int n, string s);  //check whether the password is correct by usertype(the integer returned in previous function)

	Customer* getCustomer(int n);  //return the address of a customer in the customer vector by the userId
	Keeper* getKeeper();  //return the address of a Keeper

	void addNewGoods(int uid);  //this function is used for customer to create new goods
							//note that according to requirement, one goods is required to store in single warehouse
	void addCustomer();  //this function is to let the Keeper to add customer
	void deleteCustomer();  //this function is to let the keeper to delete a existing customer
	void listCustomer();  //this function is to let the keeper to check all the customers with brief information

	void showWarehouseInfo();  //this function aims to let the keeper to show all the warehouse information

	void searchGoods();  //search goods by id
	void searchCustomer();  //search customer by id
	void searchContainer();  //search container by id

	~DataBase();  //default destructor
};

#endif
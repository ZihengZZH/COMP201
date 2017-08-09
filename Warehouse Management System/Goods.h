//Goods class
//Designed by Ruichen Zheng
//Accomplished and tested by Zhaozhong Wu
//Goods class is a simple and dependent class, which includes Container and Time class. It defines the basic data of a goods, as well as several functions to print out its information.

#ifndef _GOODS
#define _GOODS

#include<string>
#include<vector>
#include"Container.h"

#include"Time.h"
#include<sstream>

class Goods
{
	friend class Customer;
	friend class DataBase;
private:
	int goodsId;
	int userId;
	float fee;
	Time startTime;
	Time endTime;
	string goodsInfo;
	int goodsSize;

	vector<Container*> containers;  //vector to store the pointer of all the containers that have the same goodsid as this goods

	void setContainer(vector<Container> &c);  //set the container vector in this class with the pointers of the containers with same goodsid
	void emptyContainer();  //clear the container by setting the goodsid to 0
	void calFee();     //calculate the fee and return the value
public:
	Goods();  //the default constructor
	Goods(int gid, int uid, string st, string et, string ginfo, int gsize);  //the normal constructor

	void goodsInfoDisplay();  //get the basic information of this goods

	~Goods();
};

#endif

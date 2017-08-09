//Container class
//Designed by Ruichen Zheng
//Accomplished by Zhaoshi Fan and tested by Zhaozhong wu
//Container class is a simple and independent class. It defines the basic data of a container, as well as several functions to print out its information.


#ifndef _CONTAINER
#define _CONTAINER

#include<iostream>
#include <iomanip>
using namespace std;

class Container
{
	friend class Goods;
	friend class DataBase;
private:
	int containerId, locX, locY, warehouseNum, goodsId, containerSize;
	bool isEmpty();  //check whether a container is empty
public:
	Container();  //default constructor
	Container(int id, int x, int y, int wNum, int gid, int csize);  //normal constructor
	
	void containerInfor();  //get the basic information of a container
	void wareHouse();  //get the container's location

	~Container();  //default destructor
};

#endif
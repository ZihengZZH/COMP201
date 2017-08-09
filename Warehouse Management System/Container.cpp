#include "Container.h"

//default constructor
Container::Container()
{
}

//normal constructor
Container::Container(int id, int x, int y, int wNum, int gid, int csize)
{
	containerId = id;
	locX = x;
	locY = y;
	warehouseNum = wNum;
	goodsId = gid;
	containerSize = csize;
}

//get the basic information of a container
void Container::containerInfor()
{
	cout << "\t" << containerId << "\t" << locX << "\t" << locY << "\t" << warehouseNum << "\t" << containerSize << endl;
}

//get the container's location
void Container::wareHouse()
{
	if (1001 <= containerId && containerId <=1500) {
		cout << "This a big container is located in Row " << locX << " ,Column "<< locY <<" of the NO.1 large warehouse." << endl;
	}
	else if (2001 <= containerId && containerId <= 2500) {
		cout << "This a big container is located in Row " << locX << " ,Column " << locY << " of the NO.2 large warehouse." << endl;
	}
	else if (3001 <= containerId && containerId <= 3400) {
		cout << "This a small container is located in Row " << locX << " ,Column " << locY << " of the NO.3 small warehouse." << endl;
	}
	else if (4001 <= containerId && containerId <= 4400) {
		cout << "This a small container is located in Row " << locX << " ,Column " << locY << " of the NO.4 small warehouse." << endl;
	}
	else if (5001 <= containerId && containerId <= 5400) {
		cout << "This a small container is located in Row " << locX << " ,Column " << locY << " of the NO.5 small warehouse." << endl;
	}
	else if (6001 <= containerId && containerId <= 6400) {
		cout << "This a small container is located in Row " << locX << " ,Column " << locY << " of the NO.6 small warehouse." << endl;
	}
	else {
		cout << "Invalid container." << endl;
	}
}

//default destructor
Container::~Container()
{
}

//check whether a container is empty
bool Container::isEmpty()
{
	if (goodsId == 0) {
		return true;
	}
	else {
		return false;
	}
}


#include "Goods.h"

//the default constructor
Goods::Goods()
{
}

//the normal constructor
Goods::Goods(int gid, int uid, string st, string et, string ginfo, int gsize)
{
	goodsId = gid;
	userId = uid;
	Time s(st);
	Time e(et);
	startTime = s;
	endTime = e;
	goodsSize = gsize;
	goodsInfo = ginfo;
}

//set the container vector in this class with the pointers of the containers with same goodsid
void Goods::setContainer(vector<Container> &c)
{
	for (unsigned int i = 0; i < c.size(); i++) 
	{
		if (c[i].goodsId == goodsId)
		{
			containers.push_back(&c[i]);
		}
	}

	this->calFee();
}

//clear the container by setting the goodsid to 0. Then, set current goodsid to 0
void Goods::emptyContainer()
{
	for (unsigned int i = 0; i < containers.size(); i++) {
		containers[i]->goodsId = 0;
	}
	goodsId = 0;
}

//default destructor
Goods::~Goods()
{
}

//calculate the fee and return the value
void Goods::calFee()
{
	float feeTemp = 0;
	for (unsigned int i = 0; i < containers.size(); i++) {
		if (containers[i]->containerSize == 5) {
			feeTemp += 0.03* (endTime - startTime);
		}
		else {
			feeTemp += 0.02* (endTime - startTime);
		}
	}
	fee = feeTemp;
}  //fee caculated by the type and number of containers it occupied

   //get the basic information of this goods
void Goods::goodsInfoDisplay()        //display the info of the goods
{
	cout << goodsId << "\t" << goodsSize << "\t" << startTime.display() << "\t" << endTime.display() << "\t" << fee << "\t" << goodsInfo << endl;
}


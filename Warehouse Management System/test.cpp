#include <iostream>
#include "Time.h"
#include "Container.h"
using namespace std;

int main()
{
	cout<<"------------------test Time----------------------"<<endl;
	Time aa(2011,1,2);
	Time bb(2011,2,3);
	Time cc(2011,1,2);
	aa=bb;
	cout<<aa.display()<<endl;
	aa=bb + cc;
	cout<<aa.display()<<endl;
	aa=bb - cc;
	cout<<aa.display()<<endl;
	if(0!=aa.check(1,2,3))
		cout<<"Wrong date"<<endl;

	Time dd("2013/12/1");
	cout<<dd.display();
	cout<<"------------------test Container----------------------"<<endl;
	vector<Container>ContainerList;
	//int id, int x, int y, int wNum, int gid, int csize
	Container   cter(1100,1,2,1,1000,5);
	ContainerList.push_back(cter);

	vector<Container>::iterator it=ContainerList.begin();
	cout<<"checkInfo:";it->checkInfo();
		
	cout<<"containerId:"<<it->getcontainerId()<<endl; 
	cout<<"containerSize"<<it->getcontainerSize()<<endl;
    cout<<"currentNum"<<it->getcurrentNum()<<endl;
    cout<<"locX"<<it->getlocX()<<endl;
    cout<<"locY"<<it->getlocY()<<endl;
    cout<<"warehouseNum"<<it->getwarehouseNum()<<endl;
    cout<<"goodsId"<<it->getgoodsId()<<endl;
	cout<<"-------------------test containner :save goods save currentNum------------------------"<<endl;
	it->saveGoods(1234);
	it->setcurrentNum(3);
	cout<<"checkInfo:";it->checkInfo();
return 0;
}
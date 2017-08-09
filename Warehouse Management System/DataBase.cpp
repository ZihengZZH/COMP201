#include "DataBase.h"
//#include <iostream>
//#include<string>
//using namespace std;
//these head file may not need. They have been include in the Database.h

//tbis function aims to read the three txt file
void DataBase::readInfo()
{
	string s,keeper;
	int counter = 0, position, difference;

	ifstream fin1("container.txt");  //if the container file doesn't exist, create all the three files.
	if (!fin1.is_open())
	{
		ofstream fout1("container.txt");// create an goods file if does not exist
		fout1 << "containerId	locX	locY	warehouseNum	goodsId	containerSize" << endl;
		for (int i = 1; i<501; i++) {
			if (i % 50==0) {
				fout1 << 1000 + i << "\t" << (i / 50) + 1 << "\t" << 50 << "\t" << 1 << "\t" << 0 << "\t" << 5 << endl;
			}
			else {
				fout1 << 1000 + i << "\t" << (i / 50)+1 << "\t" << i % 50 << "\t" << 1 << "\t" << 0 << "\t" << 5 << endl;
			}
		}
		for (int i = 1; i<501; i++) {
			if (i % 50 == 0) {
				fout1 << 2000 + i << "\t" << (i / 50) + 1 << "\t" << 50 << "\t" << 2 << "\t" << 0 << "\t" << 5 << endl;
			}
			else {
				fout1 << 2000 + i << "\t" << (i / 50) + 1 << "\t" << i % 50 << "\t" << 2 << "\t" << 0 << "\t" << 5 << endl;
			}
		}
		for (int i = 1; i<401; i++) {
			if (i % 40 == 0) {
				fout1 << 3000 + i << "\t" << (i / 40) + 1 << "\t" << 40 << "\t" << 3 << "\t" << 0 << "\t" << 3 << endl;
			}
			else {
				fout1 << 3000 + i << "\t" << (i / 40) + 1 << "\t" << i % 40 << "\t" << 3 << "\t" << 0 << "\t" << 3 << endl;
			}
			
		}
		for (int i = 1; i<401; i++) {
			if (i % 40 == 0) {
				fout1 << 4000 + i << "\t" << (i / 40) + 1 << "\t" << 40 << "\t" << 4 << "\t" << 0 << "\t" << 3 << endl;
			}
			else {
				fout1 << 4000 + i << "\t" << (i / 40) + 1 << "\t" << i % 40 << "\t" << 4 << "\t" << 0 << "\t" << 3 << endl;
			}
		}

		for (int i = 1; i<401; i++) {
			if (i%40==0) {
				fout1 << 5000 + i << "\t" << (i / 40) + 1 << "\t" << 40 << "\t" << 5 << "\t" << 0 << "\t" << 3 << endl;
			}
			else {
				fout1 << 5000 + i << "\t" << (i / 40) + 1 << "\t" << i % 40 << "\t" << 5 << "\t" << 0 << "\t" << 3 << endl;
			}
		}

		for (int i = 1; i<400; i++) {
			if (i % 40 == 0) {
				fout1 << 6000 + i << "\t" << (i / 40) + 1 << "\t" << 40 << "\t" << 6 << "\t" << 0 << "\t" << 3 << endl;
			}
			else {
				fout1 << 6000 + i << "\t" << (i / 40) + 1 << "\t" << i % 40 << "\t" << 6 << "\t" << 0 << "\t" << 3 << endl;
			}
		}
		fout1 << 6400 << "\t" << 10 << "\t" << 40 << "\t" << 6 << "\t" << 0 << "\t" << 3; //no endl!!!

		fout1.close();

		ofstream fout2("goods.txt");// creat an goods file if does not exist
		fout2 << "goodsId	userId	startTime	endTime	goodsInfo	goodSize";  //no endl!!
		fout2.close();

		ofstream fout3("customer.txt");// creat an customer file if does not exist
		fout3 << "userID	password	name" << endl;
		fout3 << 0 << "\t" << "12345" << "\t" << "Keeper";  //no endl!!!
		fout3.close();
	}
	else
	{
		fin1.close();
	}


	// read container
	ifstream cont("container.txt");
	getline(cont, s);  //the first line is the label, which should be ignored

	while (cont.eof() == 0) {  //read the rest of the file
		getline(cont, s);  //read the whole line and store in string s
		string a[6];  //create a string array for store splitted string

		for (int i = 0; i < 6; i++) {
			position = s.find("\t", counter);
			difference = position - counter;
			a[i] = s.substr(counter, difference);
			counter = position + 1;
		}  //split the string by \t and store each parts in elements in a array
		Container y(sToInt(a[0]), sToInt(a[1]), sToInt(a[2]), sToInt(a[3]), sToInt(a[4]), sToInt(a[5]));
		containerlist.push_back(y);  //add this container to Container Vector
	}
	cont.close();  //close the file



	// read goods
	ifstream fin2("goods.txt");  //if the goods file doesn't exist, create it and empty the container.
	if (!fin2.is_open())
	{
		ofstream fout2("goods.txt");// creat an goods file if does not exist
		fout2 << "goodsId	userId	startTime	endTime	goodsInfo	goodSize";
		fout2.close();

		for (unsigned int i = 0; i < containerlist.size(); i++) {
			containerlist[i].goodsId = 0;
		}

		//write the container into txt file
		ofstream c0("container.txt");
			c0 << "containerId	locX	locY	warehouseNum	goodsId	containerSize" << endl;
		
		for (unsigned int i = 0; i < containerlist.size() - 1; i++) {
			c0 << containerlist[i].containerId << "\t" << containerlist[i].locX << "\t" << containerlist[i].locY << "\t" << containerlist[i].warehouseNum << "\t" << containerlist[i].goodsId << "\t" << containerlist[i].containerSize << endl;
		}
		c0 << containerlist.back().containerId << "\t" << containerlist.back().locX << "\t" << containerlist.back().locY << "\t" << containerlist.back().warehouseNum << "\t" << containerlist.back().goodsId << "\t" << containerlist.back().containerSize;  //WARNING! Avoid an empty line created by endline
		c0.close();

		ofstream fout3("customer.txt");// create an customer file if does not exist
		fout3 << "userID	password	name" << endl;
		fout3 << 0 << "\t" << "12345" << "\t" << "Keeper";  //no endl!!!
		fout3.close();
	}
	else
	{
		fin2.close();
	}

	ifstream goods("goods.txt");
	getline(goods, s); //the first line is the label, which should be ignored

	while (goods.eof() == 0) {  //read the rest of the file
		getline(goods, s);  //read the whole line and store in string s
		string a[6];  //create a string array for store splitted string

		for (int i = 0; i < 6; i++) {
			position = s.find("\t", counter);
			difference = position - counter;
			a[i] = s.substr(counter, difference);
			counter = position + 1;
		}  //split the string by \t and store each parts in elements in a array
		Goods y(sToInt(a[0]), sToInt(a[1]), a[2], a[3], a[4], sToInt(a[5]));
		goodsList.push_back(y);  //add this goods to Goods Vector
	}
	for (unsigned int i = 0; i < goodsList.size(); i++) {
		goodsList[i].setContainer(containerlist);
	}  //set the pointer all the containers that has the same goodid to the good object
	goods.close();  //close the file


	//read customer
	ifstream fin3("customer.txt");  //if the customer file doesn't exist, create it and empty the container and goods.
	if (!fin3.is_open())
	{
		ofstream fout3("customer.txt");// creat an customer file if does not exist
		fout3 << "userID	password	name" << endl;
		fout3 << 0 << "\t" << "12345" << "\t" << "Keeper";
		fout3.close();

		for (unsigned int i = 0; i < containerlist.size(); i++) {
			containerlist[i].goodsId = 0;
		}

		ofstream c0("container.txt");
		c0 << "containerId	locX	locY	warehouseNum	goodsId	containerSize" << endl;
		for (unsigned int i = 0; i < containerlist.size() - 1; i++) {
			c0 << containerlist[i].containerId << "\t" << containerlist[i].locX << "\t" << containerlist[i].locY << "\t" << containerlist[i].warehouseNum << "\t" << containerlist[i].goodsId << "\t" << containerlist[i].containerSize << endl;
		}
		c0 << containerlist.back().containerId << "\t" << containerlist.back().locX << "\t" << containerlist.back().locY << "\t" << containerlist.back().warehouseNum << "\t" << containerlist.back().goodsId << "\t" << containerlist.back().containerSize;  //WARNING! Avoid an empty line created by endline
		c0.close();

		goodsList.clear();

		ofstream g0("goods.txt");// creat an goods file if does not exist
		g0 << "goodsId	userId	startTime	endTime	goodsInfo	goodSize";  //no endl!!
		g0.close();
	}
	else
	{
		fin3.close();
	}

	ifstream ufile("customer.txt");

	getline(ufile, keeper); //the first line is the label, which should be ignored

	getline(ufile, keeper); //the second line stores the information of the keeper
	string kp[3];
	for (int i = 0; i < 3; i++) {
		position = keeper.find("\t", counter);
		difference = position - counter;
		kp[i] = keeper.substr(counter, difference);
		counter = position + 1;
	}  //split the string by \t and store each parts in elements in a array
	adminstrator = Keeper(sToInt(kp[0]), kp[1], kp[2]);  //initial the keeper with the read file

	while (ufile.eof() == 0) {  //read the rest of the file
		getline(ufile, s);  //read the whole line and store in string s
		string a[3];  //create a string array for store splitted string

		for (int i = 0; i < 3; i++) {
			position = s.find("\t", counter);
			difference = position - counter;
			a[i] = s.substr(counter, difference);
			counter = position + 1;
		}  //split the string by \t and store each parts in elements in a array
		Customer y(sToInt(a[0]), a[1], a[2]);
		cUser.push_back(y);  //add this customer to Customer Vector
	}
	ufile.close();
	for (unsigned int i = 0; i < cUser.size(); i++) {
		cUser[i].setGoods(goodsList);
	}   //set the pointer of all the goods that has the same userid to the customer object
	goods.close();  //close the file
}

//this is the funtion to save goods in the two large warehouse
bool DataBase::saveBig(int gid, int size) 
{
	int num;
	if (size %5 ==0) {
		num = size/5;
	}
	else {
		num = (size/5) + 1;
	}
	// num the number of containers that will be occupied

	if (num <= emptyContainer(1)) {  //if the first warehouse has enough space
			for (int i = 0; i < 500; i++) {	//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {  //whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				}  //goods may not be stored in continuous containers
				if (num == 0) {  //if all parts of the goods is store, return true
					return true;
				}
		}
	}
	else if(num <= emptyContainer(2)){  //if the second warehouse has enough space
			for (int i = 500; i < 1000; i++) { 	//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {	//whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				}  //goods may not be stored in continuous containers
				if (num == 0) {  //if all parts of the goods is store, return true
					return true;
				}
		}
	}
	else {
		return false;  //if neither of them has space, return false
	}
}

//this is the funtion to save goods in the four small warehouse
bool DataBase::saveSmall(int gid, int size)
{
	int num;
	if (size % 3 == 0) {
		num = size / 3;
	}
	else {
		num = (size / 3) + 1;
	}
	// num the number of containers that will be occupied

	if (num <= emptyContainer(3)) {  //if the first warehouse has enough space
			for (int i = 1000; i < 1400; i++) {		//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {  //whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				}  //goods may not be stored in continuous containers
				if (num == 0) {
					return true;  //if all parts of the goods is store, return true
				}
		}
	}
	else if (num <= emptyContainer(4)) {  //if the second warehouse has enough space
			for (int i = 1400; i < 1800; i++) {		//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {	 //whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				}  //goods may not be stored in continuous containers
				if (num == 0) {
					return true;  //if all parts of the goods is store, return true
				}
		}
	}
	else if (num <= emptyContainer(5)) {  //if the third warehouse has enough space
			for (int i = 1800; i < 2200; i++) {		//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {	 //whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				}  //goods may not be stored in continuous containers
				if (num == 0) {
					return true;  //if all parts of the goods is store, return true
				}
		}
	}
	else if(num <= emptyContainer(6)){	//if the fourth warehouse has enough space
			for (int i = 2200; i < 2600; i++) {		//note that the container is set and there is no function that can change their id
				if (containerlist[i].isEmpty()) {	 //whenever find an empty space, store parts of the goods
					containerlist[i].goodsId = gid;
					num--;
				} //goods may not be stored in continuous containers
				if (num == 0) {
					return true;  //if all parts of the goods is store, return true
				}
		}
	}else {
		return false;  //if neither of them has space, return false
	}
}

//this function is to check the empty containers of particular warehouse
int DataBase::emptyContainer(int WHnum)
{
	int w1 = 0, w2 = 0, w3 = 0, w4 = 0, w5 = 0, w6 = 0;
	for (unsigned int i = 0; i < containerlist.size(); i++) {
		if (1001 <= containerlist[i].containerId && containerlist[i].containerId <= 1500) {
			if (containerlist[i].isEmpty()) {
				w1 += 1;  //calculate the empty containers of the first warehouse
			}
		}
		else if (2001 <= containerlist[i].containerId && containerlist[i].containerId <= 2500) {
			if (containerlist[i].isEmpty()) {
				w2 += 1;  //calculate the empty containers of the second warehouse
			}
		}
		else if (3001 <= containerlist[i].containerId && containerlist[i].containerId <= 3400) {
			if (containerlist[i].isEmpty()) {
				w3 += 1;  //calculate the empty containers of the third warehouse
			}
		}
		else if (4001 <= containerlist[i].containerId && containerlist[i].containerId <= 4400) {
			if (containerlist[i].isEmpty()) {
				w4 += 1;  //calculate the empty containers of the fourth warehouse
			}
		}
		else if (5001 <= containerlist[i].containerId && containerlist[i].containerId <= 5400) {
			if (containerlist[i].isEmpty()) {
				w5 += 1;  //calculate the empty containers of the fifth warehouse
			}
		}
		else if (6001 <= containerlist[i].containerId && containerlist[i].containerId <= 6400) {
			if (containerlist[i].isEmpty()) {
				w6 += 1;  //calculate the empty containers of the sixth warehouse
			}
		}
		else {
		}
	}
	switch (WHnum) {  //return certain value by the given argument
	case 1:
		return w1;
		break;
	case 2:
		return w2;
		break;
	case 3:
		return w3;
		break;
	case 4:
		return w4;
		break;
	case 5:
		return w5;
		break;
	case 6:
		return w6;
		break;
	default:
		break;
	}
}

//this funtion ask user to input a integer by storing in string and return converted integer
int DataBase::inputInteger()
{
	string choice;
	int i;
	getline(cin, choice);  //use string to store the input
	stringstream ss;
	ss << choice;
	ss >> i;  //convert string to integer
	return i;
}

//this function is used to save the data in the file
void DataBase::saveData()
{
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].userID == 0) {  //for customer, when the userID == 0, it means this customer has been deleted
			cUser.erase(cUser.begin()+i);
		}
	}
	for (unsigned int i = 0; i < goodsList.size(); i++) {
		if (goodsList[i].goodsId == 0) {  //for goods, when the goodsId == 0, it means this goods has been deleted
			goodsList.erase(goodsList.begin() + i);
		}
	}  //erase the deleted customer and goods

	//write the customer and keeper into txt file
	ofstream cu("customer.txt");
	if (cUser.size()==0) {
		cu << "userID	passward	name" <<endl;
		cu << adminstrator.userID << "\t" << adminstrator.password << "\t" << adminstrator.name;  //this second should store the information of keeper
	}
	else {
		cu << "userID	passward	name" << endl;
		cu << adminstrator.userID << "\t" << adminstrator.password << "\t" << adminstrator.name << endl;  //this second should store the information of keeper
	}
	if (cUser.size()!=0) {
		for (unsigned int i = 0; i < cUser.size()-1; i++) {
			cu << cUser[i].userID << "\t" << cUser[i].password << "\t" << cUser[i].name << endl;
			}
			cu << cUser.back().userID << "\t" << cUser.back().password << "\t" << cUser.back().name;  //WARNING! Avoid an empty line created by endline
	}
	
	cu.close();

	//write the goods into txt file
	ofstream go("goods.txt");
	if (goodsList.size()==0) {
		go << "goodsId	userId	startTime	endTime	goodsInfo	goodSize";
	}
	else {
		go << "goodsId	userId	startTime	endTime	goodsInfo	goodSize" << endl;
	}
	
	if (goodsList.size()!=0) {
		for (unsigned int i = 0; i < goodsList.size() - 1; i++) {
			go << goodsList[i].goodsId << "\t" << goodsList[i].userId << "\t" << goodsList[i].startTime.display() << "\t" << goodsList[i].endTime.display() << "\t" << goodsList[i].goodsInfo << "\t" << goodsList[i].goodsSize << endl;
		}
		go << goodsList.back().goodsId << "\t" << goodsList.back().userId << "\t" << goodsList.back().startTime.display() << "\t" << goodsList.back().endTime.display() << "\t" << goodsList.back().goodsInfo << "\t" << goodsList.back().goodsSize;  //WARNING! Avoid an empty line created by endline
	}
	
	go.close();

	//write the container into txt file
	ofstream co("container.txt");
	co << "containerId	locX	locY	warehouseNum	goodsId	containerSize" << endl;
	for (unsigned int i = 0; i < containerlist.size()-1; i++) {
		co << containerlist[i].containerId << "\t" << containerlist[i].locX << "\t" << containerlist[i].locY << "\t" << containerlist[i].warehouseNum << "\t" << containerlist[i].goodsId << "\t" << containerlist[i].containerSize << endl;
	}
	co << containerlist.back().containerId << "\t" << containerlist.back().locX << "\t" << containerlist.back().locY << "\t" << containerlist.back().warehouseNum << "\t" << containerlist.back().goodsId << "\t" << containerlist.back().containerSize;  //WARNING! Avoid an empty line created by endline
	co.close();
}

//this the funtion to check whether the user exist by its username
int DataBase::userExist(string s)
{
	if (s == adminstrator.name) {
		return -1;  //return -1 if it is a adminstrator
	}
	else {
		for (unsigned int i = 0; i < cUser.size(); i++) {
			if (s == cUser[i].name) {
				return i;  //return userid if it is a customer
			}
		}
		return -2;  //return -2 if use not found
	}
	
}

//check whether the password is correct by usertype(the integer returned in previous function)
bool DataBase::isPWCorrect(int n, string s)
{
	if (n == -1) {
		return s == adminstrator.password;
	}
	else if(n >= 0){
		if (cUser.size()==0) {
			return false;
		}
		else {
			return s == cUser[n].password;
		}
	}
	else {
	}  //this condition doesn't exist, but just in case
}

//return the address of a customer in the customer vector by the userId
Customer* DataBase::getCustomer(int n)
{
	return &cUser[n];
}

//return the address of a Keeper
Keeper * DataBase::getKeeper()
{
	return &adminstrator;
}

//this function is used for customer to create new goods
//note that according to requirement, one goods is required to store in single warehouse
void DataBase::addNewGoods(int uid)
{
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].userID == 0) {  //for customer, when the userID == 0, it means this customer has been deleted
			cUser.erase(cUser.begin() + i);
		}
	}
	for (unsigned int i = 0; i < goodsList.size(); i++) {
		if (goodsList[i].goodsId == 0) {  //for goods, when the goodsId == 0, it means this goods has been deleted
			goodsList.erase(goodsList.begin() + i);
		}
	}  //erase the deleted customer and goods

	string st, et, info, sz;
	int gid;
	int size;
	if (goodsList.size()==0) {
		gid = 1;
	}
	else {
		gid = goodsList.back().goodsId + 1;
	}
	
	bool added = true;

	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(25) << "Add new goods" << setw(14) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	//let the user to input the goods size
	cout << "----------------------------------" << endl;
	cout << "Please input the Goods size: ";
	size = inputInteger();

	//the goods size cannot by 0 or negative. Moreover, the maximun space of a large warehouse is 2500
	while (size <= 0 || size > 2500) {
		cout << "Invalid size. please input again" << endl;
		cout << "----------------------------------" << endl;
		cout << "Please input the Goods size:";
		size = inputInteger();
	}

	//let the user to input start time
	cout << "----------------------------------" << endl;
	cout << "Please input the Start Time (format YYYY/MM/DD): " << endl;
	getline(cin, st);
	Time t1;

	t1 = Time(st);
	while (t1.checkTime(st) != true || t1 < systemTime) {  //reject the invalid input
		if (t1.checkTime(st) != true) {  //give the instruction for the error
			cout << "Invalid date. please input again." << endl;
		}
		else if(t1 < systemTime) {
			cout << "Start day should not be earlier than system time." << endl;
			cout << "System time: " << systemTime.display() << endl;
		}
		else {
		}
		cout << "----------------------------------" << endl;
		cout << "Please input the Start Time (format YYYY/MM/DD): " << endl;
		getline(cin, st);
		t1 = Time(st);
	}
	cout << "----------------------------------" << endl;
	cout << "Start Time successfully set." << endl;

	//ask for input end time
	cout << "----------------------------------" << endl;
	cout << "Please input the End Time (format YYYY/MM/DD):" << endl;
	getline(cin, et);
	Time t2;
	t2 = Time(et);
	while (t2.checkTime(et) != true || !(t2 > t1)) {  //reject the invalid input
		if (t2.checkTime(et) != true) {  //give the instruction for the error
			cout << "Invalid date. Please input again." << endl;
		}
		else if (!(t2 > t1)) {
			cout << "End day should be later than start time." << endl;
			cout << "System time: " << systemTime.display() << endl;
		}
		else {
		}
		cout << "----------------------------------" << endl;
		cout << "Please input the End Time (format YYYY/MM/DD): " << endl;
		getline(cin, et);
		t2 = Time(et);
	}
	cout << "----------------------------------" << endl;
	cout << "End Time successfully set." << endl;


	//ask for imput goods information
	cout << "----------------------------------" << endl;
	cout << "Please input the goods information: " << endl;
	getline(cin, info);
	cout << "----------------------------------" << endl;
	cout << "Goods information successfully set" << endl;

	//start for storing the goods
	//the big container has space of 5, the small container has space 3
	if (size <= 3) {  //if the total space is less than 3
		if (saveSmall(gid, size) == false) {
			added = false;
		}
	}
	else if (size <= 5) {  //if the space is between 3 and 5
		if (saveBig(gid, size) == false) {
			added = false;
		}
	}
	else if (size > 1200) {  // is the space is larger than 1200(the maximun size of a small warehouse)
		if (saveBig(gid, size) == false) {
			added = false;
		}
	}
	else { 
		int i = 1, j = 1;
		while (3 * i < size) {
			i++;
		}
		while (5 * j < size) {
			j++;
		}
		//calculate the number of large(j) or small container(i)

		if ((j<=emptyContainer(1) || j<=emptyContainer(2))&&(i > emptyContainer(3)|| i > emptyContainer(4)|| i > emptyContainer(5)|| i > emptyContainer(6))) {
			if (saveSmall(gid, size) == false) {
				added = false;
			}

		}  //if the large warehouse has but the small warehouse doesn't have much container

		else if ((j > emptyContainer(1) || j > emptyContainer(2)) && (i <= emptyContainer(3) || i <= emptyContainer(4) || i <= emptyContainer(5) || i <= emptyContainer(6))) {
			if (saveBig(gid, size) == false) {
				added = false;
			}

		} //if the samll warehouse has but the large warehouse doesn't have much container
		else if((j > emptyContainer(1) || j > emptyContainer(2)) && (i > emptyContainer(3) || i > emptyContainer(4) || i > emptyContainer(5) || i > emptyContainer(6))){
			added = false;

		} //if the both warehouse don't have much container
		  //the prority is the price, the next is the number of the containers
		  //the aim is to make customer paid less first (beacause they cannot determine how the goods is stored. If they could have pay less, they will not satisfied), 
		  //and occupy less space, for the profit of the warehouse
		else {
			if (2 * i < 3 * j) {  //if storing in the small container is cheaper
				if (saveSmall(gid, size) == false) {
					added = false;
				}
			}
			else if (2 * i == 3 * j) {  //if the price is the same
				if (3 * i <= 5 * j) {  //check which method will make the most of the space (less space wasted)
					if (saveSmall(gid, size) == false) {
						added = false;
					}
				}
				else {
					if (saveBig(gid, size) == false) {
						added = false;
					}
				}
			}  //if storing in the large container is cheapers
			else {
				if (saveBig(gid, size) == false) {
					added = false;
				}
			}
		}//if the both warehouse have enough container
	}

	if (added == true) {  //if no error made in saving
		Goods g(gid, uid, st, et, info, size);  //create a goods with input information
		g.setContainer(containerlist);  //set the container with the same goodsid(the goods stored) in to the goods object
		g.calFee(); //calculate the fee of the goods

		goodsList.push_back(g);

		cUser[uid - 1].goods.clear();  //clear the current Goods* vector in customer list
		cUser[uid - 1].setGoods(goodsList);   //very important!!!! When never a push_back, the memory location will change.
		//the vector must be cleared!!!!!

		cout << "----------------------------------" << endl;
		cout << "Goods has been added successfully." << endl;
		cout << endl;
	}  
	else {	//if there is an error in storing, give instructions.
		cout << "----------------------------------" << endl;
		cout << "No enough room. Goods add failed" << endl;
		cout << endl;
	}
	system("pause");
}

//this function is to let the Keeper to add customer
void DataBase::addCustomer()
{
	int cid;
	if (cUser.size()==0) {
		cid = 1;
	}
	else {
		cid = cUser.back().userID + 1;
	}
	
	string name, pass;
	bool nameExist = false;

	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(25) << "Add new customer" << setw(14) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	cout << "----------------------------------" << endl;
	cout << "Please input the customer name: ";
	getline(cin, name);

	//check whether the name is the same as the existing customer
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].name == name && cUser[i].userID!=0) {
			nameExist = true;
		}
	}

	//if the name is the same, ask for input again
	while (nameExist == true){
		cout << "Sorry, the user name exist. Please input again." << endl;
		cout << "----------------------------------" << endl;
		cout << "Please input the customer name: " << endl;
		getline(cin, name);
		nameExist = false;

		for (unsigned int i = 0; i < cUser.size(); i++) {
			if (cUser[i].name == name) {
				nameExist = true;
			}
		}
	}
	cout << "----------------------------------" << endl;
	cout << "Customer name successfully set." << endl;


	//let the user to input password
	cout << "----------------------------------" << endl;
	cout << "Please input the password:";
	getline(cin, pass);
	cout << "----------------------------------" << endl;
	cout << "Password successfully set." << endl;
	cout << "----------------------------------" << endl;

	cUser.push_back(Customer(cid, pass, name));  //no other vector that stores the customer, no need to clear!!!
}

//this function is to let the keeper to delete a existing customer
void DataBase::deleteCustomer()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(30) << "Delete current customer" << setw(9) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	bool deleted = false;

	cout << "----------------------------------" << endl;
	cout << "Please input ID of the Customer you want to delete: " << endl;
	int cid = inputInteger();
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].userID == cid) {
			cUser[i].emptyCustomer(); //when deleting, call the emptyCustomer inside the customer class
			cout << "----------------------------------" << endl;
			cout << "Customer is successfully deleted." << endl;
			deleted = true;
		}
	}
	if (deleted == false) {
		cout << "----------------------------------" << endl;
		cout << "Customer not found." << endl;
	}
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].userID == 0) {  //for customer, when the userID == 0, it means this customer has been deleted
			cUser.erase(cUser.begin() + i);
		}
	}
	for (unsigned int i = 0; i < goodsList.size(); i++) {
		if (goodsList[i].goodsId == 0) {  //for goods, when the goodsId == 0, it means this goods has been deleted
			goodsList.erase(goodsList.begin() + i);
		}
	}  //erase the deleted customer and goods
}

//this function is to let the keeper to check all the customers with brief information
void DataBase::listCustomer()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(30) << "Display all customers" << setw(9) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	for (unsigned int i = 0; i < cUser.size(); i++) {
		if (cUser[i].userID != 0) {
			cout << "-----------------------------------------------" << endl;
			cout << "Customer ID: " << cUser[i].userID << "\tCustomer name: " << cUser[i].name << endl;
		}
	}
	cout << "-----------------------------------------------" << endl;
	cout << endl;
}

//this function aimes to let the keeper to show all the warehouse information
void DataBase::showWarehouseInfo()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(30) << "Display all warhouses" << setw(9) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << "\n" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Number\tType\tTotal container\tEmpty container" << endl;
	cout << 1 << "\tLarge" << "\t500" << "\t\t" << emptyContainer(1) <<endl;
	cout << 2 << "\tLarge" << "\t500" << "\t\t" << emptyContainer(2) <<endl;
	cout << 3 << "\tSmall" << "\t400" << "\t\t" << emptyContainer(3) <<endl;
	cout << 4 << "\tSmall" << "\t400" << "\t\t" << emptyContainer(4) <<endl;
	cout << 5 << "\tSmall" << "\t400" << "\t\t" << emptyContainer(5) <<endl;
	cout << 6 << "\tSmall" << "\t400" << "\t\t" << emptyContainer(6) <<endl;
	cout << "-------------------------------------------------" << endl;
}

//this function aimes to let the keeper to search particular goods with id
void DataBase::searchGoods()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(30) << "Search current goods" << setw(9) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	bool found = false;
	cout << "----------------------------------" << endl;
	cout << "Please input ID of the Goods you want to search: " << endl;
	int gid = inputInteger();
	if (gid !=0) {
		for (unsigned int i = 0; i < goodsList.size(); i++) {
			if (goodsList[i].goodsId == gid) {
				cout << "----------------------------------" << endl;
				cout << "Goods is found." << endl;
				cout << "----------------------------------" << endl;
				cout << "Good ID\tSize\tStart time\tEnd time\tFee\tNotes" << endl;
				goodsList[i].goodsInfoDisplay();
				cout << "----------------------------------" << endl;
				cout << goodsList[i].containers.size() << " containers are occupied by this goods." << endl;
				cout << "----------------------------------" << endl;
				cout << "The occupied container list: " << endl;  //a goods must have corresponding container(s)
				cout << "Container ID\tRowNum\tColumnNum\tWarehouseNum\tContainer size" << endl;
				for (unsigned int j = 0; j < goodsList[i].containers.size(); j++) {
					goodsList[i].containers[j]->containerInfor();
				}
				cout << "----------------------------------" << endl;
				found = true;
			}
		}
	}
	if (found == false) {
		cout << "----------------------------------" << endl;
		cout << "Goods not found." << endl;
	}
}

//this function aimes to let the keeper to search particular customer with id
void DataBase::searchCustomer()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(32) << "Search current customer" << setw(7) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	bool found = false; 
	cout << "Please input ID of the Customer you want to search: ";
	int cid = inputInteger();
	if (cid !=0) {
		for (unsigned int i = 0; i < cUser.size(); i++) {
			if (cUser[i].userID == cid) {
				cout << "----------------------------------" << endl;
				cout << "Customer is found." << endl;
				cout << "----------------------------------" << endl;
				cout << "Customer id: " << cUser[i].userID << "\tCustomer name: " << cUser[i].name << endl;
				if (cUser[i].goods.size() == 1) {  //a customer may have 0, 1 or more goods
					cout << cUser[i].goods.size() << " item is stored." << endl;
				}
				else if (cUser[i].goods.size() == 0) {
					cout << cUser[i].goods.size() << " no item is stored." << endl;
				}
				else {
					cout << cUser[i].goods.size() << " items are stored." << endl;
				}
				if (cUser[i].goods.size() != 0) {
					cout << "----------------------------------" << endl;
					float Fee = cUser[i].getFee();
					cout << "Total fee: " << Fee << endl;
					cUser[i].displayGoods();
				}
				found = true;
			}
		}
	}
	
	if (found == false) {
		cout << "----------------------------------" << endl;
		cout << "Customer not found." << endl;
	}
}

//this function aimes to let the keeper to search particular container with id
void DataBase::searchContainer()
{
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(32) << "Search current container" << setw(7) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	bool found = false;
	cout << "Please input ID of the Container you want to search: ";
	int conid = inputInteger();
	cout << "----------------------------------" << endl;

	for (unsigned int i = 0; i < containerlist.size(); i++) {
		if (containerlist[i].containerId == conid) {
			cout << "Container ID: " << containerlist[i] .containerId <<endl;
			if (containerlist[i].isEmpty()) {  //a container can be empty
				cout << "It is empty" << endl;
			}
			else {
				cout << "It is not empty" << endl;
				cout << "It is storing the goods with ID: "<< containerlist[i].goodsId << endl;
			}
			containerlist[i].wareHouse();
			found = true;
		}
	}
	if (found == false) {
		cout << endl;
		cout << "Container not found." << endl;
		cout << "----------------------------------" << endl;
	}
}

//this function is used to convert string to integer
int DataBase::sToInt(string s)
{
	int i;
	stringstream ss;
	ss << s;
	ss >> i;
	return i;
}  //convert the string to int

//the constructor firstly read the file and ask the user to input a system time
DataBase::DataBase()
{
	readInfo();

	if (cUser.size()==0) {
		cout << " No customer is found. Please log in as a Keeper!" << endl;
	}

	string st;
	cout << "\n" << endl;
	cout << " Please input the System Time with format YYYY/MM/DD: ";
	getline(cin, st);

	while (systemTime.checkTime(st) != true) {  //reject invalid system time
		cout << " ----------------------------------" << endl;
		cout << " Invalid date. please input again" << endl;
		cout << endl;
		cout << " Please input the System Time (format YYYY/MM/DD): ";
		getline(cin, st);
	}
	systemTime = Time(st);
}

//default destructor
DataBase::~DataBase()
{
}
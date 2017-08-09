#include "Customer.h"

//default contructor
Customer::Customer()
{
}

//normal constructor
Customer::Customer(int u, string p, string n)
{
	userID = u;
	password = p;
	name = n;
}

//set the goods vector in this class with the pointers of the goods with same userid of this object
void Customer::setGoods(vector<Goods>& g)
{
	for (unsigned int i = 0; i < g.size(); i++) {
		if (g[i].userId == userID && g[i].goodsId != 0) {
			goods.push_back(&g[i]);
		}
	}
	
}

//the function that needs to be done inside the class
void Customer::userInterface()
{
	int choose;
	cout << "Please choose function: " << endl;
	cout << "---------------------------" << endl;
	cout << "1. Browse current goods\n2. Modify current goods\n"
		<< "3. Check out current goods\n4. Modify personal information" << endl;
	cout << "---------------------------" << endl;
	choose = inputInteger();
	system("cls");

	switch (choose) {
	case 1:
		displayGoods();
		system("pause");
		break;
	case 2:
		displayGoods();
		changeGoodsInfo();
		system("pause");
		break;
	case 3:
		displayGoods();
		deleteGoods();
		system("pause");
		break;
	case 4:
		editInfo();
		system("pause");
		break;
	default:
		break;
	}
}

//the function that better done inside the class
void Customer::showUserInfo()
{
	cout << "  ------------------------------------------------------ " << endl;
	cout << " |\t\t\t\t\t\t\t|" << endl;
	cout << " |\t\t\tWelcome !\t\t\t|" << endl;
	cout << " |\t\tNice to see you again !\t\t\t|" << endl;
	cout << " |\t\t\t\t\t\t\t|" << endl;
	cout << " |\t\tCustomer: " << name << " !\t\t|" << endl;
	if (goods.size()==1) {
		cout << " |\t\tTotal goods: " << goods.size() << " item\t\t\t|" << endl;
	}
	else {
		cout << " |\t\tTotal goods: " << goods.size() << " items\t\t\t|" << endl;
	}
	float Fee = getFee();
	cout << " |\t\tTotal fee: " << Fee << "\t\t\t|" << endl;
	cout << " |\t\t\t\t\t\t\t|" << endl;
	cout << "  ------------------------------------------------------ " << endl;
	cout << endl;
}

//the function to list all the goods the customer has(the goods in the vector inside the class)
void Customer::displayGoods()
{
	cout << "-----------------------------------------------------------------" << endl;
	cout << "Good ID\tSize\tStart time\tEnd time\tFee\tNotes" << endl;
	for (unsigned int i = 0; i < goods.size(); i++) {
		goods[i]->goodsInfoDisplay();
	}
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;
}

//the fucntion to delete certain goods with id
//it is done by call the emptyContainer function inside the goods and erase it frome the goods vector
void Customer::deleteGoods()
{
	int ID;
	bool deleted = false;
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(28) << "Delete current goods" << setw(11) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	cout << "Please input ID of the Goods you want to delete: ";
	ID = inputInteger();

	for (unsigned int i = 0; i < goods.size(); i++) {
		if (ID == goods[i]->goodsId) {
			goods[i]->emptyContainer();
			goods.erase(goods.begin()+i);
			deleted = true;
		}
	}
	if (deleted == false) {
		cout << endl;
		cout << "----------------------------------" << endl;
		cout << "Your goods has not been found." << endl;
		cout << "----------------------------------" << endl;
		cout << "No goods has been deleted." << endl;
		cout << endl;
	}
	else {
		cout << endl;
		cout << "----------------------------------" << endl;
		cout << "Your goods has been successfully deleted." << endl;
		cout << "----------------------------------" << endl;
	}
}

//the function to change the goods information
void Customer::changeGoodsInfo()
{
	int ID;
	int choice;
	bool modified = false;
	cout << "  -------------------------------------- \t" << endl;
	cout << " |" << setw(28) << "Modify current goods" << setw(11) << "|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;
	cout << "Please input ID of the Goods you want to modify: ";
	ID = inputInteger();
	string str;
	Time t;
	for (unsigned int i = 0; i < goods.size(); i++) {
		if (ID == goods[i]->goodsId) {
			cout << endl;
			cout << "----------------------------------" << endl;
			cout << "Which part of goods you want to modify?" << endl;
			cout << "1.Goods information\n2.End time" << endl;
			cout << "----------------------------------" << endl;
			choice = inputInteger();
			switch (choice)
			{
			case 1:
				cout << "----------------------------------" << endl;
				cout << "Current Information: " << goods[i]->goodsInfo << endl;
				cout << "Please input new information: ";
				getline(cin, str);
				goods[i]->goodsInfo = str;
				cout << "----------------------------------" << endl;
				cout << "Goods Information successfully modified" << endl;
				modified = true;
			break;
			
			case 2:
				cout << "----------------------------------" << endl;
				cout << "Current End Time: " << goods[i]->endTime.display() << endl;
				cout << "Please input new End Time (format YYYY/MM/DD): " << endl;
				getline(cin, str);
				t = Time(str);

				if (t.checkTime(str)==true && t > goods[i]->startTime) {
					goods[i]->endTime = t;
					goods[i]->calFee();
					cout << "----------------------------------" << endl;
					cout << "End Time successfully modified" << endl;
					cout << "Current fee: " << goods[i]->fee << endl;
					modified = true;
				}
				else {
					cout << "----------------------------------" << endl;
					cout << "Invalid end time setting. Time not changed." << endl;	
					modified = true;
				}

			break;
			default:
				cout << "#######################" << endl;
				cout << "#    Invalid input!   #" << endl;
				cout << "#######################" << endl;
				system("pause");
			}
		}
	}

	if (modified == false) {
		cout << endl;
		cout << "----------------------------------" << endl;
		cout << "Error goods ID or invalid input." << endl;
		cout << "No goods information has been changed." << endl;
		cout << "----------------------------------" << endl;
		cout << endl;
		system("pause");
	}
}

//empty the whole customer, only be called by keeper
//it is done by delete all the goods and set the id to 0
void Customer::emptyCustomer()
{
	for (unsigned int i = 0; i < goods.size(); i++) {
		goods[i]->emptyContainer();
		goods.erase(goods.begin() + i);
	}
	userID = 0;
}

//the function to calculate and show the total fee
float Customer::getFee()
{
	float fee = 0;
	
	for (unsigned int i = 0; i < goods.size(); i++) {
		fee += goods[i]->fee;
	}
	return fee;
}

//the default destructor
Customer::~Customer()
{
}

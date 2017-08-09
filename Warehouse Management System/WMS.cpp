//This project aims to design a warehouse management system (WMS) for the management of the warehouse.
//Designed by Ruichen Zheng
//Accomplished and tested by Ziheng Zhang
//It is the class containing the main function.

#include"DataBase.h"

int inputInteger(); //this external funtion ask user to input a integer by storing in string and return converted integer

int main() {
	cout << "  ------------------------------------------------------------------ " << endl;
	cout << " |" << setw(67) << "|" << endl;
	cout << " |" << setw(67) << "|" << endl;
	cout << " |" << setw(48) << "WareHouse Managing System 3.0" << setw(19) << "|" << endl;
	cout << " |" << setw(67) << "|" << endl;
	cout << " |" << setw(67) << "|" << endl;
	cout << "  ------------------------------------------------------------------ " << endl;

	DataBase db;
	cout << " ----------------------------------" << endl;
	system("pause");

	User* u;
	int choice;
	bool exit = false;
	string username, password;
	int login = 0, num;


	while (login == 0)
	{
		system("cls");
		cout << "  ------------------------------------ " << endl;
		cout << " |" << setw(37) << "|" << endl;
		cout << " |" << setw(27) << "Log in the system" << setw(10) << "|" << endl;
		cout << " |" << setw(37) << "|" << endl;
		cout << "  ------------------------------------ " << endl;
		cout << endl;
		cout << " Input your username: ";
		getline(cin,username);
		cout << " ------------------------------------" << endl;
		cout << " Input your password: ";
		getline(cin,password);
		cout << " ------------------------------------" << endl;
		cout << endl;
		num = db.userExist(username);

		if (num == -2)
		{
			cout << " #############################" << endl;
			cout << " #      No accounts found    #" << endl;
			cout << " #############################" << endl;
			cout << endl;
			cout << " #############################" << endl;
			cout << " Try again or exit the system?" << endl;
			cout << " 1. exit\n Otherwise login again" << endl;
			cout << " #############################" << endl;
			choice = inputInteger();
			if (choice == 1) {
				return 0;
			}
		}
		else
		{
			if (db.isPWCorrect(num, password))
			{
				login = 1;
				cout << "  ------------------------------------ " << endl;
				cout << " |" << setw(37) << "|" << endl;
				cout << " |" << setw(27) << "Login successfully" << setw(10) << "|" << endl;
				cout << " |" << setw(37) << "|" << endl;
				cout << "  ------------------------------------ " << endl;
				cout << endl;
				system("pause");
			}
			else
			{
				cout << " ############################" << endl;
				cout << " #       Wrong password!    #" << endl;
				cout << " ############################" << endl;
				cout << endl;
				cout << " #############################" << endl;
				cout << " Try again or exit the system?" << endl;
				cout << " 1. exit\n Otherwise login again" << endl;
				cout << " #############################" << endl;
				choice = inputInteger();
				if (choice == 1) {
					return 0;
				}
			}
			
		}
	}

	if (num == -1) {

		u = db.getKeeper();    
		//the pointer is used. The reason is that all the change done to this user should also be done on the keeper in database
			do {
				system("cls");
				u->showUserInfo();
				cout << "Please choose function: " << endl;
				cout << "---------------------------" << endl;
				cout << "1. Display all warehouses\n2. Display all customers\n3. Search container\n4. Search goods\n"
					<< "5. Search customers\n6. Add customer\n7. Delete customers\n"
					<< "8. Modify account information\n9. Log out" << endl;
				cout << "---------------------------" << endl;
				choice = inputInteger();

				system("cls");
				switch (choice) {
				case 1:
					db.showWarehouseInfo();  //show all warehouses
					break;
				case 2:
					db.listCustomer();  //delete customer
					break;
				case 3:
					db.searchContainer();  //show all customers
					break;
				case 4:
					db.searchGoods();  //search goods
					break;
				case 5:
					db.searchCustomer();  //search customer
					break;
				case 6:
					db.addCustomer();  //add customer
					break;
				case 7:
					db.deleteCustomer(); //delete customer
					break;
				case 8:
					u->userInterface(); //change account information
					break;
				case 9:
					cout << "------------------------" << endl;
					cout << "Are you sure to exit?" << endl;
					cout << "------------------------" << endl;
					cout << "1. Yes\nOtherwise No" << endl;
					cout << "------------------------" << endl;
					choice = inputInteger();
					if (choice == 1)
						exit = true;
					else
						exit = false;
					break;
				default:
					cout << " #######################" << endl;
					cout << " #    Invalid input!   #" << endl;
					cout << " #######################" << endl;
					break;
				}
				system("pause");
			} while (!exit);
	}
	else if (num >= 0) {

		u = db.getCustomer(num);  //the pointer is used. The reason is that all the change done to this user should also be done on the customer in database

		do {

			system("cls");
			u->showUserInfo();
			cout << "Please choose function: " << endl;
			cout << "-----------------------------" << endl;
			cout << "1. Check in new goods\n2. Check & modify goods information or user information\n3. Log out" << endl;
			cout << "-----------------------------" << endl;
			choice = inputInteger();
			system("cls");

			switch (choice) {
			case 1:
				db.addNewGoods(u->getID());  //add goods
				break;
			case 2:
				u->userInterface(); //other function
				break;
			case 3:
				cout << endl;
				cout << "Are you sure to exit?" << endl;
				cout << "------------------------" << endl;
				cout << "1.Yes\nOtherwise No" << endl;
				cout << "------------------------" << endl;
				choice = inputInteger();
				if (choice == 1)
					exit = true;
				else
					exit = false;
				break;
			default:
				cout << " #######################" << endl;
				cout << " #    Invalid input!   #" << endl;
				cout << " #######################" << endl;
				break;
			}
		} while (!exit);
	}
	else {
		cout << "No login. System eist. " << endl;
		cout << "--------------------------------------" << endl;
		return 0;
	}


	system("cls");
	cout << "--------------------------------------" << endl;
	cout << "Do you want to save all the changes? " << endl;
	cout << "--------------------------------------" << endl;
	cout << "1. Yes\nOtherwise No" << endl;
	cout << "--------------------------------------" << endl;
	choice = inputInteger();
	switch (choice) {
	case 1:
		db.saveData();
		cout << "--------------------------------------" << endl;
		cout << "Data have been saved successfully." << endl;
		break;
	default:
		cout << "--------------------------------------" << endl;
		cout << "You have not saved the changes." << endl;
		break;
	}
	return 0;
}

int inputInteger()
{
		string choice;
		int i;
		getline(cin, choice);
		stringstream ss;
		ss << choice;
		ss >> i;
		return i;
}

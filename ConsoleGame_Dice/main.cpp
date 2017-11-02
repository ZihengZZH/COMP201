#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "autotest.h"
#include "player.h"

using namespace std;

/*
The sequence of the game should be specified explicitly
maybe in the generic sequence with which they were created
*/


int main() {

	int player_num, auto_running;
	string player_name, line;
	vector<string> player_names;
	vector<player> players;
	vector<autoplayer> autoplayers;
	vector<int> gain_vals = { 5,10 };
	vector<int> throw_vals = { 2,3 };
	vector<int> point_vals = { 50,100 };

	cout << "---------------------------------------------\n"
		<< "| " << setw(30) << " DICE GAME FOR ELEC362" << setw(15) << "|\n"
		<< "---------------------------------------------\n"
		<< "It is a dice game called Pig, "
		<< "first described in print by John Scarne in 1945.\n"
		<< "This game supports automatical running with two strategies.\n"
		<< "First is to hold at specific gain and "
		<< "the other is to hold after specific number of throws\n"
		<< "------------------------------------------------------------\n"
		<< "Would you like to automatically run the program\n"
		<< "1 to confirm; others to cancel\n";
	getline(cin, line);
	stringstream ss(line);
	ss >> auto_running;

	if (auto_running != 1) {

		cout << "How many of you want to join in? ";
		
		cin >> player_num;
		while (cin.fail()) {
			cout << "Enter a valid integer. ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> player_num;
		}

		cout << endl;

		for (int i = 0; i < player_num; i++) {
			cout << "Please enter No " << i << " player name ";
			cin >> player_name;
			player_names.push_back(player_name);
		}

		player* start = new player("start");
		start->begin(player_names);
		
	}
	else {
		autotest* result = new autotest("start");
		result->statistics(gain_vals, throw_vals, point_vals);
	}

	system("pause");

	return 0;
}



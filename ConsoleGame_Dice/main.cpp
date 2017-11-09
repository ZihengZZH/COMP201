#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>
#include "autotest.h"
#include "player.h"

using namespace std;

/*
The sequence of the game should be specified explicitly
maybe in the generic sequence with which they were created
*/


int main() {

	// The variables for main functions
	int player_num, auto_running;
	string player_name, line;
	vector<string> player_names;
	vector<player> players;
	vector<autoplayer> autoplayers;

	// All the test conditions
	vector<int> gain_vals = { 5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 }; //20
	vector<int> throw_vals = { 1,2,3,4,5,6,7,8,9,10 }; //10
	vector<int> point_vals = { 50,100,150 }; //150
	// 16*10*11*5000 = 8,800,000
	
	cout << " --------------------------------------------\n"
		<< "| " << setw(30) << " DICE GAME FOR ELEC362" << setw(15) << "|\n"
		<< " --------------------------------------------\n"
		<< "It is a dice game called Pig, "
		<< "first described in print by John Scarne in 1945.\n"
		<< "This game supports automatical running with two strategies.\n"
		<< "First is to hold at specific gain and "
		<< "the other is to hold after specific number of throws\n"
		<< "------------------------------------------------------------\n"
		<< "Would you like to automatically run the program\n"
		<< "1 to confirm; others to cancel\n";

	// Receive the input securely
	getline(cin, line);
	stringstream ss(line);
	ss >> auto_running;

	if (auto_running != 1) {

		cout << "How many of you want to join in? ";
		// Receive a valid integer input
		cin >> player_num;
		while (cin.fail()) {
			cout << "Enter a valid integer. ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> player_num;
		}
		cout << endl;

		// Initialise the players with specified name
		for (int i = 0; i < player_num; i++) {
			cout << "Please enter No " << i << " player name ";
			cin >> player_name;
			player_names.push_back(player_name);
		}
		
		// Start the game
		player* start = new player("start");
		start->begin(player_names);

	}
	else {

		clock_t t;
		t = clock();

		// Start the auto game
		autotest* result = new autotest("start");
		result->statistics_ppl(gain_vals, throw_vals, point_vals);

		t = clock() - t;

		/* NOTICE
		There are two statistics functions to get the results of auto game
		One of them is called statistics, which runs the auto game in serial fashion and consumes time
		The other is called statistics_ppl, which runs the auto game in parallel fashion and saves time
		The statistics_ppl disable cout because parallel computing causes disorder in outstream
		*/

		printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

	}

	system("pause");

	return 0;
}

/*

36,000
parallel	38s
serial		80s

24,000
parallel	21s
serial		46s

2,400,000
parallel	2583s

*/
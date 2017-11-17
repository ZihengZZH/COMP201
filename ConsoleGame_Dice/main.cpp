#include <sstream>
#include <iomanip>
#include "autotest.h"
#include "autoplayer.h"
#include "player.h"

using namespace std;

/*
The sequence of the game should be specified explicitly
maybe in the generic sequence with which they were created
*/


// Function to receive a valid integer input
inline int get_integer(int min, int max, std::string prompt) {
	int ret_integer;
	string str_number;

	while (true) {
		cout << prompt;
		getline(cin, str_number); // Get string input
		stringstream convert(str_number); // Turn the string into a stream
		if (convert >> ret_integer && !(convert >> str_number) 
			&& ret_integer <= max && ret_integer >= min) 
			return ret_integer;
		cin.clear(); // In case an error occurs with cin (eof(), etc)
		cerr << "Input must be integer in range [" 
			<< min << "," << max << "]. Please try again.\n";
	}
}

// Function to show the conditions for auto test
inline void show_vector(vector<int> vec, string name) {

	cout << "\nThe conditions for " << name << " is as follows" << endl;
	for (auto i : vec) {
		cout << " " << i;
	}
	cout << endl;
}


int main() {

	// The variables for main functions
	int player_num, auto_running, gain_value, throw_value;
	string player_name, line;
	vector<string> player_names;
	vector<player> players;
	vector<autoplayer> autoplayers;

	// All the test conditions
	vector<int> gain_vals = { 5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 }; //20
	vector<int> throw_vals = { 1,2,3,4,5,6,7,8,9,10 }; //10
	vector<int> point_vals = { 50, 100, 150 }; //150
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
		<< "What game would you like to play\n"
		<< "1. multiplayer mode\n"
		<< "2. autoplayer mode\n"
		<< "other autotest the game\n";

	// Receive the input securely
	getline(cin, line);
	stringstream ss(line);
	ss >> auto_running;

	if (auto_running == 1) {

		player_num = get_integer(2, 20, "How many of you want to join in? ");
		cout << endl;

		// Initialise the players with specified name
		for (int i = 0; i < player_num; i++) {
			cout << "Please enter No " << i << " player name ";
			cin >> player_name;
			player_names.push_back(player_name);
		}

		// Start the game
		player* start = new player(player_names);
		start->begin();

	}
	else if (auto_running == 2) {

		gain_value = get_integer(1, 50, "Please input gain value for strategy GAIN ");
		throw_value = get_integer(1, 20, "Please input throw value for strategy THROW ");

		autoplayer* start = new autoplayer(gain_value, throw_value, 100);
		start->begin();
		 
	}
	else {

		clock_t t;
		t = clock();

		show_vector(gain_vals, "GAIN values");
		show_vector(throw_vals, "THROW values");
		show_vector(point_vals, "Point to win");

		// Start the auto game
		autotest* result = new autotest("start");
		result->statistics_ppl(gain_vals, throw_vals, point_vals);

		t = clock() - t;

		printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);


		/* NOTICE
		There are two statistics functions to get the results of auto game
		One of them is called statistics, which runs the auto game in serial fashion and consumes time
		The other is called statistics_ppl, which runs the auto game in parallel fashion and saves time
		The statistics_ppl disable cout because parallel computing causes disorder in outstream
		*/

	}

	system("pause");

	return 0;
}



/*

data scale	36,000
parallel	38s
serial		80s

data scale	24,000
parallel	21s
serial		46s

data scale	2,400,000
parallel	2583s

*/
#include "autoplayer.h"

autoplayer::autoplayer() {}

autoplayer::autoplayer(int gain_v, int throw_v, int point_v) {
	cout << "Start the auto game\n";
	// Create a autoplayer vector and fill in autoplayers
	autoplayers.push_back(autoplayer("GAINS", 0, false, 0, gain_v, point_v));
	autoplayers.push_back(autoplayer("THROWS", 1, true, throw_v, 0, point_v));
}

// Constructor to create an auto player
autoplayer::autoplayer(string input_name, int input_id, bool input_throws,
	int input_thrw, int input_gain, int input_points) : player(input_name, input_id) {
	throws = input_throws;
	throw_val = input_thrw;
	gain_val = input_gain;
	point_victory = input_points;
}

// Default destructor
autoplayer::~autoplayer(void) {}

// Function to determine if there is enough gain
bool autoplayer::enough_gain(vector<int>& cur) {
	int sum = 0;
	for (auto i : cur) {
		sum += i;
	}
	if (sum >= gain_val) return true;
	else return false;
}

// Function to run an auto game for autotest
void autoplayer::begin(void) {

	// Loop until there is any victory
	while (!is_victory_auto()) {
		// Sequence among players follows sequence of id
		for (int i = 0; i < autoplayers.size(); i++) {
			if (autoplayers[i].current) {
				autoplayers[i].auto_run();
				autoplayers[i].current = false;
				if (i != autoplayers.size() - 1)
					autoplayers[++i].current = true;
				else
					autoplayers[0].current = true;
				break;
			}
		}
	}
}

// Function to run the auto game
void autoplayer::auto_run(void) {
	srand(time(0)); // help in the generation of random numbers
	log = {}; // Log of current turns
	thrw = 0;
	cout << name << " YOUR CURRENT SCORE _" << get_sum(points) << "_\n";

	while (true) {
		cout << "Dice Rolling ... ";
		dice = rand() % 6 + 1; // Roll the dice
		cout << " Dice number _" << dice << "_" << endl;
		thrw += 1;

		// Fit two kinds of auto players (GAIN or THROW)
		if (dice == 1) {
			cout << "Dice is 1. Next turn \n";
			break;
		}
		else if (throws && thrw == throw_val) {
			points.push_back(get_sum(log));
			cout << "Hold the turn. Next turn \n";
			if (get_sum(points) >= point_victory) {
				victory = true;
				cout << "Congrats " << name << "! You win\n";
			}
			break;
		}
		else if (!throws && enough_gain(log)) {
			points.push_back(get_sum(log));
			cout << "Hold the turn. Next turn \n";
			if (get_sum(points) >= point_victory) {
				victory = true;
				cout << "Congrats " << name << "! You win\n";
			}
			break;
		}
		else {
			log.push_back(dice);
		}
	}
}

// Function to check if there is a victory
bool autoplayer::is_victory_auto(void) {
	bool any_victory = false;
	for (auto autoplayer : autoplayers) {
		any_victory |= autoplayer.victory;
		if (autoplayer.victory == true) winner = autoplayer.get_name();
	}
	// cout << "Any victory? " << boolalpha << victory << endl;
	return any_victory;
}

// Function to return winner name
string autoplayer::get_winner(void) {
	return winner;
}
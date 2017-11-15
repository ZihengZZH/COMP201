#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include "player.h"

using namespace std;

// Class autoplayer that is inherited from player
class autoplayer : public player {

private:
	// The private variables for class autoplayer
	int throw_val, gain_val, thrw;
	bool throws;
	vector<autoplayer> autoplayers;
	string winner;

public:
	// Default constructor
	autoplayer();
	// Constructor to start the auto game
	autoplayer(int gain_v, int throw_v, int point_v);
	// Constructor to create an auto player
	autoplayer(string input_name, int input_id, bool input_throws, int input_thrw,
		int input_gain, int input_points);
	// Default destructor
	~autoplayer();

	// Function to determine if there is enough gain
	bool autoplayer::enough_gain(vector<int>& cur);
	// Function to run an auto game for autotest
	void autoplayer::begin(void);
	// Function to run the auto game
	void autoplayer::auto_run(void);
	// Function to check if there is a victory
	bool autoplayer::is_victory_auto(void);
	// Function to return winner name
	string get_winner(void);

};
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

using namespace std;

class player {

protected:
	// The protected variables for class player
	// These variabls are only accessed within this class and inherited class
	int id, dice, point_victory;
	string input;
	string name;
	vector<int> log;
	vector<int> points;
	vector<player> players;

public:
	// The public variables for class player
	// These variables are accessed by other classes
	bool current;
	bool victory;

public:
	// Default constructor
	player();
	// Constructor to start the game
	player(string start);
	// Constructor to create a player
	player(string input_name, int input_id);
	// Default destructor
	~player(void);
	// Function to begin the game
	void begin(vector<string> player_names);
	// Function to run each turn of the game
	void run(void);
	// Function to display the score board of the game
	void display(void);
	// Function to calculate the sum of a vector
	int get_sum(vector<int>& nums);
	// Function to retrieve the name of a player
	string get_name(void);
	// Function to check if there is a victory
	bool is_victory(void);

};


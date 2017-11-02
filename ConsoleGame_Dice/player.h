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

	int id, dice, point_victory;
	string input;
	string name;
	vector<int> log;
	vector<int> points;
	vector<player> players;

public:
	bool current;
	bool victory;

public:
	player();
	player(string start);
	player(string input_name, int input_id);
	~player(void);
	void begin(vector<string> player_names);
	void run(void);
	int get_sum(vector<int>& nums);
	string get_name(void);
	bool is_victory(void);

};



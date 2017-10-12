#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <windows.h>

using namespace std;

class player {

public:
	int id;
	std::string name;
	vector<int> log;
	vector<int> points;

public:
	bool current;
	bool victory;

public:
	player(string input_name, int input_id);
	~player(void);
	void run(void);

	void show_list(vector<int>& nums);
	int get_sum(vector<int>& nums);


};



class autoplayer : public player {

private:
	int gain;
	bool always;
	vector<int> cur;

public:

	autoplayer(string input_name, int input_id, bool input_always) : player(input_name, input_id) {
		always = input_always;
		if (!always) {
			cout << "Please enter gain for each turn ";
			cin >> gain;
			cout << endl;
		}
	};

	~autoplayer(void) {};

	bool enough_gain(vector<int>& cur) {
		int sum = 0;
		for (auto i : cur) {
			sum += i;
		}
		if (sum >= gain) {
			return true;
		}
		else {
			return false;
		}
	};


	void auto_run(void) {
		srand(time(0));
		int dice;
		while (true) {
			cur = {};
			cout << name << " your current score is _" << get_sum(points) << "_\n";
			dice = rand() % 6 + 1;
			log.push_back(dice);
			cur.push_back(dice);
			Sleep(250);
			cout << "Dice number _" << dice << "_" << endl;
			if (dice == 1) {
				cout << "Next turn\n";
				break;
			}
			else {
				cout << "Keep rolling\n";
				points.push_back(dice);
			}

			if (!always && enough_gain(cur)) {
				cout << "Next turn\n";
				break;
			} 
			else if (get_sum(points) >= 100) {
				victory = true;
				cout << "Congrats " << name << "! You win\n";
				show_list(log);
				break;
			}
		}

	};


};
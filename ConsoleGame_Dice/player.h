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
	// WHEN input == 1, choose to hold
	int id, dice, input, point_victory;
	string name;
	vector<int> log;
	vector<int> points;

public:
	bool current;
	bool victory;

public:
	player();
	player(string input_name, int input_id);
	~player(void);
	void run(void);
	void show_list(vector<int>& nums);
	int get_sum(vector<int>& nums);
	string get_name(void);

};



class autoplayer : public player {

private:
	int num_throw, gain, thrw;
	bool throws;

public:

	autoplayer() {};

	autoplayer(string input_name, int input_id, bool input_throws, int input_thrw, int input_gain) : player(input_name, input_id) {
		throws = input_throws;
		num_throw = input_thrw;
		gain = input_gain;
	};

	~autoplayer(void) {};

	inline bool enough_gain(vector<int>& cur) {
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

	inline void auto_run(void) {
		srand(time(0));
		log = {};
		thrw = 0; 
		cout << name << " your current score is _" << get_sum(points) << "_\n";
		while (true) {
			dice = rand() % 6 + 1;
			thrw += 1;
			Sleep(100);
			cout << "Dice number _" << dice << "_" << endl;
			if (dice == 1) {
				cout << "Next turn \t";
				break;
			}
			else if (throws && thrw == num_throw) {
				cout << "Next turn \t";
				points.push_back(get_sum(log));
				if (get_sum(points) >= point_victory) {
					victory = true;
					cout << "Congrats " << name << "! You win\n";
				}
				break;
			}
			else if (!throws && enough_gain(log)) {
				cout << "Next turn \t";
				points.push_back(get_sum(log));
				if (get_sum(points) >= point_victory) {
					victory = true;
					cout << "Congrats " << name << "! You win\n";
				}
				break;
			} 
			else {
				cout << "Keep rolling\n";
				log.push_back(dice);
			}
		}
	};
};
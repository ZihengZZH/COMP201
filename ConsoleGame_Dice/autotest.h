#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <windows.h>
#include <ppl.h>
#include "player.h"

using namespace std;
using namespace concurrency;

// Global variable
vector<vector<int>> autotest_result;

// Class autoplayer that is inherited from player
class autoplayer : public player {

private:
	// The private variables for class autoplayer
	int num_throw, gain, thrw;
	bool throws;

public:
	// Default constructor
	autoplayer() {};

	// Constructor to create an auto player
	autoplayer(string input_name, int input_id, bool input_throws,
		int input_thrw, int input_gain, int input_points) : player(input_name, input_id) {
		throws = input_throws;
		num_throw = input_thrw;
		gain = input_gain;
		point_victory = input_points;
	};

	// Default destructor
	~autoplayer(void) {};

	// Function to determine if there is enough gain
	inline bool enough_gain(vector<int>& cur) {
		int sum = 0;
		for (auto i : cur) {
			sum += i;
		}
		if (sum >= gain) return true;
		else return false;
	};

	// Function to run the auto game
	inline void auto_run(void) {
		srand(time(0)); // help in the generation of random numbers
		log = {}; // Log of current turns
		thrw = 0;

		while (true) {
			dice = rand() % 6 + 1; // Roll the dice
			thrw += 1;

			// Fit two kinds of auto players (GAIN or THROW)
			if (dice == 1) {
				break;
			}
			else if (throws && thrw == num_throw) {
				points.push_back(get_sum(log));
				if (get_sum(points) >= point_victory) victory = true;
				break;
			}
			else if (!throws && enough_gain(log)) {
				points.push_back(get_sum(log));
				if (get_sum(points) >= point_victory) victory = true;
				break;
			}
			else {
				log.push_back(dice);
			}
		}
	};

};



// Class autotest to handle everything of auto game
class autotest {

private:
	// The private variables for class autotest
	int times, time, gain_wins, throw_wins;
	int gain_val, throw_val, point_val;
	autoplayer winner;
	vector<autoplayer> autoplayers;
	vector<vector<int>> autotest_data;

public:
	// Default constructor
	autotest() {};

	// Constructor to start the autotest
	autotest(string start) {
		if (start == "start")
			cout << "AUTO TEST RUNNING\n";
	}

	// Constructor to start one auto game of autotest
	autotest(int point_vic, int gain_v, int throw_v) {
		time = 0, gain_wins = 0, throw_wins = 0;
		gain_val = gain_v, throw_val = throw_v, point_val = point_vic;
		times = 5000;
		cout << "Auto test for " << times << " times begins\n";
	};

	// Default destructor
	~autotest() {};

	// Function to check if there is a victory
	inline bool is_victory_auto(vector<autoplayer>& players) {
		bool any_victory = false;
		for (auto player : players) {
			any_victory |= player.victory;
			if (player.victory == true) winner = player;
		}
		// cout << "Any victory? " << boolalpha << victory << endl;
		return any_victory;
	};

	// Function to get all the possible combinations of three conditions
	inline void get_combine(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		for (auto p : p_list) {
			for (auto g : g_list) {
				for (auto t : t_list) {
					autotest_data.push_back({ p,g,t });
				}
			}
		}
	}

	// Function to run an auto game for autotest
	inline void run() {

		autoplayer B("GAINS", 0, false, 0, gain_val, point_val);
		autoplayer C("THROWS", 1, true, throw_val, 0, point_val);
		autoplayers.push_back(B);
		autoplayers.push_back(C);

		// Loop until there is any victory
		while (!is_victory_auto(autoplayers)) {
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
	};

	// Function to begin the autotest for one condition combination 
	inline void begin() {

		// Run the auto game for specified times
		while (time < times) {
			autoplayers = {};
			run();
			if (winner.get_name() == "GAINS") ++gain_wins;
			else if (winner.get_name() == "THROWS") ++throw_wins;
			++time;
		}

		cout << "gain value " << gain_val << " throw value " << throw_val
			<< " point to win " << point_val << endl
			<< "Strategy of GAINS wins " << gain_wins <<
			" times and strategy of THROWS wins " << throw_wins <<
			" times. \n";

		// Store the parameters of one game
		autotest_result.push_back({ point_val,gain_val,throw_val,gain_wins,throw_wins });

	};

	// Function for statistical analysis in serial computational fashion
	inline void statistics(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		autotest_result = {};
		get_combine(g_list, t_list, p_list);
		for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			cout.setstate(ios_base::failbit); // Disable output
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		write_file();
	}

	// Function for statistical analysis in parallel computational fashion
	inline void statistics_ppl(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		autotest_result = {};
		get_combine(g_list, t_list, p_list);
		parallel_for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			cout.setstate(ios_base::failbit); // Disable output
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		write_file();
	}

	// Function to write the autotest result to text file for further analysis and visualisation
	inline void write_file(void) {
		ofstream outfile;
		outfile.open("autotest result.txt", ios::out | ios::in | ios::trunc);

		outfile << "Points\t\t" << "Gain_val\t" << "Throw_val\t"
			<< "Gain_win\t" << "Throw_win" << endl;

		for (auto res : autotest_result) {
			outfile << res[0] << "\t\t" << res[1] << "\t\t" << res[2] << "\t\t"
				<< res[3] << "\t\t" << res[4] << endl;
		}
	}

};
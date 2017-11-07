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

vector<vector<int>> autotest_result;


class autoplayer : public player {

private:
	int num_throw, gain, thrw;
	bool throws;

public:

	autoplayer() {};

	autoplayer(string input_name, int input_id, bool input_throws, 
		int input_thrw, int input_gain, int input_points) : player(input_name, input_id) {
		throws = input_throws;
		num_throw = input_thrw;
		gain = input_gain;
		point_victory = input_points;
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
		while (true) {
			dice = rand() % 6 + 1;
			thrw += 1;
			//Sleep(100);
			if (dice == 1) {
				break;
			}
			else if (throws && thrw == num_throw) {
				points.push_back(get_sum(log));
				if (get_sum(points) >= point_victory) {
					victory = true;
				}
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


class autotest {

private:
	int times, time, gain_wins, throw_wins;
	int gain_val, throw_val, point_val;
	autoplayer winner;
	vector<autoplayer> autoplayers;
	vector<vector<int>> autotest_data;

public:

	autotest(string start) {
		if (start == "start")
			cout << "AUTO TEST RUNNING\n";
	}

	autotest(int point_vic, int gain_v, int throw_v) {
		time = 0, gain_wins = 0, throw_wins = 0;
		gain_val = gain_v, throw_val = throw_v, point_val = point_vic;
		times = 1000;
		cout << "Auto test for " << times << " times begins\n";
	};

	~autotest() {};

	inline bool is_victory_auto(vector<autoplayer>& players) {
		bool any_victory = false;
		for (auto player : players) {
			any_victory |= player.victory;
			if (player.victory == true) winner = player;
		}
		// cout << "Any victory? " << boolalpha << victory << endl;
		return any_victory;
	};

	inline void get_combine(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		for (auto p : p_list) {
			for (auto g : g_list) {
				for (auto t : t_list) {
					autotest_data.push_back({ p,g,t });
				}
			}
		}
	}

	inline void run() {
		autoplayer B("GAINS", 0, false, 0, gain_val, point_val);
		autoplayer C("THROWS", 1, true, throw_val, 0, point_val);
		autoplayers.push_back(B);
		autoplayers.push_back(C);

		while (!is_victory_auto(autoplayers)) {

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

	inline void begin() {

		while (time < times) {
			autoplayers = {};
			run();
			if (winner.get_name() == "GAINS") ++gain_wins;
			else if (winner.get_name() == "THROWS") ++throw_wins;
			++time;
		}

		cout << "gain value " << gain_val <<" throw value " << throw_val 
			<< " point to win " << point_val << endl
			<< "Strategy of GAINS wins " << gain_wins <<
			" times and strategy of THROWS wins " << throw_wins <<
			" times. \n";
		
		autotest_result.push_back({ point_val,gain_val,throw_val,gain_wins,throw_wins });

	};

	inline void statistics(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		autotest_result = {};
		get_combine(g_list, t_list, p_list);
		for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		write_file();

	}

	inline void statistics_ppl(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		get_combine(g_list, t_list, p_list);
		parallel_for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			cout.setstate(ios_base::failbit);
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		write_file();

	}

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

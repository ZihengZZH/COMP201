#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include "player.h"

using namespace std;

class autotest {

private:
	int times, time, gain_wins, throw_wins;
	autoplayer winner;
	vector<autoplayer> autoplayers;

public:
	autotest() {
		time = 0, gain_wins = 0, throw_wins = 0;
		cout << "AUTO TEST RUNNING\n" <<
			"How many times would you like to simulate? ";
		cin >> times;
		cout << "Auto test for " << times << " times begins\n";
	};

	~autotest() {};

	inline bool is_victory_auto(vector<autoplayer>& players) {
		bool victory = false;
		for (auto player : players) {
			victory |= player.victory;
			if (player.victory == true) winner = player;
		}
		cout << "Any victory? " << boolalpha << victory << endl;
		return victory;
	};

	inline void run() {
		autoplayer B("GAINS", 0, false, 0, 10);
		autoplayer C("THROWS", 1, true, 3, 0);
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

	inline void statistics() {
		while (time < times) {
			autoplayers = {};
			run();
			if (winner.get_name() == "GAINS") ++gain_wins;
			else if (winner.get_name() == "THROWS") ++throw_wins;
			++time;
		}

		cout << "strategy of gains wins " << gain_wins <<
			" times and strategy of throws wins " << throw_wins <<
			" times. \n";

	};

};
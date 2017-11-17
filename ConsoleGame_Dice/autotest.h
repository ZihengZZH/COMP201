#pragma once
#include <fstream>
#include <cstdlib>
#include <thread>
#include <ppl.h>
#include "player.h"
#include "autoplayer.h"

using namespace std;
using namespace concurrency;


// Global variables
vector<vector<int>> autotest_result;


// Class autotest to handle everything of auto game
class autotest {

private:
	// The private variables for class autotest
	int times, time, gain_wins, throw_wins;
	int gain_val, throw_val, point_val;
	string winner;
	autoplayer* start;
	vector<vector<int>> autotest_data;

public:
	// Default constructor
	autotest() {};

	// Constructor to start the autotest
	autotest(string start) {
		if (start == "start")
			cout << "\nAUTO TEST RUNNING\n";
	};

	// Constructor to start one auto game of autotest
	autotest(int point_vic, int gain_v, int throw_v) {
		time = 0, gain_wins = 0, throw_wins = 0;
		gain_val = gain_v, throw_val = throw_v, point_val = point_vic;
		times = 5000;
		cout << "Auto test for " << times << " times begins\n";
	};

	// Default destructor
	~autotest() {};

	// Function to get all the possible combinations of three conditions
	void get_combine(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		for (auto p : p_list) {
			for (auto g : g_list) {
				for (auto t : t_list) {
					autotest_data.push_back({ p,g,t });
				}
			}
		}
	};

	// Function to begin the autotest for one condition combination 
	void begin(void) {

		// Run the auto game for specified times
		while (time < times) {
			start = new autoplayer(gain_val, throw_val, point_val);
			start->begin();
			winner = start->get_winner();
			if (winner == "GAINS") ++gain_wins;
			else if (winner == "THROWS") ++throw_wins;
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
	void statistics(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		vector<vector<int>> autotest_result;
		get_combine(g_list, t_list, p_list);
		for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			cout.setstate(ios_base::failbit); // Disable output
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		cout.clear();
		write_file();
	};

	// Function for statistical analysis in parallel computational fashion
	void statistics_ppl(vector<int> g_list, vector<int> t_list, vector<int> p_list) {
		vector<vector<int>> autotest_result;
		get_combine(g_list, t_list, p_list);
		parallel_for_each(autotest_data.begin(), autotest_data.end(), [](vector<int>& d) {
			cout.setstate(ios_base::failbit); // Disable output
			autotest A(d[0], d[1], d[2]);
			A.begin();
		});
		cout.clear();
		write_file();
	};

	// Function to write the autotest result to text file for further analysis and visualisation
	void write_file(void) {
		ofstream outfile;
		outfile.open("autotest result.txt", ios::out | ios::in | ios::trunc);

		outfile << "Points\t\t" << "Gain_val\t" << "Throw_val\t"
			<< "Gain_win\t" << "Throw_win" << endl;

		for (auto res : autotest_result) {
			outfile << res[0] << "\t\t" << res[1] << "\t\t" << res[2] << "\t\t"
				<< res[3] << "\t\t" << res[4] << endl;
		}
		cout << "AUTOTEST RESULT WRITTEN TO FILE SUCCESSFULLY" << endl;
	};

};

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
#include "autoplayer.h"

using namespace std;
using namespace concurrency;



// Class autotest to handle everything of auto game
class autotest {

private:

	// The private variables for class autotest
	int times, time, gain_wins, throw_wins;
	int gain_val, throw_val, point_val;
	string winner;
	autoplayer* start;
	vector<vector<int>> autotest_data;
	vector<vector<int>> autotest_result;

public:
	// Default constructor
	autotest();
	// Constructor to start the autotest
	autotest(string start);
	// Constructor to start one auto game of autotest
	autotest(int point_vic, int gain_v, int throw_v);
	// Default destructor
	~autotest();

	// Function to get all the possible combinations of three conditions
	void get_combine(vector<int> g_list, vector<int> t_list, vector<int> p_list);
	// Function to begin the autotest for one condition combination 
	void begin(void);
	// Function for statistical analysis in serial computational fashion
	void statistics(vector<int> g_list, vector<int> t_list, vector<int> p_list);
	// Function for statistical analysis in parallel computational fashion
	void statistics_ppl(vector<int> g_list, vector<int> t_list, vector<int> p_list);
	// Function to write the autotest result to text file for further analysis and visualisation
	void write_file(void);

};
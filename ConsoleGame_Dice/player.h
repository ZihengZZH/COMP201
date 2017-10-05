#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>

using namespace std;

class player {

private:	
	int id;
	std::string name;
	vector<int> points;

public:
	bool current;
	bool victory;

public:
	player(std::string input_name, int input_id);
	~player(void);
	void run(void);
	void show_list(vector<int>& nums);
	int get_sum(vector<int>& nums);


};
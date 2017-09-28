#pragma once
#include <iostream>
#include <vector>

class player {
	
private:
	std::string name;
	int id;
	bool choice;
	std::vector<int> points;

public:
	player(std::string input_name);
	~player(void);
	void run(void);
	int get_sum(std::vector<int>& nums);


};

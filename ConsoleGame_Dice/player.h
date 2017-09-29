#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>

class player {
	
private:
	std::string name;
	int id;
    bool victory;
	std::vector<int> points;

public:
	player(std::string input_name, int input_id);
    ~player(void);
    void main(void);
	void run(void);
	int get_sum(std::vector<int>& nums);


};
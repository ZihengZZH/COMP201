//
//  player.hpp
//  DiceGame
//
//  Created by Ziheng ZHANG on 05/10/2017.
//  Copyright © 2017 ZihengZZH. All rights reserved.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

// Not available for Xcode
//#include <windows.h>

using namespace std;

class player {
    
private:
    std::string name;
    vector<int> points;
    
public:
    int id;
    bool current;
    bool victory;
    
public:
    player(std::string input_name, int input_id);
    ~player(void);
    void run(void);
    void show_list(vector<int>& nums);
    int get_sum(vector<int>& nums);
    
    
};

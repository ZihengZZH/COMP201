//
//  player.cpp
//  DiceGame
//
//  Created by Ziheng ZHANG on 05/10/2017.
//  Copyright © 2017 ZihengZZH. All rights reserved.
//

#include "player.hpp"


player::player(string input_name, int input_id) {
    name = input_name;
    id = input_id;
    current = (input_id == 0) ? true : false;
    victory = false;
    cout << "player " << input_name << " has been created\n";
}

player::~player(void) {
    
}

void player::run(void) {
    int input, dice;
    cout << endl;
    while (true) {
        cout << name << " Your current score _" << get_sum(points)
        << "_ Hold the current score?\n"
        << "1 to hold; others to roll the dice ";
        cin >> input;
        if (input == 1) {
            current = false;
            cout << "Next turn\n";
            break;
        }
        cout << "Dice Rolling .... ";
        dice = rand() % 6 + 1;
        //Sleep(500); // Not available for Xcode
        cout << " Dice number _" << dice << "_" << endl;
        if (dice == 1) {
            current = false;
            cout << "Next turn\n";
            break;
        }
        else {
            cout << "Keep rolling\n";
            points.push_back(dice);
        }
        
        if (get_sum(points) >= 40) {
            victory = true;
            cout << "Congrats " << name << "! You win\n";
            break;
        }
    }
}

void player::show_list(vector<int>& nums) {
    for (auto num : nums) {
        cout << num << "-";
    }
    cout << endl;
    
}


int player::get_sum(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

#include <iostream>
#include <string>
#include "player.h"

using namespace std;

/*
 The sequence of the game should be specified explicitly
 maybe in the generic sequence with which they were created
 */


bool is_victory(vector<player>& players) {
    
    bool victory = false;
    for (auto player : players) {
        victory |= player.victory;
    }
    cout << "Any victory? " << boolalpha << victory << endl;
    return victory;
    
}


bool is_victory_auto(vector<autoplayer>& players) {
    
    bool victory = false;
    for (auto player : players) {
        victory |= player.victory;
    }
    cout << "Any victory? " << boolalpha << victory << endl;
    return victory;
    
}

int main() {
    
    int player_num, auto_run;
    string player_name;
    vector<player> players;
    vector<autoplayer> autoplayers;
    
    cout << "It is a multiplayer game and supports automatical running\n Would you like to automatical run the program\n 1 to confirm; others to cancel\n";
    cin >> auto_run;
    
    cout << "How many of you want to join in? ";
    cin >> player_num;
    cout << endl;
    
    if(auto_run != 1){
        
        for (int i = 0; i < player_num; i++) {
            cout << "Please enter No " << i << " player name ";
            cin >> player_name;
            player A(player_name, i);
            players.push_back(A);
        }
        
        while (!is_victory(players)) {
            
            for (int i = 0; i < players.size(); i++) {
                if (players[i].current) {
                    players[i].run();
                    players[i].current = false;
                    if (i != players.size() - 1)
                        players[++i].current = true;
                    else
                        players[0].current = true;
                    
                    break;
                }
            }
        }
    
    }else{
        
        for (int k = 0; k < player_num; k++){
            autoplayer B(to_string(k), k, false); // USE GAIN FOR LOOP STRATEGY
            autoplayers.push_back(B);
        }
        
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
    }
    
    
    
    
    system("pause");
    
    return 0;
}

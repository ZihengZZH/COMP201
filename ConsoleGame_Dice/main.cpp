#include <iostream>
#include <string>
#include "autotest.h"
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


int main() {

	int player_num, auto_running;
	string player_name;
	vector<player> players;
	vector<autoplayer> autoplayers;

	cout << "It is a multiplayer game and supports automatical running\n"
		<< "Would you like to automatical run the program\n"
		<<"1 to confirm; others to cancel\n";
	cin >> auto_running;

	if (auto_running != 1) {
		cout << "How many of you want to join in? ";
		cin >> player_num;
		cout << endl;
	}
	
	if (auto_running != 1) {

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
	}
	else {
		autotest result;
		result.statistics();
	}

	system("pause");

	return 0;
}
#include "player.h"

player::player() {}

player::player(string start) {
	if (start == "start")
		cout << "Start the game\n";
}

player::player(string input_name, int input_id) {
	name = input_name;
	id = input_id;
	current = (input_id == 0) ? true : false;
	point_victory = 100;
	victory = false;
	// cout << "player " << input_name << " has been created\n";
}

player::~player(void) {}

void player::begin(vector<string> player_names) {

	for (int j = 0; j < player_names.size(); j++) {
		player A(player_names[j], j);
		players.push_back(A);
	}

	while (true) {
		for (int i = 0; i < players.size(); i++){
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
		if (is_victory()) break;
	}

}

void player::run(void) {
	srand(time(0));
	cout << endl;
	log = {};
	cout << name << " Your current score _" << get_sum(points) << "_\nHold the turn total?";
	while (true) {
		cout << " 1 to hold; others to roll the dice ";
		getline(cin, input);
		if (input == "1") {
			cout << "Next turn \t";
			points.push_back(get_sum(log));
			// When points greater than 100
			if (get_sum(points) >= point_victory) {
				victory = true;
				cout << "Congrats " << name << "! You win\n";
			}
			break;
		}
		else {
			cout << "Dice Rolling ... ";
			dice = rand() % 6 + 1;
			Sleep(100);
			cout << " Dice number _" << dice << "_" << endl;
			if (dice == 1) {
				cout << "Next turn \t";
				break;
			}
			else {
				cout << "Keep rolling ";
				log.push_back(dice);
			}
		}
	}
}

int player::get_sum(vector<int>& nums) {
	int sum = 0;
	for (int num : nums) {
		sum += num;
	}
	return sum;
}

string player::get_name(void) {
	return name;
}

bool player::is_victory() {
	bool any_victory = false;
	for (auto player : players) {
		any_victory |= player.victory;
	}
	// cout << "Any victory? " << boolalpha << victory << endl;
	return any_victory;

}
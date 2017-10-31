#include "player.h"

player::player() {}

player::player(string input_name, int input_id) {
	name = input_name;
	id = input_id;
	current = (input_id == 0) ? true : false;
	point_victory = 20;
	victory = false;
	cout << "player " << input_name << " has been created\n";
}

player::~player(void) {}

void player::run(void) {
	srand(time(0));
	cout << endl;
	log = {};
	cout << name << " Your current score _" << get_sum(points) << "_\n Hold the turn total?";
	while (true) {
		cout << "1 to hold; others to roll the dice ";
		cin >> input;
		if (input == 1) {
			cout << "Next turn \t";
			points.push_back(get_sum(log));
			break;
		}
		cout << "Dice Rolling ... ";
		dice = rand() % 6 + 1;
		//Sleep(100);
		cout << " Dice number _" << dice << "_" << endl;
		if (dice == 1) {
			cout << "Next turn \t";
			break;
		}
		else {
			cout << "Keep rolling ";
			log.push_back(dice);
		}

		// When points greater than 100
		if (get_sum(points) >= point_victory) {
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

string player::get_name(void) {
	return name;
}
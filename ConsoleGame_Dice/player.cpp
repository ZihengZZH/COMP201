#include "player.h"

class player {

	player::player(std::string input_name) {


	}

	player::~player(void) {


	}

	void player::run(void) {


	}

	int player::get_sum(std::vector<int>& nums) {
		int sum = 0;
		for (int num : nums) {
			sum += num;
		}
		return sum;
	}

};
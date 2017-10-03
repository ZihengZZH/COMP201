#include "player.h"

player::player(std::string input_name, int input_id) {
    name = input_name;
    id = input_id;
    victory = false;
}

player::~player(void) {


}

void player::main(void){
    while (!victory){
        run();
    }

    std::cout << "Congratulations\n";

}



void player::run(void) {
    int input, dice;
    while (true) {
        std::cout << "Your current score " << get_sum(points) << "\nDo you want to hold the current score?\n";
        std::cout << "1 to hold; others to cancel\n";
        std::cin >> input;
        if (input == 1){
            std::cout << "Next turn\n";
            break;
        }
        std::cout << "Dice Rolling\n";
        dice = rand()%6+1;
        Sleep(1000);
        std::cout << "Dice number " << dice << std::endl;
        if (dice == 1){
            std::cout << "Next turn\n";
            break;
        }else{
	    std::cout<<"Keep rolling\n";
            points.push_back(dice);
        }

        if (get_sum(points) >= 100){
            victory = true;
            std::cout << "You win\n";
            break;
        }
    }
}

int player::get_sum(std::vector<int>& nums) {
	int sum = 0;
	for (int num : nums) {
		sum += num;
	}
	return sum;
}

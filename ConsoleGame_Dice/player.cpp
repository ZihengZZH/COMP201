#include "player.h"

// Default constructor
player::player() {}

// Constructor to start the game
player::player(string start) {
	if (start == "start")
		cout << "Start the game\n";
}

// Constructor to create a player
player::player(string input_name, int input_id) {
	name = input_name;
	id = input_id;
	current = (input_id == 0) ? true : false; // Detemine the start player
	point_victory = 100; // Declare the points to win in the game
	victory = false;
	cout << "player " << input_name << " has been created\n";
}

// Default destructor
player::~player(void) {}

// Function to begin the game
void player::begin(vector<string> player_names) {

	// Create a player vector and fill in players
	for (int j = 0; j < player_names.size(); j++) {
		player A(player_names[j], j);
		players.push_back(A);
	}

	// Loop the game until there is someone to win
	while (true) {
		system("CLS"); // Clear the screen
		display(); // Display the score board
		for (int i = 0; i < players.size(); i++) {
			// Sequence among players follows sequence of id
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
		// Any one winning to break the loop
		if (is_victory()) break; 
	}

}

// Function to run each turn of the game
void player::run(void) {
	srand(time(0)); // help in the generation of random numbers
	log = {}; // Log of current turn
	cout << name << " YOUR CURRENT SCORE _" << get_sum(points) << "_\n";
	
	while (true) {
		cout << "1 to hold; others to roll the dice ";
		cin >> input;

		if (input == "1") {
			cout << "Next turn \n";
			points.push_back(get_sum(log));

			// When points greater than points to win
			if (get_sum(points) >= point_victory) {
				victory = true;
				cout << "Congrats " << name << "! You win\n";
			}
			break;
		}
		else {
			cout << "Dice Rolling ... ";
			dice = rand() % 6 + 1; // Roll the dice
			Sleep(100);
			cout << " Dice number _" << dice << "_" << endl;
			
			if (dice == 1) {
				cout << "Next turn \n";
				Sleep(500);
				break;
			}
			else {
				cout << "Keep rolling ";
				log.push_back(dice);
			}
		}
	}
}

// Function to display the score board of the game
void player::display(void) {
	cout << " -------------   SCORE BOARD   -------------\n";
	cout << " -------------------------------------------\n";
	for (auto player : players) {
		cout << "\tPLAYER\t" << player.name << "\tTOTAL\t" << get_sum(player.points) << endl;
	}
	cout << " -------------------------------------------\n";
}

// Function to calculate the sum of a vector
int player::get_sum(vector<int>& nums) {
	int sum = 0;
	for (int num : nums) {
		sum += num;
	}
	return sum;
}

// Function to retrieve the name of a player
string player::get_name(void) {
	return name;
}

// Function to check if there is a victory
bool player::is_victory() {
	bool any_victory = false;
	for (auto player : players) {
		any_victory |= player.victory;
	}
	// cout << "Any victory? " << boolalpha << victory << endl;
	return any_victory;

}
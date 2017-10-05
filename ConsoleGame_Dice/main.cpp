#include <iostream>
#include <string>
#include "player.h"

using namespace std;


int main() {

	cout << "It is a biplayer game\n"
		<< "Please create two players\n";
	
	string player_1, player_2;
	cout << "Please enter name for player 1: ";
	cin >> player_1;
	cout << "Please enter name for player 2: ";
	cin >> player_2;

	player A(player_1, 0);
	player B(player_2, 1);

	while (!A.victory && !B.victory) {
		if (A.current) {
			A.run();
			B.current = true;
		}
		else if (B.current) {
			B.run();
			A.current = true;
		}
	}



	system("pause");

	return 0;
}
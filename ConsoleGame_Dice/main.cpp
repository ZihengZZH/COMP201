#include <iostream>
#include "player.h"

int main() {
	const vector<int> ids = {1,2,3,4,5,6,7,8,9,10};
	int pt = 0;
	
	player A("ZZH",ids[pt]);
	player B("SQ",ids[pt++]);
	
	A.main();
	B.main();

	return 0;
}

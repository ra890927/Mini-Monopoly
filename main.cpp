#include <time.h>
#include "Game.h"

int main(){
/*	WorldPlayer p(4);
	WorldMap m;
	m.printMap(p);
	MapUnit testMu = m.getMapUnitById(5);
	std::cout << testMu.getPrice() << std::endl;
	Player &testP = p.getPlayerById(1);
	testP.loseMoney(5000);
	// std::cout << test
	tP.getMoney() << std::endl;
	Player &testPP = p.getPlayerById(1);
	std::cout << testPP.getMoney() << std::endl;
	std::cout << testPP.getName() << std::endl; 
*/
	srand( time(NULL) );
	int numPlayer = 0;
	
	while( numPlayer < 1 || numPlayer > 4 ){
		std::cout << "Please enter player number (Min: 1, Max: 4)...>";
		std::cin >> numPlayer;
		std::cin.ignore();	
	}
	
	GameFlow monopoly(numPlayer);
	
	monopoly.play();
	
	return 0;
}

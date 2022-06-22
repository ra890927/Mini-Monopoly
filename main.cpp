#include <iostream>
#include <ctime>
#include "game.h"
using namespace std;

int main(){
	srand(time(nullptr));
	int numPlayer = 0;
	
	while( numPlayer < 1 || numPlayer > 4 ){
		cout << "Please enter player number (Min: 1, Max: 4)...> ";
		cin >> numPlayer;
		cin.ignore();
	}
	
	GameFlow monopoly(numPlayer);
	
	monopoly.play();
	
	return 0;
}

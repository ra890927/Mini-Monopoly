#include<iostream>
#include"player.h"
#include"unit.h"
using namespace std;

int main(){
	Player jason(13, "jason");

	cout << jason.get_id() << ' ' << jason.get_money() << endl;

	return 0;
}
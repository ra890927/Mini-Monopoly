#ifndef PLAYERUNIT__
#define PLAYERUNIT__

#include <iostream>
#include <vector>
#include <string>

class Player{
	public:
		Player(int, const std::string &);
		void loseMoney(int);
		void gainMoney(int);
		void addCity(int);
		void move(int, int);
		void setInJail();
		void setOutJail();
		void setPlayerOut();
		bool isBankrupt() const;
		int getId() const;
		int getMoney() const;
		int getPosition() const;
		int getOwnedCityNum() const;
		bool isInJail() const;
		bool isOut() const;
		const std::string getName() const;
		const std::vector<int> getOwnedCity() const;
	
	private:
		const int id_ = 0;
		int money_ = 0;
		int position_ = 0;
		bool inJail_ = false;
		bool out_ = false;
		const std::string name_;
		int ownedCityNum_ = 0;
		std::vector<int> ownedCity_;
		constexpr static int initMoney = 25000;
};

#endif

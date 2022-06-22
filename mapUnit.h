#ifndef MAPUNIT__
#define MAPUNIT__

#include <iostream>
#include <string>
#include <cstdio>
#include "player.h"
#include "worldPlayer.h"

class MapUnit
{
public:
	static constexpr Player *NOBODY = nullptr;

	MapUnit(char, int, const std::string &, int);
	bool isHost(const Player &) const;
	bool isBuyable() const;
	int getHostId() const;
	bool isJail() const;
	const std::string & getName() const;
	int getPrice() const;
	int getId() const;
	char getType() const;
	void boughtBy(Player &);
	
	virtual void upgradedBy(const Player & p){};
	virtual void collectedBy(const Player & p){};
	virtual void fineGuest(Player &){};
	virtual void release(){};

	virtual ~MapUnit(){
		delete host_;
	}
	virtual int getLevel(){
		return 0;
	};
	virtual int getNowFine() const {
		return 0;
	};
	virtual int getCollect() const {
		return 0;
	};
	virtual int getRandomCostFine() const {
		return 0;
	};

protected:
	const int id_ = 0;
	const int price_ = 0;
	const char type_ = 0;
	Player *host_ = NOBODY;
	const std::string name_;
};


class UpgradableUnit : public MapUnit
{
public:
	static constexpr int maxLevel = 5;
	static constexpr int minLevel = 1;

	UpgradableUnit(int, const std::string &, int, int, const int *);
	virtual ~UpgradableUnit();
	virtual void upgradedBy(const Player &);
	virtual void fineGuest(Player &);
	virtual void release();
	virtual int getLevel() const;
	virtual int getNowFine() const;
	int getUpgradePrice() const;

private: 
	int level_ = minLevel;
	const int upgradePrice_ = 0;
	const int *fineList_ = nullptr;
};


class CollectableUnit : public MapUnit
{
public:
	CollectableUnit(int, const std::string &, int, int);
	virtual int getCollect() const;
	virtual void collectedBy(const Player &);
	virtual void fineGuest(Player &);
	virtual void release();
	virtual int getNowFine() const;

private: 
	const int fine_ = 0;
	int collect_ = 0;
};

class RandomCostUnit : public MapUnit
{
public:
	RandomCostUnit(int, const std::string &, int, int);
	virtual void fineGuest(Player &, int);
	virtual int getNowFine() const;

private:  
	const int fine_ = 0;
};


class JailUnit : public MapUnit
{
public:
	JailUnit(int, const std::string &, int);
	void addPlayer(const Player &);
	void removePlayer(const Player &);

private:
	bool playerInJail[WorldPlayer::maxPlayerNum] = {0};
};

#endif

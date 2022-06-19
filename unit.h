#ifndef MAPUNIT__
#define MAPUNIT__

#include <iostream>
#include <string>
#include <stdio.h>
#include "player.h"

class MapUnit
{
public:	
	MapUnit(
		char type,
		int id,
		const std::string & name,
		int price 
	) : type_(type),
		id_(id),
		name_(name),
		price_(price) {}


	bool isHost(const Player & p) const;
	bool isBuyable() const;
	void vistiedBy(Player & p);
	int getHostId() const;
	bool isJail() const;
	const std::string & getName() const;
	int getPrice() const;
	char getType() const;
	void boughtBy(Player & p);

	virtual void upgradedBy(const Player & p) = 0;
	virtual void collectedBy(const Player & p) = 0;
	virtual void setDice(int dice) = 0;
	virtual void fineGuest() = 0;
	virtual void release() = 0;
	virtual int getLevel() const = 0;
	virtual int getNowFine() const = 0;
	virtual int getCollect() const = 0;
	virtual int getRandomCostFine() const = 0;

protected:
	Player *host_ = nullptr;
	Player *guest_ = nullptr;
	constexpr static Player *NOBODY = nullptr;
	const char type_ = 0;
	const int id_ = 0;
	const int price_ = 0;
	const std::string name_;
};


class UpgradableUnit : public MapUnit
{
public:

	constexpr static int maxLevel = 5;
	constexpr static int minlevel = 1;

	UpgradableUnit(
		int id, 
		const std::string & name,
		int price,
		int upgradePrice,
		const int *fineOfLevel
	) : MapUnit('U', id, name, price), 
		upgradePrice_(upgradePrice), 
		fineList_(fineOfLevel) {}

	virtual void upgradedBy(const Player & p);	
	virtual void fineGuest();
	virtual void release();	
	virtual int getLevel() const;	
	virtual int getNowFine() const;

	~UpgradableUnit() { delete[] fineList_; }

private: 
	const int upgradePrice_ = 0;
	const int *fineList_ = 0;
	int level_ = minlevel;	
};


class CollectableUnit : public MapUnit
{
public:

	CollectableUnit(
		int id, 
		const std::string & name,
		int price,
		int fine
	) : MapUnit('C', id, name, price),
		fine_(fine) {}

	virtual int getPrice() const;	
	virtual int getCollect() const;
	virtual void collectedBy(const Player & p);
	virtual void fineGuest();
	virtual void release();	
	virtual int getNowFine() const;

	~CollectableUnit() {}

private: 
	const int fine_ = 0;
	int collect_ = 0;
};


class RandomCostUnit  : public MapUnit
{
public:

	RandomCostUnit(
		const int id, 
		const std::string & name,
		const int price,
		const int fine
	) : MapUnit('R', id, name, price),
		fine_(fine) {}

	virtual void fineGuest();	
	virtual int getRandomCostFine() const;
	virtual void setDice(int dice);

	~RandomCostUnit() {}

private:  
	const int fine_=0;
	int dice_ = 0;
};


class JailUnit : public MapUnit
{
public:
	JailUnit(   
		int id, 
		const std::string & name,
		int price
	): MapUnit('J', id, name, price){}
	
	void addPlayer(const Player & p);
	void removePlayer(const Player & p);

	~JailUnit() {}

private:
	bool playerInJail[4] = {0};

};



#endif

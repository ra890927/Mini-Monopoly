#ifndef MAPUNIT__
#define MAPUNIT__

#include <iostream>
#include <string>
#include <stdio.h>
#include <set>
#include "player.h"

class MapUnit
{
public:	
	MapUnit(
		const char type,
		const int id,
		const std::string & name,
		const int price 
	) : type_(type),
		id_(id),
		name_(name),
		price_(price) {}


	bool isHost(const Player & p) const{
		return host->getId() == p.getId(); 
	}

	bool isBuyable() const{
		return ( !host && type_ != 'J' ) ? true : false; 
	}

	void vistiedBy(Player & p){
		guest = &p;
	}
	
	void leaveBy(Player & p){
		guest = NOBODY;
	}

	int getHostId() const { 
		return host->getId(); 
	}
	
	bool isJail() const { 
		return (type_ == 'J'); 
	}

	const std::string & getName() const { 
		return name_; 
	}

	int getPrice() const {
		return price_;
	}
	
	int getId() const { 
		return id_; 
	}
	
	char getType() const {
		return type_;
	}

	void boughtBy(Player & p){
		if( host == nullptr && !isJail() ){
			host = &p;
			host->loseMoney( price_ );
		}
	}
	virtual void upgradedBy(const Player & p){};
	virtual void collectedBy(const Player & p){};
	virtual void fineGuest() const {};
	virtual void fineGuest( int dice ) const {};
	virtual void release(){};
	virtual int getLevel(){};
	virtual int getNowFine() const {};
	virtual int getCollect() const {};
	virtual int getUpgradePrice(){};

protected:
	Player *host = nullptr;
	Player *guest = nullptr;
	constexpr static Player *NOBODY = nullptr;
	const char type_ = 0;
	const int id_ = 0;
	const int price_ = 0;
	const std::string name_;
};


class UpgradableUnit : public MapUnit
{
public:

	UpgradableUnit(
		const int id, 
		const std::string & name,
		const int price,
		const int upgradePrice_,
		const int *fine_of_level
	) : MapUnit('U', id, name, price), 
		level_(1),
		upgradePrice_(upgradePrice_), 
		fineList_(fine_of_level) {}

	virtual void upgradedBy(const Player & p) {
		if( host->getId() == p.getId() && level_ <= maxLevel ) { 
			host->loseMoney( upgradePrice_ ); 
			level_ += 1;
		}
	}
	
	virtual void fineGuest() const {
		guest->loseMoney( fineList_[level_-1] );
		host->gainMoney( fineList_[level_-1] );
	}

	virtual void release() { 
		host = NOBODY; 
		level_ = minlevel;
	}
	
	virtual bool isMaxLevel() { 
		return ( level_ == maxLevel ) ? true : false;
	}
	
	virtual int getLevel() { 
		return level_;
	}
	
	virtual int getUpgradePrice() { 
		return upgradePrice_;
	}
	
	virtual int getNowFine() const { 
		return fineList_[ level_ - 1 ] ;
	}
	
	constexpr static int maxLevel = 5, minlevel = 1;

	~UpgradableUnit() { delete[] fineList_; }

private: 
	const int upgradePrice_ = 0;
	const int *fineList_ = nullptr;
	int level_ = 1;	
};


class CollectableUnit : public MapUnit
{
public:

	CollectableUnit(
		const int id, 
		const std::string & name,
		const int price,
		const int fine
	) : MapUnit('C', id, name, price),
		collect_(0),
		fine_(fine) {}

	virtual int getPrice() const { 
		return price_; 
	}
	
	virtual int getCollect() const { 
		return collect_; 
	}

	virtual void collectedBy(const Player & p){
		if( host->getId() == p.getId() ){
			collect_ += 1;
		}
	}

	virtual void fineGuest() const {
		guest->loseMoney( fine_ * collect_ );
		host->gainMoney( fine_ * collect_ );
	}

	virtual void release() { 
		host = NOBODY; 
		collect_ = 0;
	}
	
	virtual int getNowFine() const { 
		return fine_ * collect_;
	}

private: 
	const int fine_=0;
	int collect_=0;
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

	virtual void fineGuest( int dice ) const {
		guest->loseMoney( fine_ * dice );
		host->gainMoney( fine_ * dice );
	}
	
	virtual void release() { 
		host = NOBODY; 
	}
	
	virtual int getNowFine() const { 
		return fine_;
	}

private:  
	const int fine_=0;
};


class JailUnit : public MapUnit
{
public:
	JailUnit(   
		const int id, 
		const std::string & name,
		const int price
	): MapUnit('J', id, name, price){}
	
	void addPlayer(const Player & p){ 
		playerInJail.insert( p.getId() ); 
	}
	void removePlayer(const Player & p){ 
		playerInJail.erase( p.getId() ); 
	}
	
	virtual int getNowFine() const { 
		return 0;
	}

private:
	std::set<int> playerInJail;

};

#endif

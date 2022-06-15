#ifndef MAPUNIT__
#define MAPUNIT__

#include<iostream>
#include<string>
#include<stdio.h>
#include<set>
#include "player.h"

class MapUnit
{
public:	
	MapUnit(
		const char & type,
		const int & id,
		const std::string & name,
		const int & price 
	) : type_(type),
		id_(id),
		name_(name),
		price_(price) {}


	bool isHost(const Player & p) const{
		return host->getId() == p.getId(); 
	}

	bool isBuyable() const{
		return host == NOBODY; 
	}

	virtual void release();

	void vistiedBy(Player & p){
		guest = &p;
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

	void boughtBy(Player & p){
		if( host == nullptr && !isJail() ){
			host = &p;
			host->loseMoney( price_ );
		}
	}
	virtual void upgradedBy(const Player & p);
	virtual void collectedBy(const Player & p);
	virtual void fineGuest();

protected:
	Player *host;
	Player *guest;
	constexpr static Player *NOBODY = nullptr;
	const char type_ = 0;
	const int id_ = 0, price_ = 0;
	const std::string name_;
};


class UpgradableUnit : public MapUnit
{
public:

	UpgradableUnit(
		const int & id, 
		const std::string & name,
		const int & price,
		const int & upgrade_price,
		const int *fine_of_level
	) : MapUnit('U', id, name, price), 
		upgrade_price_(upgrade_price), 
		fineList_(fine_of_level) {}

	virtual void upgradedBy(const Player & p){
		if( host->getId() == p.getId() && level_ <= maxLevel ){ 
			host->loseMoney( upgrade_price_ ); 
			level_ += 1;
		}
	}
	
	virtual void fineGuest(){
		guest->loseMoney( fineList_[level_-1] );
		host->loseMoney( fineList_[level_-1] );
	}

	virtual void release() { 
		host = NOBODY; 
		level_ = minlevel;
	}

private: 
	const int upgrade_price_;
	constexpr static int maxLevel = 5, minlevel = 1;
	const int *fineList_;
	int level_ = 1;	
};


class CollectableUnit : public MapUnit
{
public:

	CollectableUnit(
		const int & id, 
		const std::string & name,
		const int & price,
		const int & fine
	) : MapUnit('C', id, name, price),
		fine_(fine) {}

	virtual int getPrice() const { 
		return price_; 
	}

	virtual void collectedBy(const Player & p){
		if( host->getId() == p.getId() ){
			collect_ += 1;
		}
	}

	virtual void fineGuest(){
		guest->loseMoney( fine_ * collect_ );
		host->gainMoney( fine_ * collect_ );
	}

	virtual void release() { 
		host = NOBODY; 
		collect_ = 0;
	}

private: 
	const int fine_=0;
	int collect_=0;
};


class RandomCostUnit  : public MapUnit
{
public:

	RandomCostUnit(
		const int & id, 
		const std::string & name,
		const int & price,
		const int & fine
	) : MapUnit('R', id, name, price),
		fine_(fine) {}

	virtual void fineGuest(){
		guest->loseMoney( fine_ * dice );
		host->gainMoney( fine_ * dice );
	}

private: 
	int dice=0;   // dice 要從 gameflow取得
	const int fine_=0;
};


class JailUnit : public MapUnit
{
public:

	void addPlayer(const Player & p){ 
		playerInJail.insert( p.getId() ); 
	}
	void removePlayer(const Player & p){ 
		playerInJail.erase( p.getId() ); 
	}

private:
	std::set<int> playerInJail;

};



#endif
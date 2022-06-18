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
		char type,
		int id,
		const std::string & name,
		int price 
	) : type_(type),
		id_(id),
		name_(name),
		price_(price) {}


	bool isHost(const Player & p) const{
		return host_->getId() == p.getId(); 
	}

	bool isBuyable() const{
		return (host_) ? true : false; 
	}

	void vistiedBy(Player & p){
		guest_ = &p;
	}

	int getHostId() const { 
		return host_->getId(); 
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
	
	char getType() const {
		return type_;
	}

	void boughtBy(Player & p){
		if( host_ == nullptr && !isJail() ){
			host_ = &p;
			host_->loseMoney( price_ );
		}
	}
	virtual void upgradedBy(const Player & p) = 0;
	virtual void collectedBy(const Player & p) = 0;
	virtual void setDice(int dice) = 0;
	virtual void fineGuest() = 0;
	virtual void release() = 0;
	virtual int getLevel() = 0;
	virtual int getNowFine() = 0;
	virtual int getCollect() = 0;
	virtual int getRandomCostFine() = 0;

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
		int upgrade_price,
		const int *fine_of_level
	) : MapUnit('U', id, name, price), 
		upgrade_price_(upgrade_price), 
		fineList_(fine_of_level) {}

	virtual void upgradedBy(const Player & p) {
		if( host_->getId() == p.getId() && level_ <= maxLevel ) { 
			host_->loseMoney( upgrade_price_ ); 
			level_ += 1;
		}
	}
	
	virtual void fineGuest(){
		guest_->loseMoney( fineList_[level_-1] );
		host_->loseMoney( fineList_[level_-1] );
	}

	virtual void release() { 
		host_ = NOBODY; 
		level_ = minlevel;
	}
	
	virtual int getLevel() { 
		return level_;
	}
	
	virtual int getNowFine() { 
		return fineList_[level_-1];
	}

	~UpgradableUnit() { delete[] fineList_; }

private: 
	const int upgrade_price_ = 0;
	const int *fineList_ = 0;
	int level_ = 1;	
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

	virtual int getPrice() const { 
		return price_; 
	}
	
	virtual int getCollect() const { 
		return collect_; 
	}

	virtual void collectedBy(const Player & p){
		if( host_->getId() == p.getId() ){
			collect_ += 1;
		}
	}

	virtual void fineGuest(){
		guest_->loseMoney( fine_ * collect_ );
		host_->gainMoney( fine_ * collect_ );
	}

	virtual void release() { 
		host_ = NOBODY; 
		collect_ = 0;
	}
	
	virtual int getNowFine() { 
		return fine_ * collect_;
	}

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

	virtual void fineGuest(){
		guest_->loseMoney( fine_ * dice_ );
		host_->gainMoney( fine_ * dice_ );
	}
	
	virtual int getRandomCostFine() { 
		return fine_;
	}

	virtual void setDice(int dice) {
		dice_ = dice;
	}

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
	
	void addPlayer(const Player & p){ 
		playerInJail[p.getId()] = true;
	}
	void removePlayer(const Player & p){ 
		playerInJail[p.getId()] = false;
	}

private:
	bool playerInJail[4] = {0};

};



#endif

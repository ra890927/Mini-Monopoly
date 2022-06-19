#include "unit.h"

bool MapUnit::isHost(const Player & p) const{
	return host_->getId() == p.getId(); 
}

bool MapUnit::isBuyable() const{
	return (host_) ? true : false; 
}

void MapUnit::vistiedBy(Player & p){
	guest_ = &p;
}

int MapUnit::getHostId() const { 
	return host_->getId(); 
}
bool MapUnit::isJail() const { 
	return (type_ == 'J'); 
}

const MapUnit::std::string & getName() const { 
	return name_; 
}

int MapUnit::getPrice() const {
	return price_;
}

char MapUnit::getType() const {
	return type_;
}

void MapUnit::boughtBy(Player & p){
	if( host_ == nullptr && !isJail() ){
		host_ = &p;
		host_->loseMoney( price_ );
	}
}


void UpgradableUnit::upgradedBy(const Player & p) {
	if( host_->getId() == p.getId() && level_ <= maxLevel ) { 
		host_->loseMoney( upgradePrice_ ); 
		level_ += 1;
	}
}

void UpgradableUnit::fineGuest(){
	guest_->loseMoney( fineList_[level_-1] );
	host_->loseMoney( fineList_[level_-1] );
}

void UpgradableUnit::release() { 
	host_ = NOBODY; 
	level_ = minlevel;
}

int UpgradableUnit::getLevel() const{ 
	return level_;
}

int UpgradableUnit::getNowFine() const{ 
	return fineList_[level_-1];
}



int CollectableUnit::getPrice() const { 
	return price_; 
}

int CollectableUnit::getCollect() const { 
	return collect_; 
}

void CollectableUnit::collectedBy(const Player & p){
	if( host_->getId() == p.getId() ){
		collect_ += 1;
	}
}

void CollectableUnit::fineGuest(){
	guest_->loseMoney( fine_ * collect_ );
	host_->gainMoney( fine_ * collect_ );
}

void CollectableUnit::release() { 
	host_ = NOBODY; 
	collect_ = 0;
}

int CollectableUnit::getNowFine() const{ 
	return fine_ * collect_;
}


void RandomCostUnit::fineGuest(){
	guest_->loseMoney( fine_ * dice_ );
	host_->gainMoney( fine_ * dice_ );
}

int RandomCostUnit::getRandomCostFine() const { 
	return fine_;
}

void RandomCostUnit::setDice(int dice) {
	dice_ = dice;
}


void JailUnit::addPlayer(const Player & p){ 
	playerInJail[p.getId()] = true;
}
void JailUnit::removePlayer(const Player & p){ 
	playerInJail[p.getId()] = false;
}
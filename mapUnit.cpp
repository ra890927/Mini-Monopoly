#include "mapUnit.h"

MapUnit::MapUnit(
    char type,
    int id,
    const std::string & name,
    int price
) : type_(type),
    id_(id),
    name_(name),
    price_(price) {}


bool MapUnit::isHost(const Player & p) const{
    return host_->getId() == p.getId(); 
}

bool MapUnit::isBuyable() const {
    return (!host_ && type_ != 'J') ? true : false; 
}

int MapUnit::getHostId() const {
    return host_->getId(); 
}
bool MapUnit::isJail() const { 
    return (type_ == 'J'); 
}

const std::string & MapUnit::getName() const { 
    return name_; 
}

int MapUnit::getPrice() const {
    return price_;
}

int MapUnit::getId() const { 
    return id_; 
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

UpgradableUnit::UpgradableUnit(
    int id, 
    const std::string & name,
    int price,
    int upgrade_price,
    const int *fine_of_level
) : MapUnit::MapUnit('U', id, name, price), 
    upgradePrice_(upgrade_price), 
    fineList_(fine_of_level),
    level_(minLevel) {}

void UpgradableUnit::upgradedBy(const Player & p) {
    if( host_->getId() == p.getId() && level_ <= maxLevel ) { 
        host_->loseMoney( upgradePrice_ ); 
        level_ += 1;
    }
}

void UpgradableUnit::fineGuest(Player &guest){
    guest.loseMoney( fineList_[level_-1] );
    host_->gainMoney( fineList_[level_-1] );
}

void UpgradableUnit::release() { 
    host_ = NOBODY; 
    level_ = minLevel;
}

int UpgradableUnit::getLevel() const {
    return level_;
}

int UpgradableUnit::getNowFine() const { 
    return fineList_[level_-1];
}

int UpgradableUnit::getUpgradePrice() const {
    int nextLevel = level_ + 1 >= maxLevel ? maxLevel : level_ + 1;
    return fineList_[nextLevel - 1];
}

UpgradableUnit::~UpgradableUnit(){
    delete [] fineList_;
}

CollectableUnit::CollectableUnit(
    int id, 
    const std::string & name,
    int price,
    int fine
) : MapUnit::MapUnit('C', id, name, price),
    fine_(fine) {}

int CollectableUnit::getCollect() const { 
    return collect_; 
}

void CollectableUnit::collectedBy(const Player & p){
    if( host_->getId() == p.getId() ){
        collect_ += 1;
    }
}

void CollectableUnit::fineGuest(Player &guest){
    guest.loseMoney( fine_ * collect_ );
    host_->gainMoney( fine_ * collect_ );
}

void CollectableUnit::release() { 
    host_ = NOBODY; 
    collect_ = 0;
}

int CollectableUnit::getNowFine() const { 
    return fine_ * collect_;
}

RandomCostUnit::RandomCostUnit(
    int id, 
    const std::string & name,
    int price,
    int fine
) : MapUnit::MapUnit('R', id, name, price),
    fine_(fine) {}

void RandomCostUnit::fineGuest(Player &guest, int dice){
    guest.loseMoney( fine_ * dice );
    host_->gainMoney( fine_ * dice );
}

int RandomCostUnit::getNowFine() const { 
    return fine_;
}

JailUnit::JailUnit(   
    int id, 
    const std::string & name,
    int price
): MapUnit::MapUnit('J', id, name, price){}

void JailUnit::addPlayer(const Player & p){ 
    playerInJail[p.getId()] = true;
}
void JailUnit::removePlayer(const Player & p){ 
    playerInJail[p.getId()] = false;
}
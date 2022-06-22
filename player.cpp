#include "player.h"
#include <string>
#include <vector>

Player::Player( 
    int id , 
    const std::string &name 
) : id_(id),
    money_(initMoney),
    position_(0),
    inJail_(false),
    out_(false),
    name_(name) {}


void Player::loseMoney( int m ){
    money_ -= m;
}

void Player::gainMoney( int m ){
    money_ += m;
}

void Player::addCity( int cityId ){
    ownedCity_.push_back( cityId );
    ownedCityNum_ += 1;
}

void Player::move( int dicePoint , int numCity ){ 
    position_ += dicePoint;
    position_ %= numCity ;	
}

void Player::setInJail(){  
    inJail_ = true;
}

void Player::setOutJail(){ 
    inJail_ = false;
}

void Player::setPlayerOut(){
    out_ = true;
}

bool Player::isBankrupt() const {
    return ( money_ < 0 ) ? true : false;
}

int Player::getId() const {
    return id_;
}

int Player::getMoney() const {
    return money_;
}

int Player::getPosition() const {
    return position_;
}

int Player::getOwnedCityNum() const {
    return ownedCityNum_;
}

bool Player::isInJail() const {
    return inJail_;
}

bool Player::isOut() const {
    return out_;
}

const std::string Player::getName() const {
    return name_;
}

const std::vector<int> Player::getOwnedCity() const {
    return ownedCity_;
}
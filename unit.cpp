#include<iostream>
#include<string>
using namespace std;

/*
-----------------------------------For Testing-------------------------------------------
*/
class Player
{
friend class UpgradableUnit;
friend class CollectableUnit;
friend class RandomCostUnit;

public: 
	string name(){
		return name_;
	}
	bool equal_(const Player &p) const{
		return id_ == p.id_;
	}
	
private:
	int id_=10, location_=9, money_=8, num_units_=7;
	string name_="hello";
};

bool operator == (const Player & lhs, const Player & rhs) {
	return lhs.equal_(rhs);
}
/*
-------------------------------------------------------------------------------------------
*/
class MapUnit
{
//friend ostream & operator << (std::ostream &os, const MapUnit &mu);

public:
	
	void vistied_By(Player & p){
		guest = &p;
	}
	virtual void bought_By(Player & p){}	
	virtual void upgraded_By(const Player & p){}
	virtual void collected_By(const Player & p){}
	virtual void fine_Guest(){}

protected:
	Player *host;
	Player *guest;
};


// std::ostream & operator << (std::ostream &os, const MapUnit &mu) {
// 	os << "host: " << mu.host.name() << '\t' << "guest: " << mu.guest.name() << '\t' ;
// 	return os;
// }

class UpgradableUnit : public MapUnit
{
public:

	UpgradableUnit(int price, int u_price): price_(price), upgrade_price_(u_price){}
	// 不知道怎麼傳入 array 初始化 fine_[5]
	
	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host -> money_ -= price_;
		}
	}

	virtual void upgraded_By(const Player & p){
		if( host->id_ == p.id_ && level_ <= 5){
			host -> money_ -= upgrade_price_;
			level_ += 1;
		}
	}
	
	virtual void fine_Guest(){
		guest -> money_ -= fine_[level_-1];
		host -> money_ += fine_[level_-1];
	}

private: 
	int price_, upgrade_price_;
	int fine_[5];
	int level_ = 1;
};


class CollectableUnit : public MapUnit
{
public:

	CollectableUnit(int price, int fine):price_(price), fine_(fine){}

	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host -> money_ -= price_;
		}
	}

	virtual void collected_By(const Player & p){
		if( host->id_ == p.id_ ){
			collect_ += 1;
		}
	}

	virtual void fine_Guest(){
		guest -> money_ -= fine_ * collect_;
		host -> money_ += fine_ * collect_;
	}


private: 
	int price_, collect_=0;
	int fine_;
};


class RandomCostUnit  : public MapUnit
{
public:

	RandomCostUnit(int price, int fine):price_(price), fine_(fine){}

	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host -> money_ -= price_;
		}
	}

	virtual void fine_Guest(){
		guest -> money_ -= fine_ * dice;
		host -> money_ += fine_ * dice;
	}

private: 
	int price_, dice;   // dice 要從 gameflow取得
	int fine_;
};


class JailUnit : public MapUnit
{

};



int main(){
	


}

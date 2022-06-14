#ifndef MAPUNIT__
#define MAPUNIT__

#include<iostream>
#include<string>
#include"player.h"

class MapUnit
{
public:	
	bool isHost(const Player & p) const{
		return host->get_id() == p.get_id(); 
	}

	bool isBuyable() const{
		return host == NOBODY; 
	}

	void release() { 
		host = NOBODY; 
	}

	void vistied_By(Player & p){
		guest = &p;
	}

	int get_id() const { 
		return id_; 
	}

	int get_Host_id() const { 
		return host->get_id(); 
	}


	const std::string & get_Name() const { 
		return name_; 
	}

	virtual int get_Price() const ;
	virtual void bought_By(Player & p);	
	virtual void upgraded_By(const Player & p);
	virtual void collected_By(const Player & p);
	virtual void fine_Guest();

protected:
	Player *host;
	Player *guest;
	constexpr static Player *NOBODY = nullptr;
	const char TYPE = 0;
	const int id_ = 0, price_ = 0;
	const std::string name_;
};


class UpgradableUnit : public MapUnit
{
public:

	UpgradableUnit(int price, int u_price): price_(price), upgrade_price_(u_price){}
	// 不知道怎麼傳入 array 初始化 fine_[5]
	
	virtual int get_Price() const { 
		return price_; 
	}

	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host->lose_money( price_ );
		}
	}

	virtual void upgraded_By(const Player & p){
		if( host->get_id() == p.get_id() && level_ <= 5){ 
			host->lose_money( upgrade_price_ ); 
			level_ += 1;
		}
	}
	
	virtual void fine_Guest(){
		guest->lose_money( fine_[level_-1] );
		host->lose_money( fine_[level_-1] );
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

	virtual int get_Price() const { 
		return price_; 
	}

	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host->lose_money( price_ );
		}
	}

	virtual void collected_By(const Player & p){
		if( host->get_id() == p.get_id() ){
			collect_ += 1;
		}
	}

	virtual void fine_Guest(){
		guest->lose_money( fine_ * collect_ );
		host->gain_money( fine_ * collect_ );
	}


private: 
	int price_, collect_=0;
	int fine_;
};


class RandomCostUnit  : public MapUnit
{
public:

	RandomCostUnit(int price, int fine):price_(price), fine_(fine){}

	virtual int get_Price() const { 
		return price_; 
	}

	virtual void bought_By(Player & p){
		if( host == nullptr ){
			host = &p;
			host->lose_money( price_ );
		}
	}

	virtual void fine_Guest(){
		guest->lose_money( fine_ * dice );
		host->gain_money( fine_ * dice );
	}

private: 
	int price_, dice;   // dice 要從 gameflow取得
	int fine_;
};


class JailUnit : public MapUnit
{

};




#endif
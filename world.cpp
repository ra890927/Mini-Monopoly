#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

class Player{
	public:
		Player( int id , string name ){
			id_ = id ;
			money_ = 25000 ;
			position_ = 0 ;
			name_ = name ;
		//	owned_city_ 
		}
		
		void lose_money( int m ){
			money_ -= m ;
		}
		
		void gain_money( int m ){
			money_ += m ;
		}
		
		void add_city( int city_id ){
			owned_city_.push_back( city_id ) ;
		}
		
		void move( int dice_point ){
			position_ += dice_point ;
		}
		
		bool isbankrup() const {
			return ( money_ < 0 )?true:false ;
		}
		
		int get_id() const {
			return id_ ;
		}
		
		int get_money() const {
			return money_ ;
		}
		
		string get_name() const {
			return name_ ;
		}
		
		vector<int> get_owned_city() const {
			return owned_city_ ;
		}
	
	private:
		int id_ ;
		int money_ ;
		int position_ ;
		string name_ ;
		vector<int> owned_city_ ; // 擁有的city 
};

/*
--------Jason Yeah-----------我有改的會在後面加add-------------------------------------------
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
			//host -> money_ -= price_;
			host->lose_money( price_ ) ; //add
		}
	}

	virtual void upgraded_By(const Player & p){
		//if( host->id_ == p.id_ && level_ <= 5){
		if( host->get_id() == p.get_id() && level_ <= 5){ //add
			//host -> money_ -= upgrade_price_;
			host->lose_money( upgrade_price_ ) ; //add
			level_ += 1;
		}
	}
	
	virtual void fine_Guest(){
		//guest -> money_ -= fine_[level_-1];
		//host -> money_ += fine_[level_-1];
		guest->lose_money( fine_[level_-1] ) ; //add
		host->lose_money( fine_[level_-1] ) ;  //add
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
		//	host -> money_ -= price_;
			host->lose_money( price_ ) ; //add
		}
	}

	virtual void collected_By(const Player & p){
		//if( host->id_ == p.id_ ){
		if( host->get_id() == p.get_id() ){ //add
			collect_ += 1;
		}
	}

	virtual void fine_Guest(){
		//guest -> money_ -= fine_ * collect_;
		//host -> money_ += fine_ * collect_;
		cout<< "in~" <<endl ;
		guest->lose_money( fine_ * collect_ ) ; //add
		host->gain_money( fine_ * collect_ ) ;  //add
		cout<< "fine_guest" <<endl ;
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
			//host -> money_ -= price_;
			host->lose_money( price_ ) ; //add
		}
	}

	virtual void fine_Guest(){
	//	guest -> money_ -= fine_ * dice;
	//	host -> money_ += fine_ * dice;
		guest->lose_money( fine_ * dice ) ; //add
		host->gain_money( fine_ * dice ) ;  //add
	}

private: 
	int price_, dice;   // dice 要從 gameflow取得
	int fine_;
};

/*
--------Jason Yeah----------------------------------------------------------------
*/

class WorldPlayer{  //存人? 
	public:
		
	private:
		Player *units_[4] = {} ;
};

class WorldMap{
	public:
		void read_file(){
			ifstream in_file ( "map.txt" , ifstream::in ) ;
			string str ;
			int city_count = 0 ;
			
			while( getline( in_file , str ) ){
				stringstream ss(str) ;
				string tok ;
				vector<string> line_vector ;
				
				while( getline( ss , tok , ' ' ) ){
					line_vector.push_back( tok ) ;
				//	cout<< tok << endl ;
				}
				
			//	cout<< line_vector[2] <<" "<<line_vector[3] << endl ;
				
				if( line_vector[0] == "U" ){
					UpgradableUnit ucity( stoi( line_vector[2] ) , stoi( line_vector[3] ) ) ; // 應該也要傳[4]~[8] (fine[5]) 但UgradableUnit那邊說他有問題 我就牽拖 
					units_[ city_count ] = &ucity ;
					city_count += 1 ;		
				}
				else if( line_vector[0] == "C" ){
					CollectableUnit ccity( stoi( line_vector[2] ) , stoi( line_vector[3] ) ) ;
					units_[ city_count ] = &ccity ;
					city_count += 1 ;
				}
				else if( line_vector[0] == "R" ){
					RandomCostUnit rcity( stoi( line_vector[2] ) , stoi( line_vector[3] ) )	;
					units_[ city_count ] = &rcity ;
					city_count += 1 ;
				}
				else{
					cout<<"Wrong input!"<<endl ;
				} 
			}
			
			in_file.close() ;
		}
	private:
		MapUnit *units_[20] = {} ;
};

int main()
{	WorldMap m ;
	m.read_file() ;
	
	return 0 ; 
} 

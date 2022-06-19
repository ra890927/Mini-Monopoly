#ifndef PLAYERUNIT__
#define PLAYERUNIT__

#include <iostream>
#include <vector>
#include <string>

constexpr int maxPlayerNum = 4;
constexpr const char* defaultPlayerName[maxPlayerNum] = {"AoA", "Banana", "Cow boy", "Didi"};

class Player{
	public:
		Player( 
			int id , 
			const std::string &name 
		) : id_(id),
			money_(initMoney),
			position_(0),
			inJail_(false),
			//out_(false),
			name_(name) {}
		
		
		void loseMoney( int m ){
			// std::cout << money_ << std::endl;
			money_ -= m;
			// std::cout << money_ << std::endl;
		}
		
		void gainMoney( int m ){
			money_ += m;
		}
		
		void addCity( int cityId ){
			ownedCity_.push_back( cityId );
			ownedCityNum_ += 1;
		}
		
		void move( int dicePoint , int numCity ){ 
			position_ += dicePoint;
			position_ %= numCity ;	
		}
		
		void setInJail(){  
			inJail_ = true;
		}
		
		void setOutJail(){ 
			inJail_ = false;
		}
		
		void setPlayerOut(){
			out_ = true;
		}
		
		bool isBankrupt() const {
			return ( money_ < 0 ) ? true : false;
		}
				
	//	const bool isFinishRound() const {  
	//		return ( prevPosition_ > position_ ) ? true : false;
	//	} 
		
		int getId() const {
			return id_;
		}
		
		int getMoney() const {
			return money_;
		}
		
		int getPosition() const {
			return position_;
		}

		int getOwnedCityNum() const {
			return ownedCityNum_;
		}
		
		bool isInJail() const {
			return inJail_;
		}
		
		const bool isOut() const {
			return out_;
		}
		
		const std::string getName() const {
			return name_;
		}
		
		const std::vector<int> getOwnedCity() const {
			return ownedCity_;
		}
	
	private:
		const int id_ = 0;
		int money_ = 0;
		int position_ = 0;
		bool inJail_ = false;
		bool out_ = false;
		const std::string name_ ;
		int ownedCityNum_ = 0;
		std::vector<int> ownedCity_; // �֦���city 
		constexpr static int initMoney = 25000;
};

class WorldPlayer{
	public:
		WorldPlayer( int num ){
			numPlayer_ = num;
			
			for( int i = 0 ; i < num ; ++i ){
				std::string playerName;
				std::cout << "Please input player " << i+1 << "'s name (Default name is: " << defaultPlayerName[i] << "):";
				getline( std::cin , playerName );
				
				if( playerName.empty() ) playerName = defaultPlayerName[i];
				
				player.push_back(new Player( i , playerName ) );
				activePlayerId_.push_back(i);
			}			
		//	std::cout << player[1]->getName() << std::endl;
		//	std::cout << player[2]->getName() << std::endl;
		}
		
		~WorldPlayer(){
			for( int i = 0 ; i < numPlayer_ ; ++i ){
				delete player[i];
			}
		}
		
		Player& getPlayerById( int id ) const {
		//	std::cout << "getPlayerById" << std::endl;
			return *player[id];
		}
		
		void playerOut( int id ){
			player[id]->setPlayerOut(); 
		} 
		
		void decreNumPlayer(){
			numPlayer_ -= 1;
		}

		void deleteActive( int id ) {
			activePlayerId_.erase( activePlayerId_.begin() + id );
		}
		
		int getNumPlayer() const {
			return numPlayer_;
		}

		std::vector<int>getActivePlayerId() const {
			return activePlayerId_;
		}

		//constexpr static int maxPlayerNum_ = 5,
		
	private:
		int numPlayer_ = 0;
		std::vector<Player*> player;
		std::vector<int> activePlayerId_;
};

#endif

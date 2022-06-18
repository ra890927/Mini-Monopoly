#ifndef PLAYERUNIT__
#define PLAYERUNIT__

#include <iostream>
#include <vector>
#include <string>

constexpr int maxPlayerNum_ = 4;
constexpr const char* defaultPlayerName[maxPlayerNum_] = {"Player 1", "Player 2", "Player 3", "Player 4"};

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
		}
		
		void move( int dicePoint , int numCity ){ //嚙豎要嚙褒入city嚙踝蕭嚙窯嚙踝蕭 
			position_ += dicePoint;
			if( position_ > numCity - 1 ) position_ = position_ - numCity - 1 ;	
		}
		
		void setInJail(){ //嚙箠嚙褊綽蕭 
			inJail_ = true;
		}
		
		void setOutJail(){ //嚙碼嚙褊綽蕭 
			inJail_ = false;
		}
		
		const bool isBankrupt() const {
			return ( money_ < 0 ) ? true : false;
		}
				
	//	const bool isFinishRound() const {  //嚙瞌嚙稻嚙緬嚙盤嚙踝蕭嚙瘢 
	//		return ( prevPosition_ > position_ ) ? true : false;
	//	} 
		
		const int getId() const {
			return id_;
		}
		
		const int getMoney() const {
			return money_;
		}
		
		const int getPosition() const {
			return position_;
		}
		
		const bool isInJail() const {
			return inJail_;
		}
		
	/*	const bool isOut() const {
			return out_;
		}*/
		
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
	//	bool out_ = false;
		const std::string name_ ;
		std::vector<int> ownedCity_; // 嚙誰佗蕭嚙踝蕭city 
		constexpr static int initMoney = 25000;
};

class WorldPlayer{
	public:
		WorldPlayer( int num ){
			numPlayer_ = num;
			
			for( int i = 0 ; i < num ; ++i ){
				std::string name;
				std::cout << "Please input player " << i+1 << "'s name (Default name is: " << defaultPlayerName[i] << "):";
				getline( std::cin , name );
				 
				std::string playerName;
				
				if( name.empty() ) playerName = defaultPlayerName[i];
				else playerName = name;
				
				player.push_back(new Player( i , playerName ) );
			}			
		//	std::cout << player[1]->getName() << std::endl;
		//	std::cout << player[2]->getName() << std::endl;
		}
		
		Player& getPlayerById( int id ) const {
		//	std::cout << "getPlayerById" << std::endl;
			return *player[id];
		}
		
/*		void playerOut( int id ){
			player[id]->setPlayerOut(); 
		} */
		
		const int getNumPlayer() const {
			return numPlayer_;
		}
	private:
		int numPlayer_ = 0;
		std::vector<Player*> player;
};

#endif

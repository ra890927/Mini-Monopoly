#ifndef PLAYERUNIT__
#define PLAYERUNIT__

#include<iostream>
#include<vector>
#include<string>

constexpr int MAX_PLAYER_NUM = 4;
constexpr char const *DEFAULT_PLAYER_NAME[MAX_PLAYER_NUM] = {"Player 1","Player 2","Player 3","Player 4"};

class Player{
	public:
		Player( const int id , const std::string name ){
			id_ = id;
			money_ = initMoney;
			position_ = 0;
			prevPosition_ = 0;
			inJail_ = false;
			out_ = false;
			name_ = name;
		//	owned_city_ 
		}
		
		void loseMoney( const int m ){
			money_ -= m;
		}
		
		void gainMoney( const int m ){
			money_ += m;
		}
		
		void addCity( const int cityId ){
			ownedCity_.push_back( cityId );
		}
		
		void move( const int dicePoint , const int numCity ){ //需要傳入city的總數 
			prevPosition_ = position_;
			position_ += dicePoint;
			if( position_ > numCity - 1 ) position_ = position_ - numCity - 1 ;	
		}
		
		void setInJail( bool set ){ //傳入1進監獄 
			inJail_ = set;
		}
		
		void setPlayerOut( bool set ){ //傳入1將player淘汰出局 
			out_ = set;
		}
		
		const bool isBankrup() const {
			return ( money_ < 0 ) ? true : false;
		}
		
		const bool isFinishRound() const {  //是否通過原點 
			return ( prevPosition_ > position_ ) ? true : false;
		} 
		
		int getId() const {
			return id_;
		}
		
		int getMoney() const {
			return money_;
		}
		
		int getPosition() const {
			return position_;
		}
		
		bool isInJail() const {
			return inJail_;
		}
		
		bool isOut() const {
			return out_;
		}
		
		std::string getName() const {
			return name_;
		}
		
		std::vector<int> getOwnedCity() const {
			return ownedCity_;
		}
	
	private:
		int id_ = 0;
		int money_ = 0;
		int position_ = 0;
		int prevPosition_ = 0;
		bool inJail_ = false;
		bool out_ = false;
		std::string name_ ;
		std::vector<int> ownedCity_; // 擁有的city 
		constexpr static int initMoney = 25000;
};

class WorldPlayer{
	public:
		WorldPlayer( const int num ){
			numPlayer_ = num;
			
			for( int i=0 ; i<num ; ++i ){
				std::string name;
				std::cout << "Please input player " << i+1 << "'s name (Default name is: " << DEFAULT_PLAYER_NAME[i] << "):";
				getline( std::cin , name );
				
				std::string playerName;
				
				if( name.empty() ) playerName = DEFAULT_PLAYER_NAME[i];
				else playerName = name;
				
				Player *playerNode;
				playerNode = new Player( i , playerName );
				player.push_back( playerNode );
			}			
		//	std::cout << player[1]->getName() << std::endl;
		//	std::cout << player[2]->getName() << std::endl;
		}
		
		Player& getPlayerById( const int id ) const {
			return *player[id];
		}
		
		void playerOut( const int id ){
			player[id]->setPlayerOut(true); 
		}
		
		int getNumPlayer() const {
			return numPlayer_;
		}
	private:
		int numPlayer_ = 0;
		std::vector<Player*> player;
};

#endif

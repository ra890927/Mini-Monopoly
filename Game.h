#include <iostream>
#include <iomanip>
#include "worldMap.h"

constexpr int passAward = 500;

MapUnit& rollDice( Player& player , const WorldMap& worldMap ){
	int dicePoint = rand() % 6 + 1 ;
	std::cout << "The dice point is " << dicePoint << std::endl;

	if( dicePoint + player.getPosition() >= worldMap.getNumCity() ){
		player.gainMoney(passAward);
		std::cout << "Pass the origin point." << std::endl;
		std::cout << "You have gained $500!" << std::endl;
	}

	player.move( dicePoint , worldMap.getNumCity() );
	//std::cout << "roll finish";
	return worldMap.getMapUnitById( player.getPosition() );
}

void payFine( Player& player , Player& host , const MapUnit& city ){
	int dicePoint = 0 , fine = 0;
	
	if( city.getType() == 'R' ){
		dicePoint = rand() % 6 + 1 ;
		fine = dicePoint * city.getNowFine();
	}
	else{
		fine = city.getNowFine();
	}
	
	std::cout << "You have to pay " << host.getName() << " " << fine << " dollars" << std::endl;	
	
	if( city.getType() == 'R' ){
		city.fineGuest(dicePoint);
	}
	else{
		city.fineGuest();
	}

	system("pause");	
}

void buyCity( Player& player , MapUnit& city ){
	const int cityPrice = city.getPrice();
	
	if( cityPrice > player.getMoney() ){
		std::cout << "You're not afford to buy this city." << std::endl;	
		return;
	}
	
	std::cout << player.getName() << ": Do you want to buy " << city.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1)Yes [default](2)No ...>";
	std::cin >> option;
	
	if( option == 2 ) return;
	
	city.boughtBy(player);
	if( city.getType() == 'C' ) city.collectedBy(player);
	player.addCity(city.getId());

	std::cout << "You have paid " << cityPrice << " to buy " << city.getName() << std::endl;	
	system("pause");
}

void upgradeCity( Player& player , UpgradableUnit& uCity ){
	if( uCity.isMaxLevel() ){
		std::cout << "This city is already upgraded to max level." << std::endl;	
		return;
	}
	
	const int uPrice = uCity.getUpgradePrice();
	
	if( uPrice > player.getMoney() ){
		std::cout << "You're not afford to upgrade this city." << std::endl;	
		return;
	}
	
	std::cout << player.getName() << ": Do you want to upgrade " << uCity.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1)Yes [default] (2)No ...>";
	std::cin >> option;
	
	if( option == 2 ) return;
	
	uCity.upgradedBy(player);
	std::cout << "You have paid " << uPrice << " to upgrade " << uCity.getName() << " to lv." << uCity.getLevel() << std::endl;	
	system("pause");
}

void collectCity( Player& player , CollectableUnit& cCity ){
	const int cPrice = cCity.getPrice();
	
	if( cPrice > player.getMoney() ){
		std::cout << "You're not afford to collect this city." << std::endl;	
		return;
	}
	
	std::cout << player.getName() << ": Do you want to collect " << cCity.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1)Yes [default] (2)No ...>";
	std::cin >> option;

	if( option == 2 ) return;
	
	cCity.collectedBy( player );
	std::cout << "You have paid " << cPrice << " to collect " << cCity.getName() << " to number" << cCity.getLevel() << std::endl;	
	system("pause");
}

class GameFlow{
	public:
		GameFlow( 
			int numPlayer 
		) : state_(SET_UP),
			worldMap(),
			worldPlayer(numPlayer) {}
		
		enum State {
			SET_UP,
			CHECK_IS_IN_JAIL,
			UPDATE_UI,
			ROLL_DICE,
			GO_TO_JAIL,
			PAY_FINE,
			BUY_CITY,
			UPGRADE_CITY,
			COLLECT_CITY,
			CHECK_IS_BANKRUPT,
			CHECK_IS_GAMEOVER,
			NEXT_PLAYER,
			GAME_OVER
		};
		
		State cityOption( const MapUnit& city , const Player& currPlayer ){
			State nextState;
			//std::cout << "IN" << std::endl;
			if( city.isBuyable() ){
				nextState = BUY_CITY;
			}
			else if( city.isJail() ){
				std::cout<<"IN JAIL" << std::endl;
				nextState = GO_TO_JAIL;
			}
			else if( city.isHost(currPlayer) ){
				switch( city.getType() ){
					case 'U':
						nextState = UPGRADE_CITY;
						break;
					case 'C':
						nextState = COLLECT_CITY;
						break;
					case 'R':
						std::cout << "You've already owned this RandomCost City." << std::endl;
						system("pause");
						nextState = CHECK_IS_GAMEOVER;
						break;
					default:
						break;
				}
			}
			else{
				nextState = PAY_FINE;
			}
			
			return nextState;
		}
		
		void play();
		
	private:
		State state_ = SET_UP;
		const WorldMap worldMap;
		WorldPlayer worldPlayer;
};

void GameFlow::play() {
	int currPlayerId = 0;
	int winnerId = 0;
	
	for( state_ = SET_UP ; state_ != GAME_OVER ; ){
		switch(state_) {
			case SET_UP: {
				state_ = CHECK_IS_IN_JAIL;
				break;
			}
			case CHECK_IS_IN_JAIL: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				
				if( player.isInJail() ){
					player.setOutJail();
					state_ = NEXT_PLAYER;
				}
				else{
					state_ = UPDATE_UI;
				}
				
				break;
			}
			case UPDATE_UI: {
				system("cls"); 
				worldMap.printMap(worldPlayer);

				std::vector<int> activeList = worldPlayer.getActivePlayerId();
				for( int i = 0 ; i < worldPlayer.getNumPlayer() ; ++i ){
					Player &player = worldPlayer.getPlayerById(activeList[i]);
					std::cout << "[" << player.getId() << "]:" << std::setw(10) << player.getName() << " $" << std::setw(6) << player.getMoney();
					std::cout << " with " << player.getOwnedCityNum() << " units" << std::endl;
				}

				state_ = ROLL_DICE;
				break;
			}
			case ROLL_DICE: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				std::cout << player.getName() << "'s turn" << std::endl;
				
				int option = 0;
				std::cout << "Do you want to roll dice or quit" << std::endl;
				std::cout << "(1)roll dice [default](2)quit ...>";
				std::cin >> option;
				
				if( option == 2 ){
					std::cout << "Quit game." << std::endl;
					return;
				}	

				MapUnit &desCity = rollDice( player , worldMap );
				
				desCity.vistiedBy(player);
				state_ = cityOption( desCity , player );
				/*std::cout<< "Next state is:"<<state_<<std::endl;
				int tmp;
				std::cin>>tmp;
				std::cin.ignore();*/
				break;
			}
			case GO_TO_JAIL: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				const MapUnit &city = worldMap.getMapUnitById(player.getPosition());
				
				player.setInJail();
				std::cout << "You are put into jail." << std::endl;
				std::cout << "Fined $" << city.getPrice() << " dollars" << std::endl;
				player.loseMoney(city.getPrice());

				system("pause");
				state_ = NEXT_PLAYER;
				break;
			}
			case PAY_FINE: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				const MapUnit &city = worldMap.getMapUnitById(player.getPosition());
				Player &host = worldPlayer.getPlayerById(city.getHostId());			
				
				payFine( player , host , city );
				state_ = CHECK_IS_BANKRUPT;
				break;
			}
			case BUY_CITY: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				MapUnit &city = worldMap.getMapUnitById(player.getPosition());
				
				buyCity( player , city );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case UPGRADE_CITY: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				MapUnit &city = worldMap.getMapUnitById(player.getPosition());
				UpgradableUnit &uCity = dynamic_cast<UpgradableUnit &>(city);

				upgradeCity( player , uCity );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case COLLECT_CITY: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
				MapUnit &city = worldMap.getMapUnitById(player.getPosition());
				CollectableUnit &cCity = dynamic_cast<CollectableUnit &>(city);

				collectCity( player , cCity );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case CHECK_IS_BANKRUPT: {
				Player &player = worldPlayer.getPlayerById(currPlayerId);
								
				if( player.getMoney() < 0 ){
					std::vector<int> cityOwned = player.getOwnedCity();
				
					for( auto mapId : cityOwned ){
						MapUnit &city = worldMap.getMapUnitById(mapId);
						city.release();
					}

					worldPlayer.playerOut(currPlayerId);
					worldPlayer.deleteActive(currPlayerId);
					worldPlayer.decreNumPlayer();
					
					std::cout << player.getName() << " is bankrupt. Out." <<std::endl;
				/*	std::cout << "out:" <<currPlayerId<<std::endl;
					int tmp;
					std::cin>>tmp;
					std::cin.ignore();*/
				}

				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case CHECK_IS_GAMEOVER: {
				state_ = ( worldPlayer.getNumPlayer() > 1 ) ? NEXT_PLAYER : GAME_OVER ;
				break;
			}
			case NEXT_PLAYER: {
				currPlayerId += 1;
				currPlayerId %= maxPlayerNum ;
				
				while( worldPlayer.getPlayerById(currPlayerId).isOut() ){
					currPlayerId += 1;
					currPlayerId %= maxPlayerNum;	
				}
				
				state_ = CHECK_IS_IN_JAIL;
				break;
			}
			case GAME_OVER: {
				for( int i=0 ; i<4 ; ++i ){
					if( !worldPlayer.getPlayerById(i).isOut() ){
						winnerId = i ;
						break;
					}
				}
			
				break;
			}
		}
	}
	
	const Player &winner = worldPlayer.getPlayerById(winnerId);
	std::cout << "Congratulations!" << winner.getName() << "!" << std::endl;
	std::cout << "Winner is " << winner.getName() << "!" << std::endl;
}

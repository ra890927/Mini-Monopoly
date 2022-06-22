#include "game.h"

GameFlow::GameFlow( 
    int numPlayer 
) :	wm_("map.txt"),
	state_(SET_UP),
    wp_(numPlayer) {};

GameFlow::State cityOption( const MapUnit& city , const Player& currPlayer ){
    GameFlow::State nextState;
    if( city.isBuyable() ){
        nextState = GameFlow::State::BUY_CITY;
    }
    else if( city.isJail() ){
        std::cout<<"IN JAIL" << std::endl;
        nextState = GameFlow::State::GO_TO_JAIL;
    }
    else if( city.isHost(currPlayer) ){
        switch( city.getType() ){
            case 'U':
                nextState = GameFlow::State::UPGRADE_CITY;
                break;
            case 'C':
                nextState = GameFlow::State::COLLECT_CITY;
                break;
            case 'R':
                std::cout << "You've already owned this RandomCost City." << std::endl;
                nextState = GameFlow::State::CHECK_IS_GAMEOVER;
                system("pause");
                break;
            default:
                break;
        }
    }
    else{
        nextState = GameFlow::State::PAY_FINE;
    }
    
    return nextState;
}

MapUnit& rollDice( Player& player , const WorldMap& worldMap ){
	int dicePoint = rand() % 6 + 1 ;
	std::cout << "The dice point is " << dicePoint << std::endl;

	if( dicePoint + player.getPosition() >= worldMap.getNumCity() ){
		player.gainMoney(GameFlow::passAward);
		std::cout << "Pass the origin point." << std::endl;
		std::cout << "You have gained $" << GameFlow::passAward << "!" << std::endl;
	}

	player.move( dicePoint , worldMap.getNumCity() );
	return worldMap.getMapUnitById( player.getPosition() );
}

void payFine( Player& player , Player& host , MapUnit& city ){
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
		dynamic_cast<RandomCostUnit &>(city).fineGuest(player, dicePoint);
	}
	else{
		city.fineGuest(player);
	}

	system("pause");	
}

void buyCity( Player& player , MapUnit& city ){
	const int cityPrice = city.getPrice();
	
	if( cityPrice > player.getMoney() ){
		std::cout << "You're not afford to buy this city." << std::endl;
		system("pause");	
		return;
	}
	
	std::cout << player.getName() << ": Do you want to buy " << city.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1) Yes [default] (2) No ...> ";
	std::cin >> option;
	
	if( option == 2 ) return;
	
	city.boughtBy(player);
	if( city.getType() == 'C' ) city.collectedBy(player);
	player.addCity(city.getId());

	std::cout << "You have paid " << cityPrice << " to buy " << city.getName() << std::endl;	
	system("pause");
}

void upgradeCity( Player& player , UpgradableUnit& uCity ){
	if( uCity.getLevel() == UpgradableUnit::maxLevel ){
		std::cout << "This city is already upgraded to max level." << std::endl;
		system("pause");
		return;
	}
	
	const int uPrice = uCity.getUpgradePrice();
	
	if( uPrice > player.getMoney() ){
		std::cout << "You're not afford to upgrade this city." << std::endl;	
		return;
	}
	
	std::cout << player.getName() << ": Do you want to upgrade " << uCity.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1) Yes [default] (2) No ...> ";
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
		system("pause");
		return;
	}
	
	std::cout << player.getName() << ": Do you want to collect " << cCity.getName() << "?" << std::endl;	
	
	int option = 0;
	std::cout << "(1) Yes [default] (2) No ...> ";
	std::cin >> option;

	if( option == 2 ) return;
	
	cCity.collectedBy( player );
	std::cout << "You have paid " << cPrice << " to collect " << cCity.getName() << " to number " << cCity.getCollect() << std::endl;	
	system("pause");
}

void GameFlow::play() {
	int currPlayerId = 0;
	int winnerId = 0;
	
	while(state_ != GAME_OVER){
		switch(state_) {
			case SET_UP: {
				state_ = CHECK_IS_IN_JAIL;
				break;
			}
			case CHECK_IS_IN_JAIL: {
				Player &player = wp_.getPlayerById(currPlayerId);
				
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
				wm_.printMap(wp_);
				std::cout << std::endl;

				std::vector<int> activeList = wp_.getActivePlayerId();
				for( int i = 0 ; i < wp_.getNumPlayer() ; ++i ){
					const Player &player = wp_.getPlayerById(activeList[i]);
					std::cout << "[" << player.getId() << "]:" << std::setw(10) << player.getName() << " $" << std::setw(6) << player.getMoney();
					std::cout << " with " << player.getOwnedCityNum() << " units" << std::endl;
				}

				state_ = ROLL_DICE;
				break;
			}
			case ROLL_DICE: {
				Player &player = wp_.getPlayerById(currPlayerId);
				std::cout << '\n' << player.getName() << "'s turn" << std::endl;
				
				int option = 0;
				std::cout << "Do you want to roll dice or quit" << std::endl;
				std::cout << "(1) roll dice [default] (2) quit ...> ";
				std::cin >> option;
				std::cout << std::endl;
				
				if( option == 2 ){
					std::cout << "Quit game." << std::endl;
					return;
				}

				MapUnit &desCity = rollDice( player , wm_ );
				
				state_ = cityOption( desCity , player );
				break;
			}
			case GO_TO_JAIL: {
				Player &player = wp_.getPlayerById(currPlayerId);
				const MapUnit &city = wm_.getMapUnitById(player.getPosition());
				
				player.setInJail();
				std::cout << "You are put into jail." << std::endl;
				std::cout << "Fined $" << city.getPrice() << " dollars" << std::endl;
				player.loseMoney(city.getPrice());

				state_ = NEXT_PLAYER;
				system("pause");
				break;
			}
			case PAY_FINE: {
				Player &player = wp_.getPlayerById(currPlayerId);
				MapUnit &city = wm_.getMapUnitById(player.getPosition());
				Player &host = wp_.getPlayerById(city.getHostId());			
				
				payFine( player , host , city );
				state_ = CHECK_IS_BANKRUPT;
				break;
			}
			case BUY_CITY: {
				Player &player = wp_.getPlayerById(currPlayerId);
				MapUnit &city = wm_.getMapUnitById(player.getPosition());
				
				buyCity( player , city );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case UPGRADE_CITY: {
				Player &player = wp_.getPlayerById(currPlayerId);
				MapUnit &city = wm_.getMapUnitById(player.getPosition());
				UpgradableUnit &uCity = dynamic_cast<UpgradableUnit &>(city);

				upgradeCity( player , uCity );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case COLLECT_CITY: {
				Player &player = wp_.getPlayerById(currPlayerId);
				MapUnit &city = wm_.getMapUnitById(player.getPosition());
				CollectableUnit &cCity = dynamic_cast<CollectableUnit &>(city);

				collectCity( player , cCity );
				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case CHECK_IS_BANKRUPT: {
				const Player &player = wp_.getPlayerById(currPlayerId);
								
				if( player.getMoney() < 0 ){
					std::vector<int> cityOwned = player.getOwnedCity();
				
					for( auto mapId : cityOwned ){
						MapUnit &city = wm_.getMapUnitById(mapId);
						city.release();
					}

					wp_.playerOut(currPlayerId);
					wp_.deleteActive(currPlayerId);
					wp_.decreasePlayer();
					
					std::cout << player.getName() << " is bankrupt. Out." <<std::endl;
				}

				state_ = CHECK_IS_GAMEOVER;
				break;
			}
			case CHECK_IS_GAMEOVER: {
				state_ = ( wp_.getNumPlayer() > 1 ) ? NEXT_PLAYER : GAME_OVER ;
				break;
			}
			case NEXT_PLAYER: {
				currPlayerId += 1;
				currPlayerId %= WorldPlayer::maxPlayerNum;
				
				while( wp_.getPlayerById(currPlayerId).isOut() ){
					currPlayerId += 1;
					currPlayerId %= WorldPlayer::maxPlayerNum;
				}
				
				state_ = CHECK_IS_IN_JAIL;
				break;
			}
			case GAME_OVER: {
				for(int i = 0; i <= WorldPlayer::maxPlayerNum; ++i){
					if( !wp_.getPlayerById(i).isOut() ){
						winnerId = i ;
						break;
					}
				}
				break;
			}
		}
	}
	
	const Player &winner = wp_.getPlayerById(winnerId);
	std::cout << "Congratulations!" << winner.getName() << "!" << std::endl;
	std::cout << "Winner is " << winner.getName() << "!" << std::endl;
}
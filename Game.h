#ifndef GAMEFLOW__
#define GAMEFLOW__

#include <iomanip>
#include "worldMap.h"
#include "worldPlayer.h"

class GameFlow{
	public:
		static constexpr int passAward = 500;

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
		
		GameFlow(int);
		void play();
		
	private:
		State state_ = SET_UP;
		const WorldMap wm_;
		WorldPlayer wp_;
};

GameFlow::State cityOption(const MapUnit & , const Player &);
MapUnit & rollDice(Player &, const WorldMap &);
void payFine(Player &, Player &, MapUnit &);
void buyCity(Player &, MapUnit &);
void upgradeCity(Player &, UpgradableUnit &);
void collectCity(Player &, CollectableUnit &);

#endif
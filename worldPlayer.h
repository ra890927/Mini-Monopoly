#ifndef WORLD_PLAYER__
#define WORLD_PLAYER__

#include <string>
#include <vector>
#include "player.h"

class WorldPlayer{
	public:
		static constexpr int maxPlayerNum = 4;
		// static const std::string defaultPlayerName[WorldPlayer::maxPlayerNum];

		WorldPlayer(int);
		~WorldPlayer();
        Player & getPlayerById(int) const;
		void playerOut(int);
        void decreasePlayer();
		void deleteActive(int);
        int getNumPlayer() const;
        std::vector<int> getActivePlayerId() const;
		
	private:
		int numPlayer_ = 0;
		std::vector<Player*> playerList;
		std::vector<int> activePlayerId_;
};

const std::string defaultPlayerName[] = {"AoA", "Banana", "Cow boy", "Didi"};

#endif
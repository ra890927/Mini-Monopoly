#include "player.h"
#include "worldPlayer.h"

WorldPlayer::WorldPlayer( int num ){
    numPlayer_ = num;
    
    for( int i = 0 ; i < num ; ++i ){
        std::string playerName;
        std::cout << "Please input player " << i+1 << "'s name (Default name is: " << defaultPlayerName[i] << "):";
        getline( std::cin , playerName );
        
        if( playerName.empty() ) playerName = defaultPlayerName[i];
        
        playerList.push_back(new Player( i , playerName ) );
        activePlayerId_.push_back(i);
    }
}

WorldPlayer::~WorldPlayer(){
    while(!playerList.empty()){
        Player *playerUnit = playerList.back();
        playerList.pop_back();
        delete playerUnit;
    }
}

Player & WorldPlayer::getPlayerById( int id ) const {
    return *playerList[id];
}

void WorldPlayer::playerOut( int id ){
    playerList[id]->setPlayerOut(); 
} 

void WorldPlayer::decreasePlayer(){
    numPlayer_ -= 1;
}

void WorldPlayer::deleteActive( int id ) {
    activePlayerId_.erase( activePlayerId_.begin() + id );
}

int WorldPlayer::getNumPlayer() const {
    return numPlayer_;
}

std::vector<int> WorldPlayer::getActivePlayerId() const {
    return activePlayerId_;
}
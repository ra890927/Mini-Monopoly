#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "mapUnit.h"
#include "worldMap.h"
#include "worldPlayer.h"

WorldMap::WorldMap( std::string fileName){
    std::ifstream inFile ( fileName , std::ifstream::in );
    
    if( inFile.fail() ){
        std::cerr << "Open file fail!";
    }
    
    std::string inLine;
    int cityCount = 0;
    
    while( getline( inFile , inLine ) ){
        std::stringstream inputLine(inLine);
        
        char cityType = 0;
        std::string cityName;
        int cityPrice = 0;
        
        inputLine >> cityType;
        inputLine >> cityName;
        inputLine >> cityPrice;	

        switch( cityType ){
            case 'U': {
                int upgradePrice = 0;
                int *fineList = new int [UpgradableUnit::maxLevel] ;
            
                inputLine >> upgradePrice;
                for( int i = 0 ; i < UpgradableUnit::maxLevel ; ++i ) inputLine >> fineList[i];
        
                MapUnit *cityNode = new UpgradableUnit( cityCount , cityName , cityPrice , upgradePrice , fineList );
                mapList_.push_back( cityNode );
                cityCount += 1;
                break;
            }
            case 'C': {
                int fine = 0;
                inputLine >> fine;
            
                MapUnit *cityNode = new CollectableUnit( cityCount , cityName , cityPrice , fine );
                mapList_.push_back( cityNode );
                cityCount += 1;
                break;
            }
            case 'R': {
                int fine = 0;
                inputLine >> fine;
            
                MapUnit *cityNode = new RandomCostUnit( cityCount , cityName , cityPrice , fine );
                mapList_.push_back( cityNode );
                cityCount += 1;
                break;
            }	
            case 'J': {					
                MapUnit *cityNode = new JailUnit( cityCount , cityName , cityPrice );
                mapList_.push_back( cityNode );
                cityCount += 1;
                break;
            }
            default:
                std::cerr << "Error city type!";
                break;
        }
    }

    numCity_ = cityCount;						
    inFile.close();
}

WorldMap::~WorldMap(){
    while(!mapList_.empty()){
        MapUnit *mapUnit = mapList_.back();
        mapList_.pop_back();
        delete mapUnit;
    }
}

void WorldMap::printMap( const WorldPlayer& wp ) const { 
    for(int i = 0; i < numCity_ / 2; ++i){
        printMapInfo( wp , i );
        std::cout << "   ";
        printMapInfo( wp , numCity_ - i - 1 );
        std::cout << std::endl;
    }
} 

void WorldMap::printMapInfo( const WorldPlayer& wp , int index ) const {
    std::cout << "=";
    std::vector<int> activeList = wp.getActivePlayerId();
    for( int i = 0 ; i < wp.getNumPlayer() ; ++i ){
        if( wp.getPlayerById(activeList[i]).getPosition() == index ){
            std::cout << activeList[i];
        }
        else{
            std::cout << " ";
        }
    } 

    std::cout << "= [" << std::setw(2) << index << "]";
    std::cout << std::setw(10) << mapList_[index]->getName() << " ";
    
    if( mapList_[index]->isBuyable() || mapList_[index]->isJail() ) std::cout << "   ";
    else std::cout << "<" << mapList_[index]->getHostId() << ">";

    if( mapList_[index]->getType() == 'C' && !mapList_[index]->isBuyable() ){
        std::cout << " x" << mapList_[index]->getCollect() ;
    }
    else if( mapList_[index]->isBuyable() ){
        std::cout << " B$";
    }
    else if( mapList_[index]->isJail() ){
        std::cout << " J$";
    }
    else{
        std::cout << " U$";
    }
        
    if( mapList_[index]->isJail() ) std::cout << std::setw(5) << mapList_[index]->getPrice() << " ";
    else if( mapList_[index]->isBuyable() ) std::cout << std::setw(5) << mapList_[index]->getPrice() << " ";
    else std::cout << std::setw(5) << mapList_[index]->getNowFine() << " ";
        
    if( mapList_[index]->getType() == 'U' && !mapList_[index]->isBuyable() ){
        std::cout << "L" << dynamic_cast<UpgradableUnit *>(mapList_[index])->getLevel();
    }
    else{
        std::cout << "  ";
    }
}

int WorldMap::getNumCity() const {
    return numCity_;
}

MapUnit& WorldMap::getMapUnitById( int id ) const {
    return *mapList_[id];
}
#ifndef WORLDMAP__
#define WORLDMAP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include "unit.h"

class WorldMap{
	public:
		WorldMap( std::string fileName = "map.txt" ){
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
			//	std::cout<< lineVector[2] <<" "<<lineVector[3] << std::endl ;

				switch( cityType ){
					case 'U': {
						int upgradePrice = 0;
						int *fineList = new int [UpgradableUnit::maxLevel] ;
					
						inputLine >> upgradePrice;
						for( int i = 0 ; i < UpgradableUnit::maxLevel ; ++i ) inputLine >> fineList[i];
				
						MapUnit *cityNode = new UpgradableUnit( cityCount , cityName , cityPrice , upgradePrice , fineList );
						units_.push_back( cityNode );
						cityCount += 1;
						break;
					}
					case 'C': {
						int fine = 0;
						inputLine >> fine;
					
						MapUnit *cityNode = new CollectableUnit( cityCount , cityName , cityPrice , fine );
						units_.push_back( cityNode );
						cityCount += 1;
						break;
					}
					case 'R': {
						int fine = 0;
						inputLine >> fine;
					
						MapUnit *cityNode = new RandomCostUnit( cityCount , cityName , cityPrice , fine );
						units_.push_back( cityNode );
						cityCount += 1;
						break;
					}	
					case 'J': {					
						MapUnit *cityNode = new JailUnit( cityCount , cityName , cityPrice );
						units_.push_back( cityNode );
						cityCount += 1;
						break;
					}
					default:
						std::cerr << "Error city type!";
						break;
				}
			}

			numCity_ = cityCount;
			//for( int i = 0 ; i < numCity_ ; ++i ) std::cout<<" "<< units_[i]->getNowFine() ;
						
			inFile.close();
		}
		
		~WorldMap(){
			for( int i = 0; i < numCity_ ; ++i){
				delete units_[i];
			}
		}
		
		void printMap( const WorldPlayer& wp ) const { //�ݭn��player�ǤJ 
			for( int i=0 ; i<numCity_/2 ; ++i ){
				printMapInfo( wp , i );
				std::cout << "   ";
				printMapInfo( wp , numCity_-i-1 );
				std::cout << std::endl;
			}
		} 
		
		void printMapInfo( const WorldPlayer& wp , int index ) const {
			std::cout << "=";
			std::vector<int> activeList = wp.getActivePlayerId();
			for( int i = 0 ; i < wp.getNumPlayer() ; ++i )
			{	if( wp.getPlayerById(activeList[i]).getPosition() == index && !wp.getPlayerById(activeList[i]).isOut() ){
					std::cout << activeList[i];
				}
				else if( wp.getPlayerById(activeList[i]).isOut() ){
				}
				else{
					std::cout << " ";
				}
			} 
		
			std::cout << "= [" << std::setw(2) << index << "]";
			std::cout << std::setw(10) << units_[index]->getName() << " ";
			
			if( units_[index]->isBuyable() || units_[index]->isJail() ) std::cout << "   ";
			else std::cout << "<" << units_[index]->getHostId() << ">";
			
			if( units_[index]->getType() == 'C' && !units_[index]->isBuyable() ){
				std::cout << " x" << units_[index]->getCollect() ;
			}
			else if( units_[index]->isBuyable() ){
				std::cout << " B$";
			}
			else if( units_[index]->isJail() ){
				std::cout << " J$";
			}
			else{
				std::cout << " U$";
			}
				
			if( units_[index]->isJail() ) std::cout << std::setw(5) << units_[index]->getPrice() << " ";
			else if( units_[index]->isBuyable() ) std::cout << std::setw(5) << units_[index]->getPrice() << " ";
			else std::cout << std::setw(5) << units_[index]->getNowFine() << " ";
				
			if( units_[index]->getType() == 'U' && !units_[index]->isBuyable() ) std::cout << "L" << units_[index]->getLevel();
			else std::cout << "  ";
		}
		
		int getNumCity() const {
			return numCity_;
		}

		MapUnit& getMapUnitById( int id ) const {
			return *units_[id];
		}

	private:
		int numCity_ = 0;
		std::vector<MapUnit*> units_;
};

#endif

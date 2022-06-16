#ifndef WORLDMAP__
#define WORLDMAP__

#include<iostream>
#include<fstream>
#include<sstream>
#include"unit.h"

class WorldMap{
	public:
		void readFile(){
			std::ifstream inFile ( "map.txt" , std::ifstream::in );
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
			// 用id代表city的位置 這樣player的position就可以對到city	
				if( cityType == 'U' ){
					MapUnit *cityNode;
					int upgradePrice = 0;
					int fineList[UpgradableUnit::maxLevel] = {0};
					
					inputLine >> upgradePrice;
					for( int i=0 ; i<UpgradableUnit::maxLevel ; ++i ) inputLine >> fineList[i];
					
					cityNode = new UpgradableUnit( cityCount , cityName , cityPrice , upgradePrice , fineList );
					units_.push_back(cityNode);
					cityCount += 1;
				}
				else if( cityType == 'C' ){
					MapUnit *cityNode;
					int fine = 0;
					inputLine >> fine;
					
					cityNode = new CollectableUnit( cityCount , cityName , cityPrice , fine );
					units_.push_back(cityNode);
					cityCount += 1;
				}
				else if( cityType == 'R' ){
					MapUnit *cityNode;
					int fine = 0;
					inputLine >> fine;
					
					cityNode = new RandomCostUnit( cityCount , cityName , cityPrice , fine );
					units_.push_back(cityNode);
					cityCount += 1;
				}
				else if( cityType == 'J' ){
					MapUnit *cityNode;
					
					cityNode = new JailUnit( cityCount , cityName , cityPrice );
					units_.push_back(cityNode);
					cityCount += 1;
				}
				else{
					std::cout << "Wrong input!" << std::endl;
				} 
			}
			
			numCity_ = cityCount;
			
			inFile.close();
		}
		
		void printMap( std::vector<Player> player ) const { //將player傳入 
			for( int i=0 ; i<numCity_ ; ++i ){
			//	std::cout << 
			}
		}
		
		int getNumCity() const {
			return numCity_;
		}

	private:
		int numCity_ = 0;
		std::vector<MapUnit*> units_;
};

#endif

#ifndef WORLDMAP__
#define WORLDMAP__

#include <string>
#include "mapUnit.h"

class WorldMap{
	public:
		WorldMap(std::string);
		~WorldMap();
		void printMap(const WorldPlayer &) const;
		void printMapInfo(const WorldPlayer &, int) const;
		int getNumCity() const;
		MapUnit & getMapUnitById(int) const;

	private:
		int numCity_ = 0;
		std::vector<MapUnit*> mapList_;
};

#endif


#include "tile.hpp"

Tile::Tile(Type tileType, int x, int y, Map* map_) {
	xcoord = x;
	ycoord = y;
	type = tileType;
	tower = nullptr;
	map = map_;
}


int Tile::getx() const { return xcoord; }
int Tile::gety() const { return ycoord; }
int Tile::getType() const { return type; }
Tower* Tile::getTower() const { return tower; }
Map* Tile::getMap() const { return map; }

bool Tile::updateTower(Tower *newTower) {
	if (newTower == nullptr) return false;
	else { 
		tower = newTower;		//old tower may need to be erased?
		return true;
	}
}

bool Tile::removeTower() {
	tower = nullptr;
	return true;
}

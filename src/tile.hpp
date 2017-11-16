
#ifndef TILE
#define TILE

enum Type {
	Path,	//enemies walk on, can't place towers
	Grass,	//can build towers
	Water,	//can't build towers
	Undef
};




class Tower {
	public:
		Tower(int k) { test = k; }
	private:
		int test;
};

class Enemy {
	public:
		Enemy(int k) { test = k; }
	private:
		int test;
};

class Map;

class Tile {
	public:
		Tile(Type tileType, int x, int y, Map* map_);
		~Tile();
		int getx() const;
		int gety() const;
		int getType() const;
		Tower* getTower() const;
		Map* getMap() const;
		bool updateTower(Tower *newTower); // updates tower, true if succesful
		bool removeTower();		// sets tower to nullptr
		
	private:
		Map* map;
		Tower* tower;	//nullptr until changed
		Type type;
		int xcoord;
		int ycoord;
};






#endif

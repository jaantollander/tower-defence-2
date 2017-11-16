
#ifndef MAP
#define MAP

#include "tile.hpp"
#include <list>

class Map {
	public:
		Map(std::string map_name, int x_size, int y_size);
		~Map(); //map will handle destruction of towers, so tiles don't need to
		
		int xsize() const;
		int ysize() const;
		std::string name() const;
		std::vector<std::vector<Tile*>> tiles() const;
		std::vector<Enemy*> enemies() const;
		std::vector<Tower*> towers() const;
		
		Tile* getTile(int x, int y) const;
		
		bool load(const std::string& filename); //loads the tiles from a text file
		void printMap() const;
		
	private:
		std::string name_;
		int xSize;
		int ySize;
		std::vector<std::vector<Tile*>> tiles_;	//2D matrix of tiles
			//note that [0][0] is top-left corner
		std::vector<Enemy*> enemies_;	
		std::vector<Tower*> towers_;
		
};








#endif

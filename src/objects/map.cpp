
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "map.hpp"

Map::Map(std::string map_name, int x_size, int y_size) {
	name_ = map_name;
	xSize = x_size;
	ySize = y_size;
}

Map::~Map() { } //TODO

int Map::xsize() const { return xSize; }
int Map::ysize() const { return ySize; }
std::string Map::name() const { return name_; }
std::vector<std::vector<Tile*>> Map::tiles() const { return tiles_; }
std::vector<Enemy*> Map::enemies() const { return enemies_; }
std::vector<Tower*> Map::towers() const { return towers_; }
		
Tile* Map::getTile(int x, int y) const { return tiles_[y][x]; }
		
/**	mark grass as g, water as w and path as p
*	formatting for mapfiles :
*	name;xsize;ysize;
*	w;g;g;p;w;
*	w;g;p;p;q;
* 	g;g;p;w;w;
*	for example
*	formatting is easily changed if needed
*
*	this function loads a map from a textfile
*/
bool Map::load(const std::string& filename) {
	std::ifstream is(filename);
	if (is.fail()) return false;
	std::string name; std::string size; int xsize; int ysize;
	
	std::getline(is, name, ';');
	std::getline(is, size, ';');
	try { xsize = std::stoi(size, nullptr, 0); }
	catch (std::invalid_argument) { 
		std::cout << "invalid file format in Map::load" << std::endl; 
	}
	std::getline(is, size, ';');
	try { ysize = std::stoi(size, nullptr, 0); } 
	catch (std::invalid_argument) { 
		std::cout << "invalid file format in Map::load" << std::endl; 
	}
	xSize = ysize;
	ySize = xsize;
	name_ = name;
	tiles_.resize(xSize);
	int i = 0; 
	while (i < xSize) {
		tiles_[i].resize(ySize);
		i++;
	}
	std::cout << "ysize: " << tiles_.size() << std::endl;
	std::cout << "xsize: " << tiles_[0].size() << std::endl;
	
	i = 0; int j = 0;
	std::string type;
	std::getline(is, type, '\n');
	while (i < xSize) {
		while (j < ySize) {
			std::getline(is, type, ';');
			if (type == "g" || type == "G") {
				tiles_[i][j] = new Tile(Grass, j, i, this); }
			else if (type == "w" || type == "W") {
				tiles_[i][j] = new Tile(Water, j, i, this); }
			else if (type == "P" || type == "p") {
				tiles_[i][j] = new Tile(Path, j, i, this); }
			else tiles_[i][j] = new Tile(Undef, j, i, this);
			//Undef should never be read
			j++;
		}
		std::getline(is, type, '\n');
		j = 0;
		i++;
	}
	return true;
}

// just a test function to print map to console
void Map::printMap() const {
	int i = 0;
	int j = 0;
	while (i < xSize) {
		while (j < ySize) {
			if (tiles_[i][j] -> getType() == Grass) 
				std::cout << ".";
			else if (tiles_[i][j] -> getType() == Water) 
				std::cout << "~";
			else if (tiles_[i][j] -> getType() == Path) 
				std::cout << "#";
			else std::cout << "-";
			j++;
		}	
		j = 0;
		std::cout << std::endl;
		i++;
	}
}
















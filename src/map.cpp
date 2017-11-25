#include <algorithm>
#include <iostream>
#include <fstream>
#include "map.h"



GameMap::GameMap(const std::string name, int xsize, int ysize) :
    m_name(name), m_xsize(xsize), m_ysize(ysize) {
    Towers towers = {};
    Enemies enemies = {};
    m_towers = towers;
    m_enemies = enemies;
    // https://stackoverflow.com/questions/28663299/initializing-a-2d-vector
    Tiles tiles(ysize, std::vector<Tile*>(xsize, nullptr));
    m_tiles = tiles;
}

GameMap::GameMap(const std::string name, int xsize, int ysize, Tiles &tiles) :
    m_name(name), m_xsize(xsize), m_ysize(ysize), m_tiles(tiles)  {
    Towers towers = {};
    Enemies enemies = {};
    m_towers = towers;
    m_enemies = enemies;
}

// TODO
GameMap::~GameMap() {}


std::string GameMap::name() const { return m_name; }
int GameMap::xsize() const { return m_xsize; }
int GameMap::ysize() const { return m_ysize; }
Tiles GameMap::tiles() const { return m_tiles; }
Towers GameMap::towers() const { return m_towers; }
Enemies GameMap::enemies() const { return m_enemies; }
Tile* GameMap::get_tile(int x, int y) const { return m_tiles[y][x]; }
Tile* GameMap::get_tile(double x, double y) const {
    return m_tiles[int(y / tile_size)][int(x / tile_size)];
}


//TODO: direction
std::ostream& operator<<(std::ostream &os, GameMap &obj) {
    for (int y = 0; y < obj.ysize(); ++y) {
        for (int x = 0; x < obj.xsize(); ++x) {
            auto tile_type = obj.tiles()[y][x]->tile_type();
            switch (tile_type) {
                case grass: os << "g "; break;
                case water: os << "w "; break;
                case path: os << "p "; break;
                default: os << "u "; break;
            }
        }
        os << std::endl;
    }
    return os;
}


//TODO: custom exceptions
//TODO: converter for tile type string representation
GameMap load_game_map(const std::string &filename) {
    // Initialize GameMap constructor arguments
    std::string name, size;
    int xsize, ysize;

    std::ifstream is(filename);

    if (is.fail()) {
        throw std::exception();
    }

    // Read the name of the game map
    std::getline(is, name, ';');

    // Read xsize
    std::getline(is, size, ';');
    try {
        // Convert string to integer
        xsize = std::stoi(size, nullptr, 0);
    } catch (std::invalid_argument&) {
        //TODO: Invalid file format
        throw std::exception();
    }

    // Read ysize
    std::getline(is, size, ';');
    try {
        // Convert string to integer
        ysize = std::stoi(size, nullptr, 0);
    } catch (std::invalid_argument&) {
        //TODO: Invalid file format
        throw std::exception();
    }

    // Read tiles
    std::string type;
    std::getline(is, type, '\n');
    Tiles tiles(ysize, std::vector<Tile*>(xsize, nullptr));
    for (int y = 0; y < ysize; ++y) {
        for (int x = 0; x < xsize; ++x) {
            // Read the type of the tile
            std::getline(is, type, ';');
            if (type == "g" || type == "G") {
                tiles[y][x] = new Tile(x, y, grass, undefined_direction); }
            else if (type == "u" || type == "U") {
                tiles[y][x] = new Tile(x, y, water, undefined_direction); }
            else if (type == "n" || type == "N") {
                tiles[y][x] = new Tile(x, y, path, north); }
            else if (type == "s" || type == "S") {
                tiles[y][x] = new Tile(x, y, path, south); }
            else if (type == "w" || type == "W") {
                tiles[y][x] = new Tile(x, y, path, west); }
            else if (type == "e" || type == "E") {
                tiles[y][x] = new Tile(x, y, path, east); }
            else
                tiles[y][x] = new Tile(x, y, undefined_tile_type,
                                       undefined_direction);
            //Undef should never be read
        }
        std::getline(is, type, '\n');
    }

    return GameMap(name, xsize, ysize, tiles);
}

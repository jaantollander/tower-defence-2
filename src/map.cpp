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


std::ostream& operator<<(std::ostream &os, GameMap &obj) {
    for (int y = 0; y < obj.ysize(); ++y) {
        for (int x = 0; x < obj.xsize(); ++x) {
            auto tile = obj.tiles()[y][x];
            os << tile->tile_type() << tile->direction() << ";";
        }
        os << std::endl;
    }
    return os;
}


//TODO: converter for tile type string representation
GameMap game_map_from_file(const std::string &filename) {
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
        throw invalid_file_format("");
    }

    // Read ysize
    std::getline(is, size, ';');
    try {
        // Convert string to integer
        ysize = std::stoi(size, nullptr, 0);
    } catch (std::invalid_argument&) {
        throw invalid_file_format("");
    }

    // Read tiles
    std::string spec;
    std::getline(is, spec, '\n');
    Tiles tiles(ysize, std::vector<Tile*>(xsize, nullptr));
    for (int y = 0; y < ysize; ++y) {
        for (int x = 0; x < xsize; ++x) {
            // Parse tile specification
            std::getline(is, spec, ';');
            tiles[y][x] = new Tile(x, y,
                                   to_tile_type(spec[0]),
                                   to_direction(spec[1]));
        }
        std::getline(is, spec, '\n');
    }

    return GameMap(name, xsize, ysize, tiles);
}

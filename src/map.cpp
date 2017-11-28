#include <algorithm>
#include <iostream>
#include <fstream>
#include "map.h"



GameMap::GameMap(std::string name, int xsize, int ysize,
                 TowerType *empty_tower_type, TowerType *root_tower_type) :
    m_name(name), m_xsize(xsize), m_ysize(ysize), m_enemies({}),
    m_empty_tower_type(empty_tower_type), m_root_tower_type(root_tower_type) {
    // https://stackoverflow.com/questions/28663299/initializing-a-2d-vector
    Tiles tiles(ysize, std::vector<Tile*>(xsize, nullptr));
    m_tiles = tiles;
}


// TODO
GameMap::~GameMap() {}


std::string GameMap::name() const { return m_name; }
int GameMap::xsize() const { return m_xsize; }
int GameMap::ysize() const { return m_ysize; }
Tiles GameMap::tiles() const { return m_tiles; }
Enemies GameMap::enemies() const { return m_enemies; }
Tile* GameMap::get_tile(int x, int y) const { return m_tiles[y][x]; }
Tile* GameMap::get_tile(double x, double y) const {
    return m_tiles[int(y / tile_size)][int(x / tile_size)];
}
void GameMap::set_tile(int x, int y, Tile *tile) { m_tiles[y][x] = tile; }


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


GameMap game_map_from_file(const std::string &filename,
                           TowerType *empty_tower_type,
                           TowerType *root_tower_type) {
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

    // Initialize game map
    GameMap game_map = GameMap(name, xsize, ysize, empty_tower_type,
                               root_tower_type);

    // Read tiles
    std::string spec;
    std::getline(is, spec, '\n');
    for (int y = 0; y < ysize; ++y) {
        for (int x = 0; x < xsize; ++x) {
            // Parse tile specification
            std::getline(is, spec, ';');
            auto tile_type = to_tile_type(spec[0]);
            auto direction = to_direction(spec[1]);

            Tower *tower;
            if (is_buildable(tile_type))
                tower = root_tower_type->create_tower(x, y);
            else
                tower = empty_tower_type->create_tower(x, y);

            auto *tile = new Tile(x, y, tile_type, direction, tower);
            game_map.set_tile(x, y, tile);
            //TODO: add tower to the map
        }
        std::getline(is, spec, '\n');
    }

    return game_map;
}

#include <algorithm>
#include <iostream>
#include <fstream>
#include "map.h"


GameMap::GameMap(std::string &name, Tiles &tiles, Path &path) :
        m_name(name),
        m_tiles(tiles),
        m_path(path)
        {}

GameMap::~GameMap() {

}

std::string GameMap::name() const {
    return m_name;
}

Tiles GameMap::tiles() const {
    return m_tiles;
}

Path GameMap::path() const {
    return m_path;
}

Enemies GameMap::enemies() const {
    return m_enemies;
}

void GameMap::add_enemy(Enemy *enemy) {
    m_enemies.push_back(enemy);
}

std::ostream& operator<<(std::ostream &os, GameMap &obj) {
    auto tiles = obj.tiles();
    for (int y = 0; y < tiles.ysize; ++y) {
        for (int x = 0; x < tiles.xsize; ++x) {
            auto tile = tiles.tile(x, y);
            os << tile->tile_type() << tile->direction() << ";";
        }
        os << std::endl;
    }
    return os;
}



void GameMap::remove_enemy(Enemy *enemy) {
    if (enemy != nullptr) {
        auto it = m_enemies.begin();
        while (it != m_enemies.end()) {
            if (enemy == *it) {
                m_enemies.erase(it);
                break;
            }
            it++;
        }
    }
}


GameMap game_map_from_file(const std::string &filename,
                           TowerType *empty_tower_type,
                           TowerType *root_tower_type) {
    // Initialize GameMap constructor arguments
    std::string name, integer;
    int xsize, ysize, xstart, ystart;

    std::ifstream is(filename);

    if (is.fail()) {
        throw std::exception();
    }
    // Read the name of the game map
    std::getline(is, name, ';');

    // Read xsize
    std::getline(is, integer, ';');
    try {
        // Convert string to integer
        xsize = std::stoi(integer, nullptr, 0);
    } catch (std::invalid_argument&) {
        throw invalid_file_format("");
    }

    // Read ysize
    std::getline(is, integer, ';');
    try {
        // Convert string to integer
        ysize = std::stoi(integer, nullptr, 0);
    } catch (std::invalid_argument&) {
        throw invalid_file_format("");
    }

    // Read xsize
    std::getline(is, integer, ';');
    try {
        // Convert string to integer
        xstart = std::stoi(integer, nullptr, 0);
    } catch (std::invalid_argument&) {
        throw invalid_file_format("");
    }

    // Read ysize
    std::getline(is, integer, ';');
    try {
        // Convert string to integer
        ystart = std::stoi(integer, nullptr, 0);
    } catch (std::invalid_argument&) {
        throw invalid_file_format("");
    }

    // Initialize game map
    double tilesize = 1.0;
    auto tiles = Tiles(xsize, ysize, tilesize, root_tower_type, empty_tower_type);

    // Read tiles
    std::string spec;
    std::getline(is, spec, '\n');
    for (int y = 0; y < ysize; ++y) {
        for (int x = 0; x < xsize; ++x) {
            // Parse tile specification
            std::getline(is, spec, ';');
            auto tile_type = to_tile_type(spec[0]);
            auto direction = to_direction(spec[1]);

            // Create tower of right tower type in center of a tile.
            Tower *tower;
            if (is_buildable(tile_type))
                tower = root_tower_type->create_tower(
                        x * tilesize + 0.5, y * tilesize + 0.5);
            else
                tower = empty_tower_type->create_tower(
                        x * tilesize + 0.5, y * tilesize + 0.5);

            // Create new tile and place it into right tile
            auto *tile = new Tile(tile_type, direction, tower);
            tiles.tile(x, y, tile);
        }
        std::getline(is, spec, '\n');
    }

    // Path
    auto ls = construct_path(xstart, ystart, tiles);
    auto path = Path(ls);

    return GameMap(name, tiles, path);
}

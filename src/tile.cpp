#include "tile.h"


std::ostream& operator<<(std::ostream &os, TileType t) {
    switch (t) {
        case path: os << "p"; break;
        case grass: os << "g"; break;
        case water: os << "w"; break;
        default: os << "u"; break;
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, Direction d) {
    switch (d) {
        case north: os << 'N'; break;
        case east: os << 'E'; break;
        case south: os << 'S'; break;
        case west: os << 'W'; break;
        default: os << ' '; break;
    }
    return os;
}


TileType to_tile_type(char c) {
    switch (tolower(c)) {
        case 'p': return path;
        case 'g': return grass;
        case 'w': return water;
        default: return undefined_tile_type;
    }
}


Direction to_direction(char c) {
    switch (tolower(c)) {
        case 'n': return north;
        case 'e': return east;
        case 's': return south;
        case 'w': return west;
        default: return undefined_direction;
    }
}


Tile::Tile(int xindex, int yindex, TileType tile_type, Direction direction) :
        m_xindex(xindex), m_yindex(yindex), m_tile_type(tile_type),
        m_direction(direction) {
    // TODO: initialize tower as empty or root tower not nullptr
    m_tower = nullptr;
}

Tile::~Tile() { }

TileType Tile::tile_type() const { return m_tile_type; }
Direction Tile::direction() const { return m_direction; }
Tower *Tile::tower() const { return m_tower; }

bool Tile::upgrade_tower(Tower *new_tower) {
    if (new_tower == nullptr)
        return false;
    else {
        m_tower = new_tower;
        return true;
    }
}

Tower* Tile::remove_tower() {
    Tower* old_tower = m_tower;
    m_tower = nullptr;
    return old_tower;
}


void Tile::set_tower(Tower* tower) {
    if (tower != nullptr) m_tower = tower;
}
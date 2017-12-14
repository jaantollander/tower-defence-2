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

bool is_buildable(TileType t) {
    switch (t) {
        case path: return false;
        case grass: return true;
        case water: return false;
        default: return false;
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

Tile::Tile(TileType tile_type, Direction direction, Tower *tower) :
        m_tile_type(tile_type),
        m_direction(direction),
        m_tower(tower),
        m_upgraded(0)
        { }

Tile::~Tile() {
    delete(m_tower);
}

TileType Tile::tile_type() const {
    return m_tile_type;
}

Direction Tile::direction() const {
    return m_direction;
}

Tower *Tile::tower() const {
    return m_tower;
}

int Tile::upgrade_level() { return m_upgraded; }

bool Tile::upgrade_tower(int index) {
    auto new_tower = m_tower->upgrade(index);
    delete(m_tower);
    m_upgraded++;
    m_tower = new_tower;
}

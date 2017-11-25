#include "tile.h"


Tile::Tile(int xindex, int yindex, TileType tile_type, Direction direction) :
        m_xindex(xindex), m_yindex(yindex), m_tile_type(tile_type), m_direction(direction) {
    // TODO: initialize tower as empty tower not nullptr
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

bool Tile::remove_tower() {
    m_tower = nullptr;
    return true;
}

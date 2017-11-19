#include "tile.h"



Tile::Tile(int x, int y, TileType tile_type, Direction direction) :
        m_x(x),
        m_y(y),
        m_tile_type(tile_type),
        m_direction(direction),
        m_tower(nullptr) { }

int Tile::x() const { return m_x; }
int Tile::y() const { return m_y; }
TileType Tile::tile_type() const { return m_tile_type; }
Direction Tile::direction() const { return m_direction; }
TowerBase* Tile::tower() const { return m_tower; }

bool Tile::update_tower(TowerBase *new_tower) {
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

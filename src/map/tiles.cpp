#include "tiles.h"

Tiles::Tiles(int xsize_, int ysize_, double tilesize_,
             TowerType *root_tower_type,
             TowerType *empty_tower_type) :
        xsize(xsize_),
        ysize(ysize_),
        tilesize(tilesize_),
        m_root_tower_type(root_tower_type),
        m_empty_tower_type(empty_tower_type) {
    m_tiles = std::vector<std::vector<Tile*>>(ysize, std::vector<Tile*>(xsize, nullptr));
}

Tile* Tiles::tile(int x, int y) const {
    return m_tiles[y][x];
}

Tile* Tiles::tile(double x, double y) const {
    return m_tiles[int(y / tilesize)][int(x / tilesize)];
}

void Tiles::tile(int x, int y, Tile *tile) {
    m_tiles[y][x] = tile;
}

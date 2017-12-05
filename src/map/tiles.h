#ifndef TOWER_DEFENCE_2_TILES_H
#define TOWER_DEFENCE_2_TILES_H

#include "tile.h"


/// Type for 2D matrix of tiles. Note that [0][0] is top-left corner
class Tiles {
public:
    Tiles(int xsize_, int ysize_, double tilesize_, TowerType *root_tower_type,
              TowerType *empty_tower_type);

    /// Number of tiles in x dimension.
    const int xsize;

    /// Number of tiles in y dimension.
    const int ysize;

    /// Size of the tile for converting into coordinates.
    const double tilesize;

    //TODO: operator() instead of tile()

    /// Get individual tile by its indices
    Tile *tile(int x, int y) const;

    /// Get individual tile by its coordinates
    Tile *tile(double x, double y) const;

    /// Set tile by its indices
    void tile(int x, int y, Tile *tile);

private:
    TowerType *m_root_tower_type;
    TowerType *m_empty_tower_type;

    /// 2-Dimensional grid of tiles
    std::vector<std::vector<Tile*>> m_tiles;
};


#endif //TOWER_DEFENCE_2_TILES_H

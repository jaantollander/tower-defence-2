#ifndef TOWER_DEFENCE_2_TILE_H
#define TOWER_DEFENCE_2_TILE_H

#include <vector>
#include <string>
#include "objects/tower.h"


/// Possible types for the tile. Tile type defines what properties tile has.
enum TileType {
    /// Enemies walk on path. Players cannot place towers on path.
    path,

    /// Player can build towers on grass.
    grass,

    /// Players cannot build towers on water.
    water,

    /// Undefined tile type.
    undefined_tile_type
};


/// Possible directions (cardinal directions) for the enemy path.
enum Direction {
    north,
    east,
    south,
    west,
    undefined_direction
};


/// Individual tile in the game map. Contains properties of an individual tile
/// such as if tower can be built on a tile or if the tile is part of the path
/// that enemies follow.
class Tile {
public:
    Tile(int x, int y, TileType tile_type, Direction direction);
    ~Tile();

    // Coordinates
    int x() const;
    int y() const;

    /// Type of the tile
    TileType tile_type() const;

    /// The direction of the enemy path.
    Direction direction() const;

    Tower *tower() const;

    /// Update tower, true if successful.
    bool update_tower(Tower *new_tower);

    /// Sets tower to nullptr.
    bool remove_tower();

    /// True if a tower can be built on this tile.
    //bool is_buildable() const;

    /// True if this tile part of enemy path.
    //bool is_path() const;

private:
    const int m_x;
    const int m_y;
    const TileType m_tile_type;
    const Direction m_direction;

    /// Tile can contains one or zero towers.
    Tower *m_tower;

    //TODO: is map pointer necessary???
    //Map *m_map;
};


/// Type for 2D matrix of tiles. Note that [0][0] is top-left corner.
typedef std::vector<std::vector<Tile*>> Tiles;



#endif //TOWER_DEFENCE_2_TILE_H

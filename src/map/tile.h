#ifndef TOWER_DEFENCE_2_TILE_H
#define TOWER_DEFENCE_2_TILE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../objects/tower.h"


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

std::ostream& operator<<(std::ostream &os, TileType t);

/// Convert char to tile type.
TileType to_tile_type(char c);

/// True if a tower can be built in this tile else false.
bool is_buildable(TileType t);

/// Possible directions (cardinal directions) for the enemy path.
enum Direction {
    north,
    east,
    south,
    west,
    undefined_direction
};

std::ostream& operator<<(std::ostream& os, Direction d);

/// Convert char to direction.
Direction to_direction(char c);

/// Individual tile in the game map. Contains properties of an individual tile
/// such as if tower can be built on a tile or if the tile is part of the path
/// that enemies follow.
class Tile {
public:
    Tile(TileType tile_type, Direction direction, Tower *tower);

    ~Tile();

    /// Type of the tile
    TileType tile_type() const;

    /// The direction of the enemy path.
    Direction direction() const;

    /// Pointer to the tower that occupies the tile if any.
    Tower *tower() const;

    /// Update tower, true if successful. Delete the old tower.
    bool upgrade_tower(int index);

    /// Return the level of the tower, eg. how many times it has been upgraded
    int upgrade_level();

private:
    const TileType m_tile_type;
    const Direction m_direction;

    /// Tile can contains one or zero towers.
    int m_upgraded;
    Tower *m_tower;
};


#endif //TOWER_DEFENCE_2_TILE_H

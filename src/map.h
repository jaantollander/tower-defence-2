#ifndef TOWER_DEFENCE_2_MAP_H
#define TOWER_DEFENCE_2_MAP_H

#include <vector>
#include <string>
#include "objects/tower.h"
#include "objects/enemy.h"
#include "tile.h"


/// Height and width of a tile
const double tile_size = 1.0;


/// Type for collection of towers.
typedef std::vector<TowerType*> Towers;


/// Type for collection of enemies.
typedef std::vector<Enemy*> Enemies;


/// The map of the game. Contains information about the path that enemies
/// follow and where towers can be placed.
class GameMap {
public:
    /// Initialize empty game map
    GameMap(std::string name, int xsize, int ysize);

    /// Initialize game map with tiles
    GameMap(std::string name, int xsize, int ysize, Tiles &tiles);

    /// Game map will handle destruction of towers, so tiles don't need to
    ~GameMap();

    std::string name() const;
    int xsize() const;
    int ysize() const;
    Tiles tiles() const;
    Towers towers() const;
    Enemies enemies() const;

    /// Access individual tile by its indices
    Tile* get_tile(int x, int y) const;

    /// Access individual tile by its coordinates
    Tile* get_tile(double x, double y) const;

    /// Add new tower to the tile.
    /// - Tile should be buildable
    /// - There shouldn't already exist a tower
    void add_tower();

    /// Remove tower
    /// - On the death of an tower
    void remove_tower();

    /// Add new enemy to the tile.
    /// - Tile should be part of the path.
    /// - When enemy spawns
    void add_enemy();

    /// Remove enemy from the game.
    /// - On the death of an enemy
    void remove_enemy();

private:
    /// Name of the map
    const std::string m_name;

    /// Number of tile in x dimension
    const int m_xsize;

    /// Number of tiles in y dimension
    const int m_ysize;

    /// 2-Dimensional grid of tiles
    Tiles m_tiles;

    /// Collection of towers contained in the map
    Towers m_towers;

    /// Collection of enemies contained in the map
    Enemies m_enemies;
};


/// Print a representation of the game map
std::ostream &operator<<(std::ostream& os, GameMap &obj);


/// Loads game map from a text file. Example of mapfile formatting:
/// ```
/// name; xsize; ysize;
///	u;g;g;s;u;
///	u;g;s;w;q;
/// g;g;s;u;u;
/// ```
/// where tile types are:
/// water as u, grass as g and path depending on the direction
/// either n for north, s for south, e for east and w for west
GameMap load_game_map(const std::string &filename);



#endif //TOWER_DEFENCE_2_MAP_H

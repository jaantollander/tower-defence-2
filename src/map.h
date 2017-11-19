#ifndef TOWER_DEFENCE_2_MAP_H
#define TOWER_DEFENCE_2_MAP_H

#include <vector>
#include <string>
#include "objects/tower.h"
#include "objects/enemy.h"
#include "tile.h"


/// Type for binding collection of towers.
typedef std::vector<TowerBase*> Towers;


/// Type for binding collection of enemies.
typedef std::vector<EnemyBase*> Enemies;


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
    Tile* get_tile(int x, int y) const;
    void set_tile(int x, int y, Tile *tile);

    /// Print a representation of the game map
    void print_map() const;

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
    const std::string m_name;
    const int m_xsize;
    const int m_ysize;
    Tiles m_tiles;
    Towers m_towers;
    Enemies m_enemies;
};


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

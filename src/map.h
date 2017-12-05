#ifndef TOWER_DEFENCE_2_MAP_H
#define TOWER_DEFENCE_2_MAP_H

#include <vector>
#include <string>
#include "objects/tower.h"
#include "objects/enemy.h"
#include "tile.h"
#include "tiles.h"
#include "path.h"


/// Invalid file format exception class
class invalid_file_format : public std::exception {
public:
    explicit invalid_file_format(const std::string msg) : m_msg(msg) { };
    const char* what() { return m_msg.c_str(); }
private:
    const std::string m_msg;
};


//TODO: better data structure for removing arbitrary elements
/// Type for collection of enemies.
typedef std::vector<Enemy*> Enemies;


/// The map of the game. Contains information about the path that enemies
/// follow and where towers can be placed.
class GameMap {
public:
    /// Initialize empty game map
    GameMap(std::string &name, Tiles &tiles, Path &path);

    /// Game map will handle destruction of towers, so tiles don't need to
    ~GameMap();

    /// Name of the map
    std::string name() const;

    /// Tiles
    Tiles tiles() const;

    /// Path
    Path path() const;

    /// Access enemies contained in the map
    Enemies enemies() const;

    /// Upgrade existing tower into new one.
    void upgrade_tower(int x, int y, int index);

    /// Add new enemy to start of the path.
    void add_enemy(Enemy *enemy);

    /// Remove enemy.
    void remove_enemy(int index);

private:
    /// Name of the map
    const std::string m_name;

    /// Tiles
    Tiles m_tiles;

    /// Enemy path
    Path m_path;

    /// Collection of enemies contained in the map
    Enemies m_enemies;
};


/// Print a representation of the game map
std::ostream &operator<<(std::ostream& os, GameMap &obj);


/// Loads game map from a text file. Example of mapfile formatting:
/// ```
/// example;7;7;4;6;
/// w ;w ;w ;pN;w ;w ;w ;
/// g ;g ;g ;pN;g ;g ;g ;
/// g ;pE;pE;pN;g ;g ;g ;
/// g ;pN;g ;g ;g ;g ;g ;
/// g ;pN;pW;pW;pW;g ;g ;
/// g ;g ;g ;g ;pN;g ;g ;
/// w ;w ;w ;g ;pN;g ;g ;
/// ```
/// where tile types are:
/// water as u, grass as g and path depending on the direction
/// either n for north, s for south, e for east and w for west
GameMap game_map_from_file(const std::string &filename,
                           TowerType *empty_tower_type,
                           TowerType *root_tower_type);



#endif //TOWER_DEFENCE_2_MAP_H

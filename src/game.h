#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include "objects/tower.h"
#include "objects/enemy.h"


//TODO: probably need to change list to some other data structure
typedef std::list<TowerBase*> Towers;
typedef std::list<EnemyBase*> Enemies;


/// Class that contains information about the stats such as how much money
/// the player has and the score of the player.
class GameStats {
public:
    GameStats(int time, int score, int money);
    void update_time();
    void change_score();
    void change_money();

private:
    int m_time;
    int m_score;
    int m_money;
};


/// Individual tile in the game map.
class Tile {
public:
    Tile(bool is_walkable, bool is_buildable, TowerBase* tower);
    void set_is_walkable(bool is_walkable) { m_is_walkable = is_walkable; }
    void set_is_buildable(bool is_buildable) { m_is_buildable = is_buildable; }
    bool is_walkable() { return m_is_walkable; }
    bool is_buildable() { return m_is_buildable; }
    //TODO: throw error if tile is not buildable
    void set_tower(TowerBase* tower) { m_tower = tower; }
    TowerBase* get_tower() { return m_tower; }
private:
    /// Enemies can walk on walkable tiles.
    bool m_is_walkable;

    /// Towers can be built on buildable tiles.
    bool m_is_buildable;

    /// A tile can contain one tower at a time.
    TowerBase* m_tower;
};


typedef std::vector<std::vector<Tile*>> Tiles;

//TODO: load game map from file. Format?


/// The map of the game. Contains information about the path that enemies
/// follow and where towers can be placed.
class GameMap {
public:
    /// Initialize game map with sizes of x and y dimensions.
    GameMap(int xsize, int ysize);

private:
    int m_xsize;
    int m_ysize;

    /// Two-dimensional grid of tiles, shape (ysize, xsize).
    Tiles m_tiles;
};


/// Game class contains the game map, enemies, towers and game stats. This
/// class is also responsible for the implementation of the main game loop.
class GameEngine {
public:
    GameEngine(GameStats &stats,
               GameMap &game_map,
               Towers &towers,
               Enemies &enemies);

    /// Updates the game loop. In practice this method will be called by the
    /// main graphics loop.
    ///
    /// - spawn new enemies
    /// - movement of the enemies
    /// - towers shoot
    /// - remove dead enemies, add money and score from killing enemies
    /// - enemies shoot
    /// - update game stats such as money when en
    /// - etc
    void update();

    //TODO: add and remove enemies
    //TODO: add and remove towers
private:
    GameStats m_stats;
    GameMap m_game_map;
    Towers m_towers;
    Enemies m_enemies;
};


#endif //TOWER_DEFENCE_2_GAME_H

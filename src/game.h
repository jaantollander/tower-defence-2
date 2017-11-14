#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include "objects/tower.h"
#include "objects/enemy.h"


const int tile_size = 2;

typedef std::vector<TowerBase *> Towers;
typedef std::vector<EnemyBase *> Enemies;


/// Directions for the enemy path
enum Directions {
    north,
    east,
    south,
    west,
    undefined_direction
};


/// Individual tile in the game map. Contains properties of an individual tile
/// such as if tower can be built on a tile or if the tile is part of the path
/// that enemies follow.
///
/// Tile is immutable. New tile needs to be created in order to change
/// properties of an tile.
class Tile {
public:
    Tile(bool is_buildable, bool is_path, Directions direction);

    /// True if a tower can be built on this tile.
    bool is_buildable() { return m_is_buildable; }

    /// True if this tile part of enemy path.
    bool is_path() { return m_is_path; }

    /// The direction of the enemy path.
    Directions direction() { return m_direction; }
private:
    const bool m_is_buildable;
    const bool m_is_path;
    const Directions m_direction;
};


/// Type for grid of tiles
typedef std::vector<std::vector<Tile*>> Tiles;


/// The map of the game. Contains information about the path that enemies
/// follow and where towers can be placed.
class GameMap {
public:
    GameMap(int xsize, int ysize);

private:
    int m_xsize;
    int m_ysize;
    Tiles m_tiles;
};


//TODO: load game map from file. Format?


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


/// Game class contains the game map, enemies, towers and game stats. This
/// class is also responsible for the implementation of the main game loop which
/// modifies the properties of the objects by using the rules of the game logic.
class GameEngine {
public:
    GameEngine(GameStats &stats,
               GameMap &game_map,
               Towers &towers,
               Enemies &enemies);

    /// Add new tower to the tile. Check that the tile is buildable and there
    /// isn't already a tower.
    void add_tower(Tile *tile, TowerBase *tower);

    /// Remove tower
    void remove_tower();

    /// Add new enemy to the tile. Check that the tile is part of the path.
    void add_enemy(Tile *tile, EnemyBase *enemy);

    /// Remove enemy
    void remove_enemy();

    /// Implements movement of objects such as enemies.
    void movement();

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

private:
    GameStats m_stats;
    GameMap m_game_map;

    //TODO: bind objects to the tiles they currently occupy
    Towers m_towers;
    Enemies m_enemies;
};


#endif //TOWER_DEFENCE_2_GAME_H

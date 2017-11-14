#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include <string>
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
    /// Initialize empty game map
    GameMap(int xsize, int ysize);

    /// Load game map from file
    GameMap(std::string &path);

    int get_xsize() const { return m_xsize; }
    int get_ysize() const { return m_ysize; }
    Tile* get_tile(int x, int y) const { return m_tiles[y][x]; }
    void set_tile(int x, int y, Tile *tile) { m_tiles[y][x] = tile; }

private:
    const int m_xsize;
    const int m_ysize;
    Tiles m_tiles;
};


/// Contains information to start and run different game levels.
class GameLevel {
public:
    GameLevel(int starting_money);

private:
    const int m_starting_money;
    //TODO: how many enemies will spawn
    //TODO: enemy spawn interval
};


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
    GameEngine(GameStats &stats, GameMap &game_map, GameLevel game_level,
               Towers &towers, Enemies &enemies);

    /// Add new tower to the tile. Check that the tile is buildable and there
    /// isn't already a tower.
    void add_tower(Tile *tile, TowerBase *tower);

    /// Remove tower
    /// - if tower dies
    void remove_tower();

    /// Add new enemy to the tile. Check that the tile is part of the path.
    void add_enemy(Tile *tile, EnemyBase *enemy);

    /// Remove enemy from the game.
    /// - if enemy dies
    void remove_enemy();

    /// Implements movement of objects that can move (enemies).
    void movement();

    /// Towers attack enemies. Increase score and money if enemies die and
    /// remove dead enemies from the game.
    void towers_attack();

    /// Enemies attack towers
    void enemies_attack();

    /// Updates the game loop. In practice this method will be called by the
    /// main graphics loop.
    void update();

private:
    GameStats m_stats;
    GameMap m_game_map;
    GameLevel m_game_level;

    //TODO: bind objects to the tiles they currently occupy
    Towers m_towers;
    Enemies m_enemies;
};


#endif //TOWER_DEFENCE_2_GAME_H

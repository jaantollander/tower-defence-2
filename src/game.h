#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include <string>
#include "objects/tower.h"
#include "objects/enemy.h"
#include "tile.h"
#include "map.h"


/// Contains information to start and run different game levels.
class GameLevel {
public:
    GameLevel(int starting_money, int enemies_spawned,
              std::vector<int> &enemy_spawn_interval);

    void increment_enemies_spawned();

private:
    const int m_starting_money;
    int m_enemies_spawned;
    const std::vector<int> m_enemy_spawn_interval;
};


/// Class that contains information about the stats such as how much money
/// the player has and the score of the player.
class GameStats {
public:
    GameStats(int time, int score, int money);

    /// Increments the game time by 1.
    void update_time();

    /// Change player's score. Game score can't go below zero.
    void change_score(int amount);

    /// Change player's money. Return false and doesn't change the value if the
    /// amount of change would drop player's money below zero otherwise returns
    /// true and changes the money based on the amount given.
    bool change_money(int amount);

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
    GameEngine(GameStats &game_stats, GameMap &game_map, GameLevel &game_level);
    ~GameEngine();

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
    GameStats m_game_stats;
    GameMap m_game_map;
    GameLevel m_game_level;
};


#endif //TOWER_DEFENCE_2_GAME_H

#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include "objects/enemy.h"
#include "objects/tower.h"
#include "map/tile.h"
#include "map/map.h"
#include "level.h"


// Deferred declaration
class graphicsEngine;


/// Game states
enum GameState {
    ///
    level_unfinished,

    ///
    level_completed,

    ///
    game_over,
};

enum GameSpeed {
    normal,
    fast
};


/// Game class contains the game map, enemies, towers and game stats. This
/// class is also responsible for the implementation of the main game loop which
/// modifies the properties of the objects by using the rules of the game logic.
class GameEngine {
public:
    GameEngine(double time, double timestep, int score,
                   GameLevel &game_level, GameMap &game_map);

    ~GameEngine();

    double time() const;
    const double timestep() const;
    int score() const;
    int money() const;
    int lives() const;

    /// Change the gamespeed to fast or normal
    void change_game_speed(GameSpeed new_speed);

    /// Increments the game time by one timestep.
    void increment_time();

    /// Change player's score. Game score can't go below zero.
    void add_score(int amount);

    /// Change player's money.
    /// \returns false and doesn't change the value if the amount of change
    ///          would reduce player's money below zero otherwise true and changes
    ///          the money based on the amount given.
    bool add_money(int amount);

    /// Reduce one life from the player. Player dies if lives reach zero.
    /// \returns true if player dies else false.
    void reduce_life();

    /// Upgrade existing tower into new one.
    void upgrade_tower(int x, int y, int index);

    /// Change targeting policy of all towers
    void change_targeting(TargetingPolicy new_policy);

    /// Add new enemy to game map
    void add_enemy(Enemy *enemy);

    /// Handles level specific tasks such as spawning new enemies according to
    /// the game level description.
    void advance_game_level();

    /// Move enemies along the path.
    /// - If enemy reaches the end of the path
    ///     - Remove enemy from the game
    ///     - Reduce players score
    ///     - Reduce one life from player
    void enemy_movement();

    /// Other combat objects that this object can target.
    /// - withing the attack range
    /// - targeting policy
    Enemy* find_targets(Tower *tower, Enemies &enemies);

    /// Towers attack enemies. Increase score and money if enemies die and
    /// remove dead enemies from the game.
    void towers_attack(graphicsEngine& gE);

    /// Updates the game loop. In practice this method will be called by the
    /// main graphics loop.
    /// TODO: Events: game over, level completed
    GameState update(graphicsEngine& gE);

    /// Getter for game map
    GameMap game_map();

    friend bool update_high_score(const std::string &filename, GameEngine engine);

private:
    GameSpeed m_speed;
    double m_time;
    double m_timestep;
    int m_score;
    int m_money;
    int m_lives;
    GameLevel m_game_level;
    GameMap m_game_map;
};

/// Function that reads high scores from a file
/// top 5 scores are saved. File format is: """
/// 2890
/// 2510
/// """ etc.
std::vector<int> high_score(const std::string &filename);

/// Updates high score if needed, takes the name of
/// the file where high scores are kept
/// Returns true if high scores were changed
bool update_high_score(const std::string &filename, GameEngine engine);

#include "Graphics/graphicsEngine.h"


#endif //TOWER_DEFENCE_2_GAME_H

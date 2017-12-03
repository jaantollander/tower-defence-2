#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include <vector>
#include "objects/enemy.h"
#include "objects/tower.h"
#include "tile.h"
#include "map.h"
#include "level.h"


/// Game class contains the game map, enemies, towers and game stats. This
/// class is also responsible for the implementation of the main game loop which
/// modifies the properties of the objects by using the rules of the game logic.
class GameEngine {
public:
    GameEngine(double time, int score, int money, double timestep, int lives,
                   GameMap &game_map, GameLevel &game_level);

    ~GameEngine();

    /// Increments the game time by one timestep.
    void increment_time();

    /// Change player's score. Game score can't go below zero.
    void change_score(int amount);

    /// Change player's money.
    /// @returns false and doesn't change the value if the amount of change
    ///          would reduce player's money below zero otherwise true and changes
    ///          the money based on the amount given.
    bool change_money(int amount);

    /// Reduce one life from the player. Player dies if lives reach zero.
    /// @returns true if player dies else false.
    bool recude_life();

    /// Handles level specific tasks such as spawning new enemies according to
    /// the game level description.
    void advance_game_level();

    /// Move enemies along the path.
    /// - If enemy reaches the end of the path
    ///     - Remove enemy from the game
    ///     - Reduce players score
    ///     - Reduce one life from player
    void enemy_movement();

    /// Towers attack enemies. Increase score and money if enemies die and
    /// remove dead enemies from the game.
    void towers_attack();

    /// Updates the game loop. In practice this method will be called by the
    /// main graphics loop.
    void update();

    /// Other combat objects that this object can target.
    /// - withing the attack range
    /// - targeting policy
    Enemies find_targets(Tower *tower, Enemies &enemies);

private:
    double m_time;
    int m_score;
    int m_money;
    const double m_timestep;
    int m_lives;
    GameMap m_game_map;
    GameLevel m_game_level;
};


#endif //TOWER_DEFENCE_2_GAME_H

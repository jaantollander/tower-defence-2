#ifndef TOWER_DEFENCE_2_GAME_H
#define TOWER_DEFENCE_2_GAME_H


#include "objects/enemy.h"
#include "tile.h"
#include "map.h"
#include "level.h"
#include "stats.h"


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

    /// Updates the game loop. In practice this method will be called by the
    /// main graphics loop.
    /// - Advance game level
    /// - Movement
    /// - Tower attack turn
    /// - Enemy attack turn
    /// - Update game time
    void update();

private:
    GameStats m_game_stats;
    GameMap m_game_map;
    GameLevel m_game_level;
};


#endif //TOWER_DEFENCE_2_GAME_H

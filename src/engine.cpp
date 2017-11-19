#include "engine.h"


GameEngine::GameEngine(GameStats &game_stats,
                       GameMap &game_map,
                       GameLevel &game_level) :
        m_game_stats(game_stats),
        m_game_map(game_map),
        m_game_level(game_level) { }

//TODO:
GameEngine::~GameEngine() {}


//void GameEngine::update() {
    //TODO: spawn new enemies according to level description
//    movement();
//    towers_attack();
//    enemies_attack();
//    m_stats.update_time();
//}

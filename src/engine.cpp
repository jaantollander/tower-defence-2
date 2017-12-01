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

std::vector<Enemy> GameEngine::enemies_in_range(Tower* tower) {
    std::vector<Enemy> in_range;
    size_t size = m_game_map.enemies().size();
    int i = 0;
    while (i < size) {
        if (tower -> distance(*m_game_map.enemies()[i]) <= tower -> radius()) {
            in_range.push_back(*m_game_map.enemies()[i]);
        }
        i++;
    }
    return in_range;
}


void GameEngine::towers_attack() {
    size_t size = m_game_map.towers().size();
    int i = 0;
    while (i < size) {
        if (m_game_map.towers()[i] -> tower_type().name() != "EmptyTower") {
            std::vector<Enemy> in_range = enemies_in_range(m_game_map.towers()[i]);
            if (in_range.size() != 0) {
                //TODO: which enemy is attacked?
                Enemy& e = in_range[0];
                m_game_map.towers()[i] -> deal_damage(e);
            }
        }
        i++;
    }
}

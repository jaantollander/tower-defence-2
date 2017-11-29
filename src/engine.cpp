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

std::vector<Enemy> GameEngine::enemies_in_range(Tower& tower) {
    std::vector<Enemy> in_range;
    auto it = m_game_map.enemies().begin();
    while (it != m_game_map.enemies().end()) {
        if (tower.distance(**it) <= tower.radius()) {
            in_range.push_back(**it);
        }
        it++;
    }
    return in_range;
}

/*
void GameEngine::towers_attack() {
    auto it = m_game_map.towers().begin();
    while (it != m_game_map.towers().end()) {
        if ((*it) -> tower_type().name() != "EmptyTower") {
            std::vector<Enemy> in_range = enemies_in_range(**it);
            std::cout << "in range:" << in_range.size() << std::endl;
            if (in_range.size() != 0) {
                //TODO: which enemy is attacked?
                (*it) -> deal_damage(in_range[0]);
            }
       }
        it++;
    }
}
*/
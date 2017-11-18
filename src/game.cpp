#include "game.h"


GameLevel::GameLevel(int starting_money, int enemies_spawned,
                     std::vector<int> &enemy_spawn_interval) :
        m_starting_money(starting_money),
        m_enemies_spawned(enemies_spawned),
        m_enemy_spawn_interval(enemy_spawn_interval) { }


void GameLevel::increment_enemies_spawned() { m_enemies_spawned++; }


GameStats::GameStats(int time, int score, int money) :
        m_time(time), m_score(score), m_money(money) { }


void GameStats::update_time() { m_time++; }


void GameStats::change_score(int amount) {
    int new_score = m_score + amount;
    if (new_score < 0)
        m_score = 0;
    else
        m_score = new_score;
}


bool GameStats::change_money(int amount) {
    int new_money = m_money + amount;
    if (new_money < 0)
        return false;
    else {
        m_money = new_money;
        return true;
    }
}


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

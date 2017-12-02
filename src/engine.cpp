#include "engine.h"


GameEngine::GameEngine(double time, int score, int money, double timestep,
                       int lives, GameMap &game_map, GameLevel &game_level) :
        m_time(time), m_score(score), m_money(money), m_timestep(timestep),
        m_lives(lives), m_game_map(game_map),
        m_game_level(game_level) { }


GameEngine::~GameEngine() { }


void GameEngine::increment_time() { m_time += m_timestep; }


void GameEngine::change_score(int amount) {
    int new_score = m_score + amount;
    if (new_score < 0)
        m_score = 0;
    else
        m_score = new_score;
}


bool GameEngine::change_money(int amount) {
    int new_money = m_money + amount;
    if (new_money < 0)
        return false;
    else {
        m_money = new_money;
        return true;
    }
}


bool GameEngine::recude_life() {
    m_lives--;
    return m_lives <= 0;
}


void GameEngine::advance_game_level() {

}


void GameEngine::enemy_movement() {

}


void GameEngine::towers_attack() {
    //TODO: iterate over all tower, towers that have over zero damage should
    //      attack their targets
    //TODO: if enemy is killed increase
}


void GameEngine::update() {
    advance_game_level();
    enemy_movement();
    towers_attack();
    increment_time();
}


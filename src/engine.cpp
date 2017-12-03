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


Enemies GameEngine::find_targets(Tower *tower, Enemies &enemies) {
    if (enemies.empty())
        return {};

    switch (tower->targeting_policy()) {
        case target_first: {
            auto path = this->m_game_map.path();

            // Object within attack range
            Enemy *first = nullptr;
            double d_min = path.get_length();

            // Iterate over enemies
            for (auto enemy : enemies) {
                // Check if enemy is in attack range
                if (tower->distance(*enemy) < tower->attack_range()) {
                    // Targeting policy
                    auto d = path.distance_from_end(
                            enemy->distance_travelled());
                    if (d <= d_min) {
                        d_min = d;
                        first = enemy;
                    }
                }
            }

            return {first};
        }
        case target_last:
            //TODO: similar implementation as for target_first
            return {};
        case target_least_health:
            //TODO: similar implementation as for target_first
            return {};
        default:
            throw std::exception();
    }
}


void GameEngine::towers_attack() {
    auto tiles = this->m_game_map.tiles();
    // Iterate over all tower in tiles
    for (int y = 0; y < tiles.ysize; ++y) {
        for (int x = 0; x < tiles.xsize; ++x) {
            auto tile = tiles.tile(x, y);
            auto tower = tile->tower();
            if (tower->damage() > 0) {
                auto enemies = this->m_game_map.enemies();
                auto targets = find_targets(tower, enemies);
                for (auto target : targets) {
                    tower->deal_damage(*target);
                    //TODO: check if enemy dies and update money, score and remove enemy
                }
            }
        }
    }
}


void GameEngine::update() {
    advance_game_level();
    enemy_movement();
    towers_attack();
    increment_time();
}

#include "engine.h"


GameEngine::GameEngine(double time, double timestep, int score, int money, int lives,
                       GameLevel &game_level, GameMap &game_map) :
        m_time(time), m_score(score), m_money(money), m_timestep(timestep),
        m_lives(lives), m_game_map(game_map),
        m_game_level(game_level) {
    m_money = game_level.initial_money();
    m_lives = game_level.initial_lives();
}


GameEngine::~GameEngine() {

}


void GameEngine::add_score(int amount) {
    int new_score = m_score + amount;
    if (new_score < 0)
        m_score = 0;
    else
        m_score = new_score;
}


bool GameEngine::add_money(int amount) {
    int new_money = m_money + amount;
    if (new_money < 0)
        return false;
    else {
        m_money = new_money;
        return true;
    }
}


bool GameEngine::reduce_life() {
    m_lives--;
    return m_lives <= 0;
}


void GameEngine::advance_game_level() {
    auto start = m_game_map.path().start();

    // New enemies to spawn
    auto enemy_types = m_game_level.spawn_enemies(m_time);

    for (auto enemy_type : enemy_types) {
        // Create new enemies
        auto enemy = enemy_type->create_enemy(start.x, start.y);

        // Add new enemies to game map
        m_game_map.add_enemy(&enemy);
    }

}


void GameEngine::enemy_movement() {
    auto enemies = m_game_map.enemies();
    auto path = m_game_map.path();

    for (auto enemy : enemies) {
        enemy->distace_travelled(enemy->speed() * m_timestep);
        auto d = enemy->distance_travelled();
        if (path.has_reached_end(d)) {
            //reduce players score
            this->add_score(-enemy->score());

            // Reduce life and check if player dies
            if (this->reduce_life()) {
                //TODO: player is dead game over

            }

            //TODO: remove enemy
//            m_game_map.remove_enemy()
        } else {
            // Update enemy's x and y positions
            auto p = path.position(d);
            enemy->position(p.x, p.y);
        }
    }

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
                    //TODO: attack_speed
//                    tower->deal_damage(*target);

                    this->add_money(target->money());
                    this->add_score(target->score());

                    //TODO: check if enemy dies and remove enemy
                }
            }
        }
    }
}


void GameEngine::increment_time() {
    m_time += m_timestep;
}


void GameEngine::update() {
    advance_game_level();
    enemy_movement();
    towers_attack();
    increment_time();
}

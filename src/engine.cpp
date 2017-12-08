#include <iostream>
#include <fstream>
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

void GameEngine::upgrade_tower(int x, int y, int index) {
    auto tiles = m_game_map.tiles();
    auto tile = tiles.tile(x, y);

    if (add_money(0))
        tile->upgrade_tower(index);
}

void GameEngine::add_enemy(Enemy *enemy) {
    m_game_map.add_enemy(enemy);
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
            m_game_map.remove_enemy(enemy);
        } else {
            // Update enemy's x and y positions
            auto p = path.position(d);
            enemy->position(p.x, p.y);
        }
    }

}

Enemy* GameEngine::find_targets(Tower *tower, Enemies &enemies) {
    if (enemies.empty())
        return nullptr;

    auto path = this->m_game_map.path();
    switch (tower->targeting_policy()) {
        case target_first: {

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

            return first;
        }
        case target_last: {
            Enemy* last = nullptr;
            double d_max = 0;
            for (auto enemy : enemies) {
                if (tower -> distance(*enemy) < tower -> attack_range()) {
                    double d = path.distance_from_end(
                            enemy -> distance_travelled());
                    if (d >= d_max) {
                        d_max = d;
                        last = enemy;
                    }
                }
            }
            return last;
        }
        case target_least_health: {
            Enemy* weak = nullptr;
            int least_hp = 10000; //should be larger than hp of any enemy
            for (Enemy* enemy : enemies) {
                if (tower -> distance(*enemy) < tower -> attack_range()) {
                    if (enemy->health() < least_hp) {
                        least_hp = enemy -> health();
                        weak = enemy;
                    }
                }
            }
            return weak;
        }

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
                auto target = find_targets(tower, enemies);
                if (target != nullptr) {

                    //TODO: attack_speed
                    tower->deal_damage(*target);

                    if (target->is_dead()) {
                        this->add_money(target->money());
                        this->add_score(target->score());
                        this->m_game_map.remove_enemy(target);
                    }
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

std::vector<int> GameEngine::high_score(const std::string &filename) {
    std::ifstream is(filename);
    if (is.fail()) { throw std::exception(); }
    std::vector<int> high_scores;
    int i = 0;
    int score = 0;
    std::string str;

    //only top 5 are saved
    while (i < 5) {
        std::getline(is, str, '\n');
        if (!is.eof()) {
            try { score = std::stoi(str, nullptr, 0); }
            catch (std::invalid_argument &) { throw invalid_file_format(""); }
            high_scores.push_back(score);
            i++;
        }
        else break;
    }
    return high_scores;
}

bool GameEngine::update_high_score(const std::string &filename) {
    std::vector<int> scores;
    try { scores = high_score(filename); }
    catch (invalid_file_format &) { return false; }
    bool flag = false;
    auto it = scores.begin();

    //check if score better than previous
    while (it != scores.end()) {
        if (m_score > *it) {
            flag = true;
            scores.insert(it, m_score);
            break;
        } else it++;
    }

    //check if there are less than five scores
    if (flag == false && scores.size() < 5) {
        scores.insert(it, m_score);
        flag = true;
    }

    //write the new scores, if they are better than previous
    if (flag) {
        std::ofstream os(filename);
        if (os.fail()) throw std::exception();
        int i = 0;
        it = scores.begin();
        while (it != scores.end() && i < 5) {
            os << *it << std::endl;
            it++; i++;
        }
        os.close();
    }
    return flag;
}

#include "engine.h"

GameLevel::GameLevel(int initial_money, int initial_lives, int enemies_spawned,
                     EnemySpawnInterval &enemy_spawn_interval) :
        m_initial_money(initial_money),
        m_initial_lives(initial_lives),
        m_enemies_spawned(enemies_spawned),
        m_enemy_spawn_interval(enemy_spawn_interval)
        { }

int GameLevel::initial_money() const {
    return m_initial_money;
}

int GameLevel::initial_lives() const {
    return m_initial_lives;
}

std::vector<EnemyType *> GameLevel::spawn_enemies(double time) {
    std::vector<EnemyType *> enemies = {};
    auto size = m_enemy_spawn_interval.size();
    for (int i = m_enemies_spawned; i < size; ++i) {
        auto s = m_enemy_spawn_interval[i];
        if (s.first < time) {
            enemies.push_back(s.second);
            m_enemies_spawned++;
        } else
            break;
    }
    return enemies;
}

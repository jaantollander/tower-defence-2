#include "engine.h"

GameLevel::GameLevel(int starting_money, int enemies_spawned,
                     std::vector<int> &enemy_spawn_interval) :
        m_starting_money(starting_money),
        m_enemies_spawned(enemies_spawned),
        m_enemy_spawn_interval(enemy_spawn_interval) { }

void GameLevel::increment_enemies_spawned() { m_enemies_spawned++; }

#include "engine.h"

GameLevel::GameLevel(int initial_money, int initial_lives, int enemies_spawned,
                     EnemySpawnInterval &enemy_spawn_interval) :
        m_initial_money(initial_money),
        m_initial_lives(initial_lives),
        m_enemies_spawned(enemies_spawned),
        m_enemy_spawn_interval(enemy_spawn_interval) { }

void GameLevel::increment_enemies_spawned() { m_enemies_spawned++; }

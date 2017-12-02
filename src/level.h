#ifndef TOWER_DEFENCE_2_LEVEL_H
#define TOWER_DEFENCE_2_LEVEL_H

#include <vector>
#include <string>
#include "objects/tower.h"


/// Type for collection of pair where double denotes the time when enemy of
/// type EnemyType should spawn.
typedef std::vector<std::pair<double, EnemyType *>> EnemySpawnInterval;


/// Contains information to start and run different game levels.
/// What types of enemies will spawn, when and where.
class GameLevel {
public:
    GameLevel(int initial_money, int initial_lives, int enemies_spawned,
                  EnemySpawnInterval &enemy_spawn_interval);

    void increment_enemies_spawned();

private:
    const int m_initial_money;
    const int m_initial_lives;
    int m_enemies_spawned;
    const EnemySpawnInterval m_enemy_spawn_interval;
};



#endif //TOWER_DEFENCE_2_LEVEL_H
